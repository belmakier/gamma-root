/**
   @file
   @author Timothy Gray <timothy.gray@anu.edu.au>
   @section DESCRIPTION
   
   This file contains wrappers for calculating angular correlations

*/

#ifndef ANGCORR_HH
#define ANGCORR_HH

#include <vector>

#include <TMath.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h> 
#include <Math/SpecFunc.h> /* legendre polynomials, 3j and 6j symbols */

#include <nucleus/Transition.hh>
#include <angdist/AngDist.hh>

namespace GamR {
  namespace AngDist {
    
    class AngCorr {
      /**
         This is a wrapper for Fk and Ak coefficients for use in angular correlations for a cascade between 3 states.  It's designed to be used to construct TF1 objects which can then be plotted, and fitted
      */
    public:
      double spin1;
      double spin2;
      double spin3;

      GamR::AngDist::SolidAttenuation *Qk;
      /**
         Constructor for AngCorr object

         @param spin1 Initial spin
         @param spin2 Intermediate spin
         @param spin3 Final spin
      */
      AngCorr(double spin1, double spin2, double spin3)
      {
        this->spin1 = spin1;
        this->spin2 = spin2;
        this->spin3 = spin3;
        std::vector<double> Qks = {1.0, 1.0, 1.0, 1.0, 1.0};
        this->Qk = new GamR::AngDist::SolidAttenuation(Qks);
      }
      AngCorr(double spin1, double spin2, double spin3, GamR::AngDist::SolidAttenuation* Q)
      {
        this->spin1 = spin1;
        this->spin2 = spin2;
        this->spin3 = spin3;
        this->Qk = Q;
      }
      double Ak(double k, double delta1, double delta2);
      double operator() (double *x, double *p)
      {
        double theta = x[0]*TMath::Pi()/180.0;
        double a2 = Ak(2.0, p[1], p[2]);
        double a4 = Ak(4.0, p[1], p[2]);
        return p[0]*(1+Qk->Get(2)*a2*ROOT::Math::legendre(2, cos(theta))+Qk->Get(4)*a4*ROOT::Math::legendre(4, cos(theta)));
      }
      int Mixed(double s1, double s2);
      int Mixed(int i);
      int Mixed1() { return Mixed(spin1, spin2); }
      int Mixed2() { return Mixed(spin2, spin3); }
    };

    class AngCorrFit : public TNamed {
      /** 
          A wrapper for the AngCorr class to contain TGraphErrors to fit to as well
      */
    public:
      std::vector<Color_t> fColors;
      
      std::vector<double> spin1s;
      std::vector<double> spin2s;
      std::vector<double> spin3s;

      std::vector<double> fAngles;
      std::vector<double> fIntensities;
      std::vector<double> fErrors;

      std::vector<AngCorr*> fCorrs;
      std::vector<TF1*> fCorrFuncs;
      std::vector<TGraph*> fChiGraphs;

      std::vector<double> fDelta1;
      std::vector<double> fDelta2;
      std::vector<std::pair<double,double> > fDelta1Err;
      std::vector<std::pair<double,double> > fDelta2Err;
      std::vector<double> fChiSquared;

      std::vector<double> fixDelta;//[2];
      std::vector<int> fDel;//[2];

      GamR::AngDist::SolidAttenuation *Qk;
      
    public:
      void SetData(std::vector<double> angs, std::vector<TH2D*> hists, GamR::Nucleus::Transition peak1, GamR::Nucleus::Transition peak2, TH1D *angNorm);
      void SetSpins(std::vector<double> s1s, std::vector<double> s2s, std::vector<double> s3s) { spin1s = s1s; spin2s = s2s; spin3s = s3s; }
      void SetQk(GamR::AngDist::SolidAttenuation *Q) { delete Qk; Qk = Q; };
      
      AngCorrFit(std::vector<double> angs, std::vector<TH2D*> hists, GamR::Nucleus::Transition peak1, GamR::Nucleus::Transition peak2, TH1D *angNorm, const char *name, const char *title);
      AngCorrFit(std::vector<double> angs, std::vector<TH2D*> hists, GamR::Nucleus::Transition peak1, GamR::Nucleus::Transition peak2, TH1D *angNorm);

      void FixDel1(double delta) { fixDelta[0] = delta; fDel[0] = 1; }
      void FixDel2(double delta) { fixDelta[1] = delta; fDel[1] = 1; }
      
      int GetNPoints() {return fAngles.size(); }
      int GetNCombs() {return fCorrs.size(); }
      void ErasePoint(double ang);
      double Average();      
      TGraphErrors *GetGraph();
      TGraphErrors *GetDispGraph(double start, double interval);

      void Fit(); 
      TMultiGraph* GetChiGraph();

      void DrawChiGraph(TCanvas *c1, double ylow, double yhigh);
      void DrawAngCorr(TCanvas *c1, double start, double interval);
      void PrintDelta1(int i) { std::cout << "Delta 1 = " << fDelta1[i] << " +" << fDelta1Err[i].second << "/-" << -fDelta1Err[i].first << std::endl;}
      void PrintDelta2(int i) { std::cout << "Delta 2 = " << fDelta2[i] << " +" << fDelta2Err[i].second << "/-" << -fDelta2Err[i].first << std::endl;}
      void Save(std::string filename, double start, double interval);
      void SaveChiGraph(std::string filename);

      ClassDef(AngCorrFit, 1);
    };      
  }
}
#endif
