/**
   @file
   @author Timothy Gray <timothy.gray@anu.edu.au>
   @section DESCRIPTION

   This file contains many common functions used in the formalism of angular
   correlations and distributions.
*/

#ifndef ANGDIST_HH
#define ANGDIST_HH

#include <vector>
#include <complex>
#include <functional>

#include "SolidAttenuation.hh"
#include "StatTensor.hh"

namespace GamR {
  /*!
    \addtogroup AngDist
    @{
  */

  //! Library of tools for all things angular distribution/correlation. Functions
  //! to calculate various coefficents, make R(t) functions, double-ratios, etc.
  //! etc.
  namespace AngDist {
    double Fk(double k, double jf, double lambda, double lambdaPrime, double ji);

    double Fgen(double k, double k2, double k1, double jf, double lambda, double lambdaPrime, double ji);

    double Ak(double k, double ji, double lambda, double lambdaPrime, double jf, double delta);

    double Agen(double k, double k1, double k2, double jf, double lambda, double lambdaPrime, double ji, double delta);

    std::function<std::complex<double>(double, double, double, double, double) >
    TransFrame(std::complex<double> (&Gk)(double, double, double, double, double), double alpha, double beta, double gamma);

    double W(double theta, double ji, double lambda, double lambdaPrime, double jf, double delta, StatTensor *rho,
             SolidAttenuation *Qk, double kmax = 4);

    std::vector<double> W(std::vector<double> theta, double ji, double lambda, double lambdaPrime, double jf, double delta,
                          StatTensor *rho, SolidAttenuation *Qk, double kmax = 4);

  } // namespace AngDist
  /*! @} */
} // namespace GamR

#endif // ANGDIST_HH
