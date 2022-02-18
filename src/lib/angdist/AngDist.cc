/**
   @file
   @author Timothy Gray <timothy.gray@anu.edu.au>
   @section DESCRIPTION

   Library to calculate angular distributions/correlations, following the
   formalism in Morinaga and Yamazaki - In-Beam Gamma-Ray Spectroscopy, amongst
   other references.

   This file contains many common functions used in the formalism of angular
   correlations and distributions.
*/

/* C++ */
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

/* CERN ROOT */
#include <Math/SpecFunc.h> /* legendre polynomials, 3j and 6j symbols */

#include "AngDist.hh"
#include "WignerD.hh"

namespace GamR {
namespace AngDist {

/**
   Fk coefficients - see Equation 2.42, or 12.168 in Hamilton
*/
double Fk(double k, double jf, double lambda, double lambdaPrime, double ji)
{
   return pow((-1), -1 + ji + jf) * pow((2 * lambda + 1) * (2 * lambdaPrime + 1) * (2 * ji + 1) * (2 * k + 1), 0.5) *
          ROOT::Math::wigner_3j((int)(2 * lambda), (int)(2 * lambdaPrime), (int)(2 * k),
                                2, -2, 0) *
          ROOT::Math::wigner_6j((int)(2 * ji), (int)(2 * ji), (int)(2 * k),
                                (int)(2 * lambdaPrime), (int)(2 * lambda), (int)(2 * jf));
}

/**
   Generalised Fk coefficients - see Equation 12.163 in Hamilton

   @param k lambda
   @param k2 lambda_1
   @param k1 lambda_0
   @param jf I1
   @param ji I0
   @param lambda L
   @param lambdaPrime L'
*/
double Fgen(double k, double k2, double k1, double jf, double lambda, double lambdaPrime, double ji)
{
   return pow(-1, lambdaPrime + k2 + k1 + 1) *
          sqrt((2 * ji + 1) * (2 * jf + 1) * (2 * lambda + 1) * (2 * lambdaPrime + 1) * (2 * k1 + 1) * (2 * k2 + 1) *
               (2 * k + 1)) *
          ROOT::Math::wigner_3j((int)(2 * lambda), (int)(2 * lambdaPrime), (int)(2 * k), 2, -2, 0) *
          ROOT::Math::wigner_9j((int)(2 * jf), (int)(2 * lambda), (int)(2 * ji), (int)(2 * jf), (int)(2 * lambdaPrime),
                                (int)(2 * ji), (int)(2 * k2), (int)(2 * k), (int)(2 * k1));
}

/**
    Ak function - Equation 2.44 (Morinaga and Yamazaki), with the statistical
   tensor removed for consistency with other literature
*/
double Ak(double k, double ji, double lambda, double lambdaPrime, double jf, double delta)
{
   return 1. / (1. + pow(delta, 2)) *
          (Fk(k, jf, lambda, lambda, ji) + 2 * delta * Fk(k, jf, lambda, lambdaPrime, ji) +
           pow(delta, 2) * Fk(k, jf, lambdaPrime, lambdaPrime, ji));
}

/**
    Generalised Ak coefficients - Equation 5 of AES NIM A 485(2002)753
*/
double Agen(double k, double k1, double k2, double jf, double lambda, double lambdaPrime, double ji, double delta)
{
   return 1. / (1. + pow(delta, 2)) *
          (Fgen(k, k2, k1, jf, lambda, lambda, ji) + 2 * delta * Fgen(k, k2, k1, jf, lambda, lambdaPrime, ji) +
           pow(delta, 2) * Fgen(k, k2, k1, jf, lambdaPrime, lambdaPrime, ji));
}

/**
   Equation 2.43 from Morinaga and Yamazaki

   This assumes a "nice" geometry where the detectors are in a plane parallel to
   the beam direction producing the alignment. It will be much faster than the
   equivalent function found as a member of the StatTensor class, but also much
   less general.

   @param theta Angle between the detector and the beam direction (radians)
   @param ji Initial spin
   @param lambda Multipolarity 1 of the transition
   @param lambdaPrime Multipolarity 2 of the transition
   @param jf Final spin
   @param delta Mixing ratio for multipolarities
   @param rho Statistical tensor specifying the initial state
   @param Qk Solid attenuation coefficients for the detector
   @param kmax Maximum k to be calculated, default =4
   @return W(theta) - angular distribution value at given theta value
*/
double W(double theta, double ji, double lambda, double lambdaPrime, double jf, double delta, StatTensor *rho,
         SolidAttenuation *Qk, double kmax /*= 4*/)
{
   std::complex<double> wtheta = 0;
   for (int ik = 0; ik <= int(kmax); ++ik) {
      double k = (double)ik;
      wtheta = wtheta + Ak(k, ji, lambda, lambdaPrime, jf, delta) * rho->GetBk(k) * Qk->Get()[ik] *
                           ROOT::Math::legendre(ik, cos(theta));
   }
   if (abs(wtheta.imag()) >= 1e-15)
      std::cout << "Warning: imaginary parts of statistical tensor have not cancelled" << std::endl;
   return wtheta.real();
}

