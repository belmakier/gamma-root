#ifndef GAMR_SPECT_CUT_HH
#define GAMR_SPECT_CUT_HH

#include <memory>
#include <vector>

#include <TCanvas.h>
#include <TH2.h>
#include <TCutG.h>
#include <TSpectrum2.h>

#include <utils/Utilities.hh>
#include <toolkit/Gate.hh>
#include <nucleus/Transition.hh>

namespace GamR {
  namespace Spect {

    TH1D *ProjX(TH2 *hist, const char *name);
    TH1D *ProjX(TH2 *hist);
    TH1D *ProjX(TVirtualPad *canvas, const char *name);
    TH1D *ProjX(TVirtualPad *canvas);

    TH1D *ProjY(TH2 *hist, const char *name);
    TH1D *ProjY(TH2 *hist);
    TH1D *ProjY(TVirtualPad *canvas, const char *name);
    TH1D *ProjY(TVirtualPad *canvas);
    
    TH1D *GateX(TH2 *hist, GamR::TK::Gate peak, const char *name);
    TH1D *GateX(TH2 *hist, GamR::TK::Gate peak);
    TH1D *GateX(TCanvas *canvas, const char *name);
    TH1D *GateX(TCanvas *canvas);

    TH1D *GateY(TH2 *hist, GamR::TK::Gate peak, const char *name);
    TH1D *GateY(TH2 *hist, GamR::TK::Gate peak);
    TH1D *GateY(TCanvas *canvas, const char *name);
    TH1D *GateY(TCanvas *canvas);
    
    TH1D *BackgroundSubtractX(TH2 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background, const char *name);
    TH1D *BackgroundSubtractX(TH2 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background);
    TH1D *BackgroundSubtractX(TH2 *hist, GamR::TK::Gate peak, GamR::TK::Gate background, const char *name);
    TH1D *BackgroundSubtractX(TH2 *hist, GamR::TK::Gate peak, GamR::TK::Gate background);
    TH1D *BackgroundSubtractX(TH2 *hist, GamR::Nucleus::Transition peak, const char *name);
    TH1D *BackgroundSubtractX(TH2 *hist, GamR::Nucleus::Transition peak);
    TH1D *BackgroundSubtractX(TCanvas *canvas, const char *name);
    TH1D *BackgroundSubtractX(TCanvas *canvas);

    TH1D *BackgroundSubtractY(TH2 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate >background, const char *name);
    TH1D *BackgroundSubtractY(TH2 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate >background);
    TH1D *BackgroundSubtractY(TH2 *hist, GamR::TK::Gate peak, GamR::TK::Gate background, const char *name);
    TH1D *BackgroundSubtractY(TH2 *hist, GamR::TK::Gate peak, GamR::TK::Gate background);
    TH1D *BackgroundSubtractY(TH2 *hist, GamR::Nucleus::Transition peak, const char *name);
    TH1D *BackgroundSubtractY(TH2 *hist, GamR::Nucleus::Transition peak);
    TH1D *BackgroundSubtractY(TCanvas *canvas, const char *name);
    TH1D *BackgroundSubtractY(TCanvas *canvas);

    TH2D *BackgroundSubtract2D(TH2 *peak, TH2 *background, double scale);

    TCutG *DrawCut(TVirtualPad *canvas, bool verbose=false, std::string filename="", int ID=-1);
    TCutG *DrawCut(std::string cutfile, int ID, TVirtualPad *canvas);

    void PrintCut(TCutG *cut);

    std::shared_ptr<TH2D> BackgroundEstimate(const TH2 *hist, Int_t NiterX = 4, Int_t NiterY = 4,
                                             Int_t direction = TSpectrum2::kBackIncreasingWindow,
                                             Int_t filtertype = TSpectrum2::kBackOneStepFiltering);

  } // namespace Spect
} // namespace GamR


#endif
