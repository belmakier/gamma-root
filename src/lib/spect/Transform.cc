/* ROOT */
#include <TMath.h>
#include <TRandom3.h>

#include <utils/Utilities.hh>
#include <toolkit/Gate.hh>
#include "Transform.hh"
#include "Display.hh"

namespace GamR {
  namespace Spect {

    /**
     * @brief Scales a histogram along the X axis and dithers to avoid
     * quantization errors.
     *
     * @param h Input histogram
     * @param f Function
     * @return Scaled copy of histogram
     */
    TH1D Scale(const TH1 *h, TFormula f)
    {
      TRandom3 dither(0430204771);
      TH1D newhist;
      newhist.SetBins(h->GetNbinsX(), f.Eval(h->GetXaxis()->GetXmin()), f.Eval(h->GetXaxis()->GetXmax()));
      for (int i = 0; i < h->GetNbinsX(); ++i) {
        for (int c = 0; c < h->GetBinContent(i); ++c) {
          auto x = h->GetXaxis()->GetBinLowEdge(i) + dither.Rndm() * h->GetXaxis()->GetBinWidth(i);
          newhist.Fill(f.Eval(x));
        }
      }
      return newhist;
    }

    /**
     * @brief Scales histogram by a polynomial.
     *
     *  If first order, use GamR::Spect::ScaleLabelsLinear to avoid a
     *  significant amount overhead.
     *
     * @param h Input histogram
     * @param pars Polynomial coefficients (zeroth = constant)
     * @return Scaled copy of histogram
     */
    TH1D ScalePoly(const TH1 *h, std::vector<Double_t> pars)
    {
      std::string funcstr = "pol" + std::to_string(pars.size() - 1);
      TFormula f("func", funcstr.c_str());
      for (size_t n = 0; n < pars.size(); ++n) {
        f.SetParameter(n, pars[n]);
      }
      f.Print();
      return Scale(h, f);
    }

    /**
     * @brief Scales the labels of a histogram. Preferable over GamR::Spect::Scale
     * and GamR::Spect::ScalePoly as it avoids having to regenerate the histogram.
     *
     * @param h Histogram to be scaled.
     * @param m First derivative / Gain
     * @param c Shift / Offset
     */
    void ScaleLabelsLinear(TH1 *h, Double_t m, Double_t c)
    {
      auto y = [&](Double_t x) { return m * x + c; };
      auto xlo = h->GetXaxis()->GetXmin();
      auto xhi = h->GetXaxis()->GetXmax();
      h->GetXaxis()->SetLimits(y(xlo), y(xhi));
      return;
    }

    /**
       Shifts the contents of a histogram (in place) by a specified
       number of bins

       @param h Histogram to be acted upon
       @param shift Number of bins to shift contents (positive = right shift)
    */
    void Shift(TH1 &h, Int_t shift)
    {
      if (shift == 0) {
        return;
      } else if (shift > 0) // go from high to low
        {
          for (int i = h.GetNbinsX(); i > shift; --i) {
            h.SetBinContent(i, h.GetBinContent(i - shift));
            h.SetBinError(i, h.GetBinError(i - shift));
          }
          for (int i = shift; i >= 0; --i) {
            h.SetBinContent(i, 0);
            h.SetBinError(i, 0);
          }
        } else if (shift < 0) // go from low to high
        {
          for (int i = 0; i < h.GetNbinsX() + shift; ++i) {
            h.SetBinContent(i, h.GetBinContent(i - shift));
            h.SetBinError(i, h.GetBinError(i - shift));
          }
          for (int i = h.GetNbinsX() + shift; i < h.GetNbinsX(); ++i) {
            h.SetBinContent(i, 0);
            h.SetBinError(i, 0);
          }      
        }
      return;
    }

    /**
       Function to add two histograms with correct error handling

       Note that the histograms should be of the same dimension.
       Errors are added in quadrature

       @param hist1 First histogram
       @param hist2 Second histogram
       @param name Name of the output histogram
       @param c1 Weight for hist1
       @param c2 Weight for hist2
       @return c1*hist1 + c2*hist2
    */
    TH1D *Add(TH1 *hist1, TH1 *hist2, const char *name, double c1 /*=1.0*/, double c2 /*=1.0*/)
    {
      TH1D *out = (TH1D *)hist1->Clone(name);
      out->Add(hist1, hist2, c1, c2);
      for (int i = 0; i < hist1->GetNbinsX(); ++i) {
        out->SetBinError(i, sqrt(pow(c1 * hist1->GetBinError(i), 2) + pow(c2 * hist2->GetBinError(i), 2)));
      }
      return out;
    }

