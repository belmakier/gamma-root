/* library to calculate Wiger D symbols */
/* following the formalism in Alder and Winther - Electromagnetic Excitation, pg
 * 311   */
/* load libMathMore before compiling */
/* Tim Gray - timothy.gray@anu.edu.au */

#include <cmath>
#include <iostream>

#include "WignerD.hh"

namespace GamR {
namespace AngDist {
double djmm(double j, double m, double mprime, double beta)
/* Appendix D, equation 15 */
/* also implimented in DCOSUBS.f90 (I think) */
{
   if (j < 0 || j + mprime < 0) {
      std::cout << "Error in djmm argument" << std::endl;
      return 0;
   }
   double f1 = GamR::Utils::Fac10((int)(j + mprime));
   f1 = f1 * GamR::Utils::Fac10((int)(j - mprime));
   f1 = f1 * GamR::Utils::Fac10((int)(j + m));
   f1 = f1 * GamR::Utils::Fac10((int)(j - m));
   double root = sqrt(f1);
   double sum = 0;
   int iSigma = 0;

   double f2;
   double cosB = cos(beta / 2.0);
   double sinB = sin(beta / 2.0);
   while (1) {
      double sigma = (double)iSigma;
      if (m + mprime + sigma >= 0) {
         f2 = GamR::Utils::Fac10((int)(m + mprime + sigma));
      } else {
         iSigma = iSigma + 1;
         continue;
      }
      if (j - mprime - sigma >= 0) {
         f2 = f2 * GamR::Utils::Fac10((int)(j - mprime - sigma));
      } else
         break;
      if (j - m - sigma >= 0) {
         f2 = f2 * GamR::Utils::Fac10((int)(j - m - sigma));
      } else
         break;

      double denom = f2 * GamR::Utils::Fac10((int)sigma);
      double phase = pow(-1, j - mprime - sigma);
      double top;
      if (2 * sigma + m + mprime == 0)
         top = phase;
      else
         top = phase * pow(cosB, 2 * sigma + m + mprime);
      if (2 * j - 2 * sigma - m - mprime != 0)
         top = top * pow(sinB, 2 * j - 2 * sigma - m - mprime);

      sum = sum + top / denom;
      iSigma = iSigma + 1;
   }
   return root * sum;
}

std::complex<double> BigD(double j, double m, double mprime, double alpha, double beta, double gamma)
/* equation 12 in Alder and Winther */
{
   std::complex<double> Zi = std::complex<double>(0.0, 1.0);
   std::complex<double> Z1 = std::exp(Zi * m * alpha);
   std::complex<double> Z2 = std::exp(Zi * mprime * gamma);
   return Z1 * djmm(j, m, mprime, beta) * Z2;
}
} // namespace AngDist
} /* namespace GamR */