  /**
     Equation 14 from AES NIM A 485(2002)753 - transforming a Gk coefficient from one frame to another using Wigner D matrices

     @param Gk Gk Function in initial frame
     @param alpha Euler angle alpha
     @param beta Euler angle beta
     @param gamma Euler angle gamma

  */

  std::function<std::complex<double>(double, double, double, double, double) >
  TransFrame(std::complex<double> (&Gk)(double, double, double, double, double), double alpha, double beta, double gamma)
  {
    std::function<std::complex<double>(double, double, double, double, double)> newGk;
        
    newGk = [alpha, beta, gamma, &Gk](double q, double qprime, double k, double kprime, double t) {
      //std::cout << "Frame transformation" << std::endl;
      std::complex<double> sum = 0;
      for (int iQ = 0; iQ < 2*k + 1; ++iQ) {
        for (int iQprime = 0; iQprime < 2*kprime+1; ++iQprime) {
          double Q = (double)iQ - k;
          double Qprime = (double)iQprime - kprime;
          sum += std::conj(GamR::AngDist::BigD(k, q, Q, alpha, beta, gamma))*
            std::conj(Gk(Q, Qprime, k, kprime, t))*
            GamR::AngDist::BigD(kprime, qprime, Qprime, alpha, beta, gamma);

          // if (Q==Qprime && k==kprime) {
          //   std::cout << k << "   " << q << "  " << Q << "  " << std::conj(GamR::AngDist::BigD(k, q, Q, alpha, beta, gamma)) << std::endl;
          //   std::cout << kprime << "  " << qprime << "  " << Qprime << "  " <<  GamR::AngDist::BigD(kprime, qprime, Qprime, alpha, beta, gamma) << std::endl;
          //}
        }
      }
      //printf("Gkk = (%15.14f, %15.14f)\n", sum.real(), -sum.imag());
      return std::conj(sum);
    };

    return newGk;
  }
  
/**
   Equation 2.43 from Morinaga and Yamazaki

   This assumes a "nice" geometry where the detectors are in a plane parallel to
   the beam direction producing the alignment. It will be much faster than the
   equivalent function found as a member of the StatTensor class, but also much
   less general.

   @param theta Vector of angles between the detector and the beam direction
   (radians)
   @param ji Initial spin
   @param lambda Multipolarity 1 of the transition
   @param lambdaPrime Multipolarity 2 of the transition
   @param jf Final spin
   @param delta Mixing ratio for multipolarities
   @param rho Statistical tensor specifying the initial state
   @param Qk Solid attenuation coefficients for the detector
   @param kmax Maximum k to be calculated, default =4
   @return A vector of W(theta) values corresponding to the input theta vector
*/

std::vector<double> W(std::vector<double> theta, double ji, double lambda, double lambdaPrime, double jf, double delta,
                      StatTensor *rho, SolidAttenuation *Qk, double kmax /*= 4*/)
{
   /* equation 2.43 */
   std::vector<std::complex<double>> Aks;
   std::vector<double> W;
   for (int ik = 0; ik <= int(kmax); ++ik) {
      double k = (double)ik;
      Aks.push_back(Ak(k, ji, lambda, lambdaPrime, jf, delta) * rho->GetBk(k));
   }
   for (int it = 0; it < (int)theta.size(); ++it) {
      std::complex<double> wtheta = 0;
      for (int ik = 0; ik <= int(kmax); ++ik) {
         double k = (double)ik;
         wtheta = wtheta + Aks[ik] * Qk->Get()[ik] * ROOT::Math::legendre(k, cos(theta[it]));
      }
      if (wtheta.imag() != 0)
         std::cout << "Warning: imaginary parts of statistical tensor have not "
                      "cancelled"
                   << std::endl;

      W.push_back(wtheta.real());
   }
   return W;
}

} /* namespace AngDist */
} /* namespace GamR */
