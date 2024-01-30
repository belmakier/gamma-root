#ifndef GAMR_SPECT_CALIBRATE_HH
#define GAMR_SPECT_CALIBRATE_HH

namespace GamR {
  namespace Spect {
    std::pair<double, double> TwoPointCalibrate(TVirtualPad *canvas, double sigma=2);
    std::pair<double, double> TwoPointCalibrate(TH1 *hist, double lowEst, double highEst, double lowEn, double highEn, double sigma=2);
    std::pair<double, double> TwoPointCalibrate(TVirtualPad *canvas, double lowEn, double highEn, double sigma=2);
    std::pair<double, double> TwoClickCalibrate(TVirtualPad *canvas);
    
  }
}


#endif
