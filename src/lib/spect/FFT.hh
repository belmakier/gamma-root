#ifndef GAMR_SPECT_FFT_HH
#define GAMR_SPECT_FFT_HH

#include <TH1.h>

namespace GamR {
  namespace Spect {
    enum class FFTWindow { BOX, HANN, HAMMING };

    TH1D* FFT(TH1 *hist, const char *name, double low, double high, FFTWindow window=FFTWindow::BOX);
    
  }
}

#endif
