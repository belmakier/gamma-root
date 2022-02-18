#ifndef GAMROOT_ANGDIST_GAUSSIANDISTR_HH
#define GAMROOT_ANGDIST_GAUSSIANDISTR_HH

/* STD */
#include <string>
#include <vector>

/* ROOT */
#include <TF1.h>
#include <TH1.h>

/*GamR */
#include <utils/Utilities.hh>
#include <toolkit/Gate.hh>
#include <nucleus/Transition.hh>

namespace GamR {
  namespace AngDist {
    class GaussianDistr {
    private:
      std::vector<double> Bhfs;
      std::vector<double> RelAmps;      
      int nSamples;
      int Limit;

      std::vector<double> ParVals;
      std::vector<double> ParLimsLow;
      std::vector<double> ParLimsHigh;
      std::vector<double> ParErrs;
      std::vector<int> ParFix;

      class GlobalChiSquare;
      
    public:
      double mean;
      double FWHM;
      double amp;
      double offset;
      double g;
      
      double Low;
      double High;

      TH1 *Hist;
      TF1 *FitFunc;
      
      int FixedField;

      GaussianDistr(double L, double H, std::vector<double> pars) : nSamples(50), Limit(20), Low(L), High(H), ParVals(pars) {
        ParLimsLow = {-1.0, -1.5, -100.0, 0.0, -100.0};
        ParLimsHigh = {1.0, 1.5, 100.0, 50.0, 100.0};
        ParFix = {0, 1, 0, 0, 0};
        ParErrs = {0.01, 0.01, 0.01, 0.01, 0.01};
        //set initial guesses into member variables
        SetPars();
        
        FixedField = 0;        
      }
      
      void Normalise();
      std::vector<double> GetBhfs() { return Bhfs; }
      std::vector<double> GetRelAmps() { return RelAmps; }
      void SetSamples(int i) { nSamples = i; }
      void SetLimit(int i) { Limit = i; }
      
      void SetAmp(double a) { amp = a; ParVals[0] = amp;}
      void SetG(double gfac) { g = gfac; ParVals[1] = g;}
      void SetMean(double m) { mean = m; ParVals[2] = mean;}
      void SetFWHM(double w) { FWHM = w; ParVals[3] = FWHM;}
      void SetOffset(double o) { offset = o; ParVals[4] = offset;}
      void SetHist(TH1* hist) { Hist = hist; }

      void SetField();

      double GetG() { return g; }
      double GetGErr() { return ParErrs[1]; }
      double GetAmp() { return amp; }
      double GetAmpErr() { return ParErrs[0]; }
      double GetMean() { return mean; }
      double GetMeanErr() { return ParErrs[2]; }
      double GetFWHM() { return FWHM; }
      double GetFWHMErr() { return ParErrs[3]; }
      double GetOffset() { return offset; }
      double GetOffsetErr() { return ParErrs[4]; }

      void FixField() { ParFix[2] = 1; ParFix[3] = 1; FixedField = 1;}
      void UnFixField() { ParFix[2] = 0; ParFix[3] = 0; FixedField = 0;}
      void FixG() { ParFix[1] = 1; }
      void UnFixG() { ParFix[1] = 0; }
      void FixAmp() { ParFix[0] = 1; }
      void UnFixAmp() { ParFix[0] = 1; }
      void FixOffset() { ParFix[4] = 1; }
      void UnFixOffset() { ParFix[4] = 0; }
      std::vector<double> GetPars() { return ParVals; }
      void SetPars() { SetPars(ParVals); }
      void SetPars(std::vector<double> pars) { ParVals = pars; amp = pars[0]; g = pars[1]; mean = pars[2]; FWHM = pars[3]; offset = pars[4]; }
      
      double RatioFunc(double x, double a, double gfac, double off);
      double operator()(double *x, double *p);
      TF1* GetFunc();

      void Fit(int quiet);

      void Print() {
        std::cout << "      g        amp       offset      Bhf       FWHM   " << std::endl;
        std::cout << GamR::Utils::wrresult(GetG(), GetGErr()) << "    "
                  << GamR::Utils::wrresult(GetAmp(), GetAmpErr()) << "    "
                  << GamR::Utils::wrresult(GetOffset(), GetOffsetErr()) << "    "
                  << GamR::Utils::wrresult(GetMean(), GetMeanErr()) << "    "
                  << GamR::Utils::wrresult(GetFWHM(), GetFWHMErr()) << "    " << std::endl;
      }
        
      
    };

    class DoubleGaussianDistr { // this is for two precessions overlayed, same field
    private:
      std::vector<double> Bhfs;
      std::vector<double> RelAmps;      
      int nSamples;
      int Limit;

      std::vector<double> ParVals;
      std::vector<double> ParLimsLow;
      std::vector<double> ParLimsHigh;
      std::vector<double> ParErrs;
      std::vector<int> ParFix;

      class GlobalChiSquare;
      
    public:
      double amp1;
      double amp2;
      double g1;
      double g2;
      double tau1;
      double tau2;
      double n1n2;
      double mean;
      double FWHM;
      double offset;
      
      double Low;
      double High;

      TH1 *Hist;
      TF1 *FitFunc;

      int FixedField;

      DoubleGaussianDistr(double L, double H, std::vector<double> pars) : nSamples(50), Limit(20), Low(L), High(H), ParVals(pars) {
        ParLimsLow = {-1.0, -1.0, -1.5, -1.5, 0.0, 0.0, 0.0, -100.0, 0.0, -100.0};
        ParLimsHigh = {1.0, 1.0, 1.5, 1.5, 1000.0, 1000.0, 2.0, 100.0, 50.0, 100.0};
        ParFix = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        ParErrs = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01};
        SetPars();
        FixedField = 0;
      }
      
