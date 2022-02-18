#include <TMinuit.h>

#include "TDPAD.hh"

namespace GamR {
  namespace AngDist {
    /** \class SpinPrec

        The SpinPrec class.  Construct with

        \code{.cpp}
        GamR::AngDist::SpinPrec prec(gfac, amp, theta, B, timestart, timedir);
        \endcode

        and get the relevant TF1 (to fit) with

        \code{.cpp}
        prec.GetFunc();
        \endcode

        Only the g factor and amplitude will be free parameters in the fit. Use
        setting functions to change the parameters and/or starting guesses.  Note
        that `GetFunc()` returns a clone of the TF1 stored in the class - this way
        the parameters can only be editted through the appropriate setters.
    */

    /**
       Basic ratio function: creates and returns a TH1D formed by
       (h1-h2)/(h1+h2).  Errors are also calculated correctly. Assumes
       that h1 and h2 have the same number of bins and axis
       parameters.

       @param h1 First input histogram (i.e., a TAC or time difference spectrum)
       @param h2 Second input histogram
       @return R(t) function formed from h1 and h2.
    */
    TH1D *RatioFunction(TH1 *h1, TH1 *h2)
    {
      TH1D *ratio = new TH1D("", "", h1->GetNbinsX(), h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax());
      for (int i = 0; i < h1->GetNbinsX(); ++i) {
        double A = h1->GetBinContent(i);
        double B = h2->GetBinContent(i);

        // so ratio function is (A-B)/(A+B)
        double delA = 0;
        double delB = 0;
        if (A + B > 0) {
          delA = 2 * B / pow(A + B, 2);
          delB = 2 * A / pow(A + B, 2);
          ratio->SetBinContent(i, (A - B) / (A + B));
        }
        // error is given by sqrt((delA*σ_A)^2+(delB*σ_B)^2)
        double sigma_A = h1->GetBinError(i);
        double sigma_B = h2->GetBinError(i);
        ratio->SetBinError(i, sqrt(pow(delA * sigma_A, 2) + pow(delB * sigma_B, 2)));
      }
      return ratio;
    }

    TH1D *RatioFunction(TH1 *h1, TH1 *h2, const char *name)
    {
      TH1D *ratio = RatioFunction(h1, h2);
      ratio->SetName(name);
      return ratio;
    }

    TH1D *RatioFunction(TH2 *h1, TH2 *h2, GamR::TK::Gate peak, GamR::TK::Gate background) {
      TH1D *hTotal1      = peak.ApplyX(h1, "hTotal1");      
      TH1D *hBackground1 = background.ApplyX(h1, "hBackground1");
      TH1D *hTotal2      = peak.ApplyX(h2, "hTotal2");
      TH1D *hBackground2 = background.ApplyX(h2, "hBackground2");
      TH1D *hEnergy      = h1->ProjectionX();
      
      TH1D *hDifference = (TH1D*)hTotal1->Clone("difference");
      TH1D *hSum        = (TH1D*)hTotal1->Clone("sum");
      hDifference->Add(hTotal2, -1.);
      hSum->Add(hTotal2, 1.);
      double scale = (double)peak.GetBinWidth(hEnergy)/(double)background.GetBinWidth(hEnergy);
      hSum->Add(hBackground1, -scale);
      hSum->Add(hBackground2, -scale);
      TH1D *hRatio      = (TH1D*)hDifference->Clone("ratio_func");
      hRatio->Divide(hSum);

      int Nbins=hTotal1->GetNbinsX();
      for ( int i=1; i <=Nbins; i=i+1 ) {
        double sigT1 = hTotal1->GetBinError(i);
        double sigT2 = hTotal2->GetBinError(i);
        double sigB1 = hBackground1->GetBinError(i);
        double sigB2 = hBackground2->GetBinError(i);
        double T1    = hTotal1->GetBinContent(i);
        double T2    = hTotal2->GetBinContent(i);
        double B1    = hBackground1->GetBinContent(i);
        double B2    = hBackground2->GetBinContent(i);
        double denom = pow((T1+T2-scale*B1 - scale*B2), 2);
        if ( denom == 0 ){
          hRatio->SetBinError(i, 0);
        }
        else {
          double delT1 = ( 2*T2 - scale*B1 - scale*B2 )/denom;
          double delT2 = ( 2*T1 - scale*B1 - scale*B2 )/denom;
          double delB1 = ( scale*(T1-T2) )/denom;
          double delB2 = ( scale*(T1-T2) )/denom;
          hRatio->SetBinError(i, sqrt( pow(sigT1*delT1, 2) + pow(sigT2*delT2, 2) + pow(sigB1*delB1, 2) + pow(sigB2*delB2, 2) ) );
        }
      }
      
      delete hDifference;
      delete hSum;
      delete hTotal1;
      delete hTotal2;
      delete hBackground1;
      delete hBackground2;
      
      return hRatio;
    }

    TH1D *RatioFunction(TH2 *h1, TH2 *h2, GamR::TK::Gate peak, GamR::TK::Gate background, const char *name) {
      TH1D *hRatio = RatioFunction(h1, h2, peak, background);
      hRatio->SetName(name);
      return hRatio;
    }

    TH1D *RatioFunction(TH2 *h1, TH2 *h2, GamR::Nucleus::Transition peak) {
      TH1D *hRatio = RatioFunction(h1, h2, *(peak.GetGate()), *(peak.GetGateBG()));
      return hRatio;
    }

