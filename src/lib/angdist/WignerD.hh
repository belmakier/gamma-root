/* library to calculate Wiger D symbols */
/* following the formalism in Alder and Winther - Electromagnetic Excitation, pg
 * 311   */
/* Tim Gray - timothy.gray@anu.edu.au */
#ifndef GAMR_ANGDIST_WIGNERD_HH
#define GAMR_ANGDIST_WIGNERD_HH

#include <complex>

#include <utils/Utilities.hh>

namespace GamR {
namespace AngDist {
double djmm(double j, double m, double mprime, double beta);
std::complex<double> BigD(double j, double m, double mprime, double alpha, double beta, double gamma);
} // namespace AngDist
} // namespace GamR

#endif