      void Normalise();
      std::vector<double> GetBhfs() { return Bhfs; }
      std::vector<double> GetRelAmps() { return RelAmps; }
      void SetSamples(int i) { nSamples = i; }
      void SetLimit(int i) { Limit = i; }
      void SetAmp1(double a) { amp1 = a; ParVals[0] = amp1; }
      void SetAmp2(double a) { amp2 = a; ParVals[1] = amp2; }
      void SetG1(double gfac) { g1 = gfac; ParVals[2] = g1; }
      void SetG2(double gfac) { g2 = gfac; ParVals[3] = g2;}
      void SetTau1(double tau) { tau1 = tau; ParVals[4] = tau1;}
      void SetTau2(double tau) { tau2 = tau; ParVals[5] = tau2;}
      void SetN1N2(double n) { n1n2 = n; ParVals[6] = n1n2;}
      void SetMean(double m) { mean = m; ParVals[7] = mean;}
      void SetFWHM(double w) { FWHM = w; ParVals[8] = FWHM;}
      void SetOffset(double o) { offset = o; ParVals[9] = offset;}
      void SetHist(TH1* hist) { Hist = hist; }
      void SetField();

      double GetG1() { return g1; }
      double GetG1Err() { return ParErrs[2]; }
      double GetG2() { return g2; }
      double GetG2Err() { return ParErrs[3]; }
      double GetAmp1() { return amp1; }
      double GetAmp1Err() { return ParErrs[0]; }
      double GetAmp2() { return amp2; }
      double GetAmp2Err() { return ParErrs[1]; }
      double GetTau1() { return tau1; }
      double GetTau1Err() { return ParErrs[4]; }
      double GetTau2() { return tau2; }
      double GetTau2Err() { return ParErrs[5]; }
      double GetN1N2() { return n1n2; }
      double GetN1N2Err() { return ParErrs[6]; }
      double GetMean() { return mean; }
      double GetMeanErr() { return ParErrs[7]; }
      double GetFWHM() { return FWHM; }
      double GetFWHMErr() { return ParErrs[8]; }
      double GetOffset() { return offset; }
      double GetOffsetErr() { return ParErrs[9]; }

      void FixField() { ParFix[7] = 1; ParFix[8] = 1; FixedField = 1;}
      void UnFixField() { ParFix[7] = 0; ParFix[8] = 0; FixedField = 0;}
      void FixG1() { ParFix[2] = 1; }
      void UnFixG1() { ParFix[2] = 0; }
      void FixG2() { ParFix[3] = 1; }
      void UnFixG2() { ParFix[3] = 0; }
      void FixAmp1() { ParFix[0] = 1; }
      void UnFixAmp1() { ParFix[0] = 1; }
      void FixAmp2() { ParFix[1] = 1; }
      void UnFixAmp2() { ParFix[1] = 1; }
      void FixTau1() { ParFix[4] = 1; }
      void UnFixTau1() { ParFix[4] = 1; }
      void FixTau2() { ParFix[5] = 1; }
      void UnFixTau2() { ParFix[5] = 1; }
      void FixN1N2() { ParFix[6] = 1; }
      void UnFixN1N2() { ParFix[7] = 1; }
      void FixOffset() { ParFix[9] = 1; }
      void UnFixOffset() { ParFix[9] = 0; }
      std::vector<double> GetPars() { std::vector<double> pars = { amp1, amp2, g1, g2, tau1, tau2, n1n2,  mean, FWHM, offset }; return pars; }

      void SetPars() { SetPars(ParVals); }
      void SetPars(std::vector<double> pars) { ParVals = pars; amp1 = pars[0]; amp2 = pars[1]; g1 = pars[2]; g2 = pars[3]; tau1 = pars[4]; tau2 = pars[5]; n1n2 = pars[6]; mean = pars[7]; FWHM = pars[8]; offset = pars[9]; }

      void SetParLimits(int i, double low, double high) { ParLimsLow[i] = low; ParLimsHigh[i] = high; }
      
      double RatioFunc(double x, double a1, double a2, double gfac1, double gfac2, double t1, double t2, double n, double off);
      double operator()(double *x, double *p);
      TF1* GetFunc();

      void Fit(int quiet);

      void Print() {
        std::cout << "g1       " << GamR::Utils::wrresult(GetG1(), GetG1Err()) << std::endl;
        std::cout << "g2       " << GamR::Utils::wrresult(GetG2(), GetG2Err()) << std::endl;
        std::cout << "amp1       " << GamR::Utils::wrresult(GetAmp1(), GetAmp1Err()) << std::endl;
        std::cout << "amp2       " << GamR::Utils::wrresult(GetAmp2(), GetAmp2Err()) << std::endl;
        std::cout << "tau1       " << GamR::Utils::wrresult(GetTau1(), GetTau1Err()) << std::endl;
        std::cout << "tau2       " << GamR::Utils::wrresult(GetTau2(), GetTau2Err()) << std::endl;
        std::cout << "n1/n2      " << GamR::Utils::wrresult(GetN1N2(), GetN1N2Err()) << std::endl;
        std::cout << "Bhf        " << GamR::Utils::wrresult(GetMean(), GetMeanErr()) << std::endl;
        std::cout << "FWHM       " << GamR::Utils::wrresult(GetFWHM(), GetFWHMErr()) << std::endl;
        std::cout << "Offset     " << GamR::Utils::wrresult(GetOffset(), GetOffsetErr()) << std::endl;
      } 
      
    };
    
  } // namespace AngDist
} // namespace GamR

#endif
