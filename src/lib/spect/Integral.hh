#ifndef GAMR_SPECT_CLICKINT_HH
#define GAMR_SPECT_CLICKINT_HH

#include <vector>

#include <TCanvas.h>
#include <TF1.h>
#include <TROOT.h>
#include <RtypesCore.h>

#include <toolkit/Gate.hh>
#include <nucleus/Transition.hh>

namespace GamR {
  namespace Spect {
    //std::vector<double, double> *ClickInt(TH1 *hist, double peakLow, double
		//		  peakHigh, double bg1Low, double bg1high);
    // TF1 *FitGaussians(TCanvas *canvas = gPad->GetCanvas(), Option_t* foption="", Option_t* option="");
    std::pair<double, double> Integral(TH1 *hist, GamR::TK::Gate peak);
    std::pair<double, double> Integral(TH1 *hist, double peakLow, double peakHigh);
    std::pair<double, double> Integral(TCanvas *canvas = gPad->GetCanvas());

    std::pair<double, double> IntegralBS(TH1 *hist, GamR::Nucleus::Transition transition);
    std::pair<double, double> IntegralBS(TH1 *hist, GamR::TK::Gate peak, GamR::TK::Gate background);
    std::pair<double, double> IntegralBS(TH1 *hist, double peakLow, double peakHigh, double backLow, double backHigh);   
    std::pair<double, double> IntegralBS(TCanvas *canvas = gPad->GetCanvas());

    std::pair<double, double> Counts(TH1 *hist, GamR::TK::Gate peak);
    std::pair<double, double> Counts(TH1 *hist, double peakLow, double peakHigh);
    std::pair<double, double> Counts(TCanvas *canvas = gPad->GetCanvas());

    std::pair<double, double> CountsBS(TH1 *hist, GamR::Nucleus::Transition transition);
    std::pair<double, double> CountsBS(TH1 *hist, GamR::TK::Gate peak, GamR::TK::Gate background);
    std::pair<double, double> CountsBS(TH1 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate> backgrounds);
    std::pair<double, double> CountsBS(TH1 *hist, double peakLow, double peakHigh, double backLow, double backHigh);
    

    std::pair<double, double> CountsBS(TCanvas *canvas = gPad->GetCanvas());
  } /* namespace Spect */  
} /* namespace GamR */

#endif //GAMR_SPECT_CLICKINT_HH