    TH1D *Add(std::vector<TH1*> hists, const char *name) {
      if (hists.size() == 0) { return NULL; }
      TH1D *out = (TH1D *)hists[0]->Clone(name);
      for (int i=1; i<hists.size(); ++i) {
        out->Add(hists[i], 1);
      }
      return out;
    }

    TH1D *Add(std::vector<int> hists, const char *name) {
      auto spectra = List1DSpectra(true);
      std::vector<TH1*> sum_spectra;
      for (auto &i : hists) {
        sum_spectra.push_back(spectra[i]);
      }
      return Add(sum_spectra, name);
    }

    TH1D *Add(int iStart, int iStop, const char *name) {
      auto spectra = List1DSpectra(true);
      std::vector<TH1*> sum_spectra;
      for (int i=iStart; i<=iStop; ++i) {
        sum_spectra.push_back(spectra[i]);
      }
      return Add(sum_spectra, name);
    }

    /**
       Function to add two histograms with correct error handling

       Note that the histograms should be of the same dimension.
       Errors are added in quadrature

       @param hist1 First histogram
       @param hist2 Second histogram
       @param name Name of the output histogram
       @param c1 Weight for hist1
       @param c2 Weight for hist2
       @return c1*hist1 + c2*hist2
    */
    TH2D *Add(TH2 *hist1, TH2 *hist2, const char *name, double c1 /*=1.0*/, double c2 /*=1.0*/)
    {
      TH2D *out = (TH2D *)hist1->Clone(name);
      out->Add(hist1, hist2, c1, c2);
      for (int i = 0; i < hist1->GetNbinsX(); ++i) {
        for (int j = 0; j < hist1->GetNbinsY(); ++j) {
          out->SetBinError(i, j, sqrt(pow(c1 * hist1->GetBinError(i, j), 2) + pow(c2 * hist2->GetBinError(i, j), 2)));
        }
      }
      return out;
    } /*Add*/

    TH2D *Add(std::vector<TH2*> hists, const char *name) {
      if (hists.size() == 0) { return NULL; }
      TH2D *out = (TH2D*)hists[0]->Clone(name);
      for (int i=1; i<hists.size(); ++i) {
        out->Add(hists[i], 1);
      }
      return out;
    }

    TH2D *Add2(std::vector<int> hists, const char *name) {
      auto spectra = List2DSpectra(true);
      std::vector<TH2*> sum_spectra;
      for (auto &i : hists) {
        sum_spectra.push_back(spectra[i]);
      }
      return Add(sum_spectra, name);
    }

    TH2D *Add2(int iStart, int iStop, const char *name) {
      auto spectra = List2DSpectra(true);
      std::vector<TH2*> sum_spectra;
      for (int i=iStart; i<=iStop; ++i) {
        sum_spectra.push_back(spectra[i]);
      }
      return Add(sum_spectra, name);
    }
    
    /**
       Function to multiply a histogram with correct error handling

       Errors are multiplied by the same constant

       @param hist1 Histogram input
       @param name Name of the output histogram
       @param c1 Factor to multiply
       @return c1*hist1
    */
    TH1D *Multiply(TH1 *hist1, const char *name, double c1 /*= 1.0*/) {
      TH1D *out = (TH1D*)hist1->Clone(name);
      out->Scale(c1);
      for (int i=0; i < hist1->GetNbinsX(); ++i) {
        out->SetBinError(i, c1*hist1->GetBinError(i));
      }
      return out;
    }
  
    /**
       Reverses histogram in place (flips X-axis).  Since in ROOT axis
       cannot run backwards, the axis labels are not changed.

       @param h Histogram to be acted upon
       @return Reversed histogram
    */
    void Reverse(TH1 *h)
    {
      TH1D *clone = (TH1D *)h->Clone();
      for (int i = 0; i < h->GetNbinsX(); ++i) {
        h->SetBinContent(i, clone->GetBinContent(h->GetNbinsX() - i));
        h->SetBinError(i, clone->GetBinError(h->GetNbinsX() - i));
      }
      return;
    }

    /** rotates TH2 spectrum anticlocwise by angle (degrees) applying the optional
        cut of bananaGate if required.
        @param hist Histogram to be rotated
        @param angle Angle to rotate by
        @param name Name of output histogram
        @param bananaGate Optional TCutG cut
        @return Rotated histogram
    */