    TH1D *RatioFunction(TH2 *h1, TH2 *h2, GamR::Nucleus::Transition peak, const char *name) {
      TH1D *hRatio = RatioFunction(h1, h2, *(peak.GetGate()), *(peak.GetGateBG()), name);
      return hRatio;
    }
    
    /**
       Forms an autocorrelation function of the given histogram between start and
       stop values. Useful for confirming frequencies that are present in R(t)
       function data.  See https://en.wikipedia.org/wiki/Autocorrelation.

       @param h1 Input histogram
       @param start Beginning of section to be correlated
       @param start End of section to be correlated
    */
    TH1D *AutoCorrelation(TH1 *h1, double start, double stop)
    {
      int k1 = h1->FindBin(start);
      int k2 = h1->FindBin(stop);

      TH1D *out = new TH1D("", "", k2 - k1 + 1, -h1->GetBinWidth(0)/2.0, h1->GetBinLowEdge(k2) + h1->GetBinWidth(k2) - h1->GetBinLowEdge(k1) - h1->GetBinWidth(0)/2.0);
      double mean = 0;

      // find mean value
      for (int k = k1; k <= k2; ++k) {
        mean = mean + h1->GetBinContent(k);
      }
      mean = mean / (k2 - k1 + 1);

      // find normalisation constant
      double B = 0; // normalisation constant
      for (int k = k1; k <= k2; ++k) {
        B = B + (h1->GetBinContent(k) - mean) * (h1->GetBinContent(k) - mean) / (k2 - k1 + 1);
      }

      // calculate function value for each t
      for (int t = 0; t < k2 - k1; ++t) {
        double A = 0; // A is the sum
        // calculate sum from k=k1 to k=k2-t
        for (int k = k1; k <= k2 - t; ++k) {
          A = A + (h1->GetBinContent(k) - mean) * (h1->GetBinContent(k + t) - mean) / (k2 - k1 - t + 1);
        }
        double X = A / B; // normalise, X is the final value of the function
        if (X > 1) {
          // cout << "value of X = " << X << ", at t = " << t << ", with A = " << A
          // << ", and B = " << B << endl;
        }
        // fill relevant bin with correct value
        out->SetBinContent(t + 1, X);
      }
      // calculate errors
      for (int t = 0; t < k2 - k1; ++t) { // deal with each bin of (out) histogram one at a time
        // cout << "calculating error for t = " << t << endl;
        double A = 0;
        for (int k = k1; k <= k2 - t; ++k) {
          A = A + (h1->GetBinContent(k) - mean) * (h1->GetBinContent(k + t) - mean) / (k2 - k1 - t + 1);
        }
        double sigsquaredX = 0;
        for (int i = k1; i <= k2; ++i) { // need to sum error from each component (i.e. bin in h1)
          // cout << "calculating contribution from bin " << i << endl;
          double xipt;
          double ximt;
          if (k1 <= i + t && i + t <= k2 - t) {
            xipt = h1->GetBinContent(i + t); // x_{i+t}
          } else {
            xipt = 0;
          }
          if (k1 <= i - t && i - t <= k2 - t) {
            ximt = h1->GetBinContent(i - t); // x_{i-t}
          } else {
            ximt = 0;
          }
          // double xi=h1->GetBinContent(i);
          double delA = (xipt + ximt) / (k2 - k1 - t + 1);
          double delB = 0; // 2*xi/(k2-k1);
          double delX = (delA * B - delB * A) / (B * B);
          sigsquaredX = sigsquaredX + pow(delX * h1->GetBinError(i), 2);
        }
        out->SetBinError(t + 1, sqrt(sigsquaredX));
      }
      return out;
    }

    TH1D *AutoCorrelation(TH1 *h1)
    {
      return AutoCorrelation(h1, h1->GetBinCenter(1), h1->GetBinCenter(h1->GetNbinsX() - 1));
    }

    TH1D *AutoCorrelation(TH1 *h1, const char *name)
    {
      TH1D *out = AutoCorrelation(h1, h1->GetBinCenter(1), h1->GetBinCenter(h1->GetNbinsX() - 1));
      out->SetName(name);
      out->SetTitle(name);
      return out;
    }

    TH1D *AutoCorrelation(TH1 *h1, double start, double stop, const char *name)
    {
      TH1D *out = AutoCorrelation(h1, start, stop);
      out->SetName(name);
      out->SetTitle(name);
      return out;
    }

    /**
       Constructor for SpinPrec object.

       @param g g factor
       @param a amplitude of R(t)
       @param thet angle of detector (in degrees)
       @param b magnetic field strenth in Tesla
       @param ts value of x-axis at the start time
       @param td direction of positive time (kTRUE for forwards, kFALSE for
       backwards)

    */
    SpinPrec::SpinPrec(double g, double a, double thet, double b, double ts, bool td)
    {
      func = new TF1("", "[0]*cos(2.*([1] - (-[2]*[3]*[4]*0.01/[5])*[6]*(x - [7])))", 0, 8192);
      SetG(g);
      SetAmp(a);
      SetTheta(thet);
      SetB(b);
      SetTStart(ts);
      SetTDir(td);
      func->FixParameter(3, mun);
      func->FixParameter(5, hbar);
      func->SetParNames("amp", "theta", "g", "mun", "B", "hbar", "tdir", "tstart");
    }

    TF1 *SpinPrec::GetFunc()
    {
      TF1 *funcclone = (TF1 *)func->Clone();
      return funcclone;
    }


  } // namespace AngDist
} // namespace GamR
