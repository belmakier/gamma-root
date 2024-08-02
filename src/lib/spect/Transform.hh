#ifndef GAMROOT_SPECT_TRANSFORM_HH
#define GAMROOT_SPECT_TRANSFORM_HH

/* STD */
#include <string>
#include <vector>

/* ROOT */
#include <TCutG.h>
#include <TFormula.h>
#include <TH1.h>
#include <TH2.h>
#include <TVirtualPad.h>

namespace GamR {
/*!
  \addtogroup Spect
  @{
*/

//! Library of tools spectroscopy tools - transforming histograms, fitting
//! peaks, doing cuts and background subtractions etc.
  namespace Spect {

    TH1D Scale(const TH1 *h, TFormula f);
    TH1D ScalePoly(const TH1 *h, std::vector<Double_t> pars);
    void ScaleLabelsLinear(TH1 *h, Double_t m, Double_t c);
    void Shift(TH1 &h, Int_t shift);
    TH1D *Add(TH1 *hist1, TH1 *hist2, const char *name, double c1 = 1, double c2 = 1);
    TH1D *Add(std::vector<TH1*> hists, const char *name);
    TH1D *Add(std::vector<int> hists, const char *name);
    TH1D *Add(int iStart, int iStop, const char *name);
    TH2D *Add(TH2 *hist1, TH2 *hist2, const char *name, double c1 = 1, double c2 = 1);
    TH2D *Add(std::vector<TH2*> hists, const char *name);
    TH2D *Add2(std::vector<int> hists, const char *name);
    TH2D *Add2(int iStart, int iStop, const char *name);
    TH1 *Rebin(TH1 *hist, int rebin);
    void Rebin(TVirtualPad *canvas, int rebin);
    TH2 *RebinX(TH2 *hist, int rebin);
    void RebinX(TVirtualPad *canvas, int rebin);
    TH2 *RebinY(TH2 *hist, int rebin);
    void RebinY(TVirtualPad *canvas, int rebin);
    TH1D *Multiply(TH1 *hist1, const char *name, double c1 = 1);
    void Reverse(TH1 *h);
    TH2D *RotateTH2(TH2 *hist, float angle, const char *name, TCutG *bananaGate = 0);
    void Norm(TH1 *hist, TH1* ref, double low, double high);
    void NormBackSub(TH1 *hist, TH1* ref, double low, double high, double backlow, double backhigh);
  } // namespace Spect
  /*! @} */
} // namespace GamR

#endif
