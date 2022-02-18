#ifndef GAMROOT_SPECT_TDPAD_HH
#define GAMROOT_SPECT_TDPAD_HH

/* STD */
#include <string>
#include <vector>

/* ROOT */
#include <TF1.h>
#include <TH1.h>

/*GamR */
#include <toolkit/Gate.hh>
#include <nucleus/Transition.hh>


namespace GamR {
  namespace AngDist {
    TH1D *RatioFunction(TH1 *h1, TH1 *h2);
    TH1D *RatioFunction(TH1 *h1, TH1 *h2, const char *name);
    TH1D *RatioFunction(TH2 *h1, TH2 *h2, GamR::TK::Gate peak, GamR::TK::Gate background);
    TH1D *RatioFunction(TH2 *h1, TH2 *h2, GamR::TK::Gate peak, GamR::TK::Gate background, const char *name);
    TH1D *RatioFunction(TH2 *h1, TH2 *h2, GamR::Nucleus::Transition peak);
    TH1D *RatioFunction(TH2 *h1, TH2 *h2, GamR::Nucleus::Transition peak, const char *name);
    TH1D *AutoCorrelation(TH1 *h1);
    TH1D *AutoCorrelation(TH1 *h1, const char *name);
    TH1D *AutoCorrelation(TH1 *h1, double start, double stop);
    TH1D *AutoCorrelation(TH1 *h1, double start, double stop, const char *name);

    /** Spin precession class.  Wrapper for an R(t) TF1, but taking relevant
     * parameters such as g factor, magnetic field strength, and detector angle.
     */
    class SpinPrec {
    private:
      double gfac;
      double amp;
      double theta;
      double B;
      double mun = 5.050786;   // in J/T*1e27
      double hbar = 1.0545726; // e-7, in J.s*1e27
      double tstart;
      bool tdir;
      TF1 *func;

    public:
      SpinPrec(double g, double a, double thet, double b, double ts, bool td);
      double GetOmega() { return -gfac * mun * B / hbar * 0.01; }
      double SetTheta(double ang)
      {
        theta = ang * 3.141592 / 180;
        func->FixParameter(1, theta);
        return theta;
      }
      double SetG(double g)
      {
        gfac = g;
        func->SetParameter(2, gfac);
        return gfac;
      }
      double SetB(double b)
      {
        B = b;
        func->FixParameter(4, B);
        return B;
      }
      double SetAmp(double a)
      {
        amp = a;
        func->SetParameter(0, amp);
        return amp;
      }
      double SetTStart(double ts)
      {
        tstart = ts;
        func->FixParameter(7, tstart);
        return tstart;
      }
      bool SetTDir(bool dir)
      {
        tdir = dir;
        if (dir) {
          func->FixParameter(6, 1.0);
        } else {
          func->FixParameter(6, -1.0);
        };
        return tdir;
      }
      double GetG() { return gfac; }
      double GetAmp() { return amp; }
      double GetB() { return B; }
      double GetTheta() { return theta; }
      double GetTStart() { return tstart; }
      bool GetTDir() { return tdir; }
      TF1 *GetFunc();
    };

  } // namespace AngDist
} // namespace GamR

#endif
