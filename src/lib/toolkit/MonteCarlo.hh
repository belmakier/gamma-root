#ifndef GAMR_TOOLKIT_MONTECARLO_HH
#define GAMR_TOOLKIT_MONTECARLO_HH

#include <functional>
#include <memory>

#include <TCanvas.h>
#include <TH2.h>
#include <TRandom3.h>

namespace GamR {
namespace TK {

std::shared_ptr<TH2D> MonteCarlo(std::function<std::pair<double, double>(TH1 *, TRandom3 &)> func, TH1 *system,
                                 size_t ntoys, Bool_t draw = kTRUE, const Bool_t weight = kFALSE,
                                 TCanvas *c1 = nullptr);

} /* namespace TK */
} /* namespace GamR */

#endif
