#include <TMinuit.h>

#include <utils/Utilities.hh>
#include "TDPAD.hh"
#include "GaussianDistr.hh"

namespace GamR {
  namespace AngDist {
    void GaussianDistr::SetField() {
      double sigma = FWHM/2.3548;
      double start = mean - (double)Limit*sigma;
      double stop = mean + (double)Limit*sigma;
      Bhfs.clear();
      RelAmps.clear();
      for (int i=0; i<nSamples; ++i) {
        double Bhf = start + (double)i*(stop-start)/(double)(nSamples-1.0);
        Bhfs.push_back(Bhf);
        RelAmps.push_back(exp(-0.5*pow(((Bhf-mean)/sigma), 2)));
      }
      Normalise();
    }

    void GaussianDistr::Normalise() {
      double total = 0;
      for (int i=0; i<RelAmps.size(); ++i) {
        total += RelAmps[i];
      }
      for (int i=0; i<RelAmps.size(); ++i) {
        RelAmps[i] = RelAmps[i]/total;
      }          
    }
    
    double GaussianDistr::RatioFunc(double x, double a, double gfac, double off) {
      double ratio = 0;
      for (int i=0; i<nSamples; ++i) {
        double Bhf = Bhfs[i];
        ratio += a*RelAmps[i]*sin(-2*Bhf*0.04789*gfac*(x-off));
      }
      return ratio;
    }

    double GaussianDistr::operator() (double *x, double *p) {
      return RatioFunc(x[0], p[0], p[1], p[2]);
    }

    TF1* GaussianDistr::GetFunc() {
      TF1* func = new TF1("GaussianRatio", *this, Low, High, 3);
      func->SetParameter(0, amp);
      func->SetParameter(1, g);
      func->SetParameter(2, offset);
      return func;
    }

    class GaussianDistr::GlobalChiSquare {
    private:
      static GaussianDistr *p;

    public:
      GlobalChiSquare(GaussianDistr *parent) { p = parent; }

      static void minuit(int &npar, double *gin, double &f, double *par, int iflag) {
        f = 0;
        
        p->SetAmp(par[0]);
        p->SetG(par[1]);
        p->SetMean(par[2]);
        p->SetFWHM(par[3]);
        p->SetOffset(par[4]);

        TF1 *func; 
        if (p->FixedField) { 
          func = p->FitFunc; //TF1 generated before, field does not change
        }
        else { //Generate new TF1, set field again
          p->SetField();
          func = p->GetFunc();
        }
        //set parameters of func
        func->SetParameter(0, par[0]);
        func->SetParameter(1, par[1]);
        func->SetParameter(2, par[4]);

        f = p->Hist->Chisquare(func, "R");

        if (!(p->FixedField)) { delete func; }
        
        return;        
      }
    };

    GaussianDistr *GaussianDistr::GlobalChiSquare::p = nullptr;
    //int GaussianDistr::FixedField = 0;

    void GaussianDistr::Fit(int quiet) {
      int npars = 5;
      auto gMinuit = new TMinuit(npars);
      if (quiet) {
        gMinuit->Command("SET PRINT -1");
      }

      /* check if field is fixed or not */
      if (FixedField) {
        SetField();
        FitFunc = new TF1("GaussianDistr", *this, Low, High, 3);
      }
      
      GlobalChiSquare func(this);
      gMinuit->SetFCN(func.minuit);

      double arglist[10];
      arglist[0] = 1;

      int ierflg = 0;      
      gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
      arglist[0] = 2;
      gMinuit->mnexcm("SET STR", arglist, 1, ierflg);

      int parnum = 0;

      std::vector<std::string> parnames = {"Amp", "g", "mean", "FWHM", "offset"};
      std::vector<double> pars = GetPars();
      for (int i=0; i<5; ++i) {
        double min = ParLimsLow[i];
        double max = ParLimsHigh[i];
        std::cout << i << "   " << min << "   " << max << "   " << pars[i] << std::endl;
        gMinuit->mnparm(parnum, parnames[i].c_str(), pars[i], ParErrs[i], min, max, ierflg);
        ++parnum;
      }

      for (int i=0; i<5; ++i) {
        if (ParFix[i]==1) {
          gMinuit->FixParameter(i);
        }
      }

      arglist[0] = 100000;
      arglist[1] = 1;
      gMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);
      gMinuit->mnimpr();
      gMinuit->mnexcm("HESSE", arglist, 2, ierflg);
      gMinuit->mnexcm("MINOS", arglist, 2, ierflg);

      ParVals.clear();
      ParErrs.clear();
      for (int i=0; i<5; ++i) {
        double parVal, parErr;
        gMinuit->GetParameter(i, parVal, parErr);
        ParVals.push_back(parVal);
        ParErrs.push_back(parErr);
      }
      SetPars();

      delete gMinuit;      
    }

    /* DOUBLE GAUSSIAN */
    void DoubleGaussianDistr::SetField() {
      double sigma = FWHM/2.3548;
      double start = mean - (double)Limit*sigma;
      double stop = mean + (double)Limit*sigma;
      Bhfs.clear();
      RelAmps.clear();
      for (int i=0; i<nSamples; ++i) {
        double Bhf = start + (double)i*(stop-start)/(double)(nSamples-1.0);
        Bhfs.push_back(Bhf);
        RelAmps.push_back(exp(-0.5*pow(((Bhf-mean)/sigma), 2)));
      }
      Normalise();
    }