    TH2D *RotateTH2(TH2 *hist, float angle, const char *name, TCutG *bananaGate /*=0*/)
    {
      TRandom3 random;

      int iMax = hist->GetNbinsX();
      int jMax = hist->GetNbinsY();

      float xMin = ((TAxis *)hist->GetXaxis())->GetXmin();
      float xMax = ((TAxis *)hist->GetXaxis())->GetXmax();
      float yMin = ((TAxis *)hist->GetYaxis())->GetXmin();
      float yMax = ((TAxis *)hist->GetYaxis())->GetXmax();

      float cosangle = TMath::Cos(angle * TMath::Pi() / 180.);
      float sinangle = TMath::Sin(angle * TMath::Pi() / 180.);

      int nOutX = iMax * cosangle + jMax * sinangle;
      int nOutY = iMax * sinangle + jMax * cosangle;

      TH2D *out_h = new TH2D(name, name, nOutX, xMin * cosangle - yMax * sinangle, xMax * cosangle - yMin * sinangle,
                             nOutY, xMin * sinangle + yMin * cosangle, xMax * sinangle + yMax * cosangle);
      // TH1D *out_h = new TH1D(name, name, iMax, xMin*cosangle - yMax*sinangle,
      // xMax*cosangle - yMin*sinangle);
      float binWidthX = ((TAxis *)hist->GetXaxis())->GetBinCenter(1) - ((TAxis *)hist->GetXaxis())->GetBinCenter(0);
      float binWidthY = ((TAxis *)hist->GetYaxis())->GetBinCenter(1) - ((TAxis *)hist->GetYaxis())->GetBinCenter(0);

      for (int i = 0; i < iMax; i++) {
        for (int j = 0; j < jMax; j++) {
          float x = ((TAxis *)hist->GetXaxis())->GetBinCenter(i);
          float y = ((TAxis *)hist->GetYaxis())->GetBinCenter(j);

          if (bananaGate) {
            if (!bananaGate->IsInside(x, y)) {
              continue;
            }
          }
          /* do rotation + projection */

          for (int w = 1; w <= hist->GetBinContent(i, j); w++) {
            float xRan = x + (random.Rndm() - 0.5) * binWidthX;
            float yRan = y + (random.Rndm() - 0.5) * binWidthY;
            float projX = xRan * cosangle - yRan * sinangle;
            float projY = xRan * sinangle + yRan * cosangle;

            out_h->Fill(projX, projY);
          }
        }
      }

      return out_h;
    }

    TH1 *Rebin(TH1 *hist, int rebin) {
      hist->Rebin(rebin);
      return hist;
    }

    TH2 *RebinX(TH2 *hist, int rebin) {
      hist->RebinX(rebin);
      return hist;
    }

    TH2 *RebinY(TH2 *hist, int rebin) {
      hist->RebinY(rebin);
      return hist;
    }

    void RebinX(TVirtualPad *canvas, int rebin) {
      if (!canvas) { if (!gPad) { return; } canvas = gPad; }

      int nPads = GamR::Utils::GetNPads(canvas);
      
      if (!nPads) {
        TH2D* hist = GamR::Utils::GetHist2D(canvas);
        GamR::Spect::RebinX(hist, rebin);
        canvas->Modified();
      }      
      
      for (int i=0; i<nPads; ++i) {
        canvas->cd(i+1);
        RebinX(canvas->cd(i+1), rebin);
      }
      canvas->Modified();
      canvas->cd();
    }
    
    void RebinY(TVirtualPad *canvas, int rebin) {
      if (!canvas) { if (!gPad) { return; } canvas = gPad; }

      int nPads = GamR::Utils::GetNPads(canvas);
      
      if (!nPads) {
        TH2D* hist = GamR::Utils::GetHist2D(canvas);
        GamR::Spect::RebinY(hist, rebin);
        canvas->Modified();
      }      
      
      for (int i=0; i<nPads; ++i) {
        canvas->cd(i+1);
        RebinY(canvas->cd(i+1), rebin);
      }
      canvas->Modified();
      canvas->cd();
    }

    void Rebin(TVirtualPad *canvas, int rebin) {
      if (!canvas) { if (!gPad) { return; } canvas = gPad; }

      int nPads = GamR::Utils::GetNPads(canvas);
      
      if (!nPads) {
        std::vector<TH1D*> hists = GamR::Utils::GetHists1D(canvas);
        if (hists.size() > 0) {
          for (int i=0; i<hists.size(); ++i) {
            GamR::Spect::Rebin(hists[i], rebin);
          }
          canvas->Modified();
        }
      }      
      
      for (int i=0; i<nPads; ++i) {
        canvas->cd(i+1);
        Rebin(canvas->cd(i+1), rebin);
      }
      canvas->Modified();
      canvas->cd();
    }

    void Norm(TH1 *hist, TH1 *ref, double low, double high) {
      GamR::TK::Gate gate(low, high);
      gate.Norm(hist, ref);
    }

    void NormBackSub(TH1 *hist, TH1 *ref, double low, double high, double backlow, double backhigh) {
      GamR::TK::Gate gate(low, high);
      GamR::TK::Gate back(backlow, backhigh);
      gate.NormBackSub(hist, ref, back);
    }
  } // namespace Spect
} // namespace GamR
