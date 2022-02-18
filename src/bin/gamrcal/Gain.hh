#ifndef GAMRCAL_GAIN_HH
#define GAMRCAL_GAIN_HH

/* STD*/
#include <string>
#include <vector>

/* ROOT */
#include <TCanvas.h>
#include <TF1.h>
#include <TH1.h>

namespace GamR {
namespace TK {

Int_t GainMatchEnergy(TH1 *spec1, TH1 *spec2, std::vector<Double_t> &pars, bool draw = kTRUE, UInt_t target = 1,
                      std::string outfn = "", Double_t step = 0.95, TCanvas *c1 = nullptr);

} // namespace TK
} // namespace GamR

#endif