    void DoubleGaussianDistr::Normalise() {
      double total = 0;
      for (int i=0; i<RelAmps.size(); ++i) {
        total += RelAmps[i];
      }
      for (int i=0; i<RelAmps.size(); ++i) {
        RelAmps[i] = RelAmps[i]/total;
      }          
    }
    
    double DoubleGaussianDistr::RatioFunc(double x, double a1, double a2, double gfac1, double gfac2, double t1, double t2, double n, double off) {
      double ratio = 0;
      for (int i=0; i<nSamples; ++i) {
        double Bhf = Bhfs[i];
        double intensity1 = n/t1*exp(-(x-off)/t1)*(1+a1*sin(-2*(x-off)*0.04789*Bhf*gfac1)) +
          1.0/t2*exp(-(x-off)/t2)*(1+a2*sin(-2*(x-off)*0.04789*Bhf*gfac2));
  
        double intensity2 = n/t1*exp(-(x-off)/t1)*(1+a1*sin(2*(x-off)*0.04789*Bhf*gfac1)) +
          1.0/t2*exp(-(x-off)/t2)*(1+a2*sin(2*(x-off)*0.04789*Bhf*gfac2));

        double r = 0;
        if (intensity1 == 0 && intensity2 == 0) { continue; }
  
        r = ((intensity1-intensity2)/(intensity1 + intensity2));

        ratio += RelAmps[i]*r;
      }
      return ratio;
    }

    double DoubleGaussianDistr::operator() (double *x, double *p) {
      return RatioFunc(x[0], p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
    }

    TF1* DoubleGaussianDistr::GetFunc() {
      TF1* func = new TF1("DoubleGaussianRatio", *this, Low, High, 8);
      func->SetParameter(0, amp1);
      func->SetParameter(1, amp2);
      func->SetParameter(2, g1);
      func->SetParameter(3, g2);
      func->SetParameter(4, tau1);
      func->SetParameter(5, tau2);
      func->SetParameter(6, n1n2);
      func->SetParameter(7, offset);
      return func;
    }

    class DoubleGaussianDistr::GlobalChiSquare {
    private:
      static DoubleGaussianDistr *p;

    public:
      GlobalChiSquare(DoubleGaussianDistr *parent) { p = parent; }

      static void minuit(int &npar, double *gin, double &f, double *par, int iflag) {
        f = 0;

        p->SetAmp1(par[0]);
        p->SetAmp2(par[1]);
        p->SetG1(par[2]);
        p->SetG2(par[3]);
        p->SetTau1(par[4]);
        p->SetTau2(par[5]);
        p->SetN1N2(par[6]);
        p->SetMean(par[7]);
        p->SetFWHM(par[8]);
        p->SetOffset(par[9]);

        TF1 *func;
        if (p->FixedField) {
          func = p->FitFunc; //TF1 generated in Fit(), field does not change
        }
        else { //Generate new TF1
          p->SetField();
          func = p->GetFunc();
        }
        func->SetParameter(0, par[0]);
        func->SetParameter(1, par[1]);
        func->SetParameter(2, par[2]);
        func->SetParameter(3, par[3]);
        func->SetParameter(4, par[4]);
        func->SetParameter(5, par[5]);
        func->SetParameter(6, par[6]);
        func->SetParameter(7, par[9]);

        f = p->Hist->Chisquare(func, "R");

        if (!(p->FixedField)) {delete func; }

        return;        
      }
    };

    DoubleGaussianDistr *DoubleGaussianDistr::GlobalChiSquare::p = nullptr;

    void DoubleGaussianDistr::Fit(int quiet) {
      int npars = 10;
      auto gMinuit = new TMinuit(npars);
      if (quiet) { 
        gMinuit->Command("SET PRINT -1");
      }

      // Check if the field is fixed or not
      if (FixedField) {
        SetField();
        FitFunc = new TF1("DoubleGaussianDistr", *this, Low, High, 8);
      }
      
      GlobalChiSquare func(this);
      gMinuit->SetFCN(func.minuit);

      double arglist[10];
      arglist[0] = 1;

      int ierflg = 0;

      gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
      arglist[0] = 2;
      gMinuit->mnexcm("SET STR", arglist, 1, ierflg);

      int parnum = 0;

      std::vector<std::string> parnames = {"Amp1", "Amp2", "g1", "g2", "Tau1", "Tau2", "N1N2", "mean", "FWHM", "offset"};
      std::vector<double> pars = GetPars();
      for (int i=0; i<10; ++i) {
        double min = ParLimsLow[i];
        double max = ParLimsHigh[i];
        gMinuit->mnparm(parnum, parnames[i].c_str(), pars[i], ParErrs[i], min, max, ierflg);
        ++parnum;
      }

      for (int i=0; i<10; ++i) {
        if (ParFix[i]==1) {
          gMinuit->FixParameter(i);
        }
      }

      arglist[0] = 100000;
      arglist[1] = 1;
      gMinuit->mnexcm("MINIGRAD", arglist, 2, ierflg);
      //gMinuit->mnimpr();
      //gMinuit->mnexcm("HESSE", arglist, 2, ierflg);
      //gMinuit->mnexcm("MINOS", arglist, 2, ierflg);

      ParVals.clear();
      ParErrs.clear();
      for (int i=0; i<10; ++i) {
        double parVal, parErr;
        gMinuit->GetParameter(i, parVal, parErr);
        ParVals.push_back(parVal);
        ParErrs.push_back(parErr);
      }
      SetPars();

      delete gMinuit;      
    }
  }
}
