/**
   @file
   @author Timothy Gray <timothy.gray@anu.edu.au>
   @section DESCRIPTION

   This file relates to the statistical tensor formalism.
*/

#include <algorithm>
#include <complex>
#include <iostream>

#include <Math/SpecFunc.h> /* legendre polynomials, 3j and 6j symbols */

#include "AngDist.hh"
#include "StatTensor.hh"
#include "WignerD.hh"

namespace GamR {
  namespace AngDist {
    /**
       Constructor that initialises the correct dimensions given the spin

       @param j Max spin
    */
    StatTensor::StatTensor(double j)
    {
      this->j = j;
      Clear();
    }

    /**
       Statistical tensor constructor using the population parameter definition
       expanded from that included in Morinaga and Yamazaki - see AES NIM A
       485(2002)753 Equation 2.36

       @param Pm Vector of m-projections weights, i.e. \f$-j, -j+1,...,j-1,j\f$
       @param j Max spin
    */
    StatTensor::StatTensor(std::vector<double> Pm, double j) : StatTensor(j)
    {
      Set(Pm);
    }

    void StatTensor::Set(std::vector<double> Pm) {
      for (int ik = 0; ik < 2 * j + 1; ++ik) {
        double k = (double)ik;

        double sum = 0;
        for (int im = 0; im < 2 * j + 1; ++im) {
          double m = (double)im - j;
          double value =
            pow(-1, j - m) *
            ROOT::Math::wigner_3j((int)(2 * j), (int)(2 * j), (int)(2 * k), (int)(2 * m), (int)(2 * -m), 0) *
            // sqrt(2*k + 1) *  /* removed to make consistent with Andrew's
            // program
            //                      see AES NIM A 485(2002)753, equation 1 and 2
            //                      vs Morinaga and Yamazaki 2.36 */

            Pm[im];
          sum = sum + value;
        }

        this->rho[k][k] = std::complex<double>(sum * sqrt(2 * j + 1), 0);
      }
    }
    
    /**
       Initialises correct dimensions of statistical tensor, with all zeroes
    */
    void StatTensor::Clear()
    {
      this->rho.clear();
      this->rho.reserve((int)(2*this->j+1));
      for (int ik = 0; ik < 2 * this->j + 1; ++ik) {
        double k = (double)ik;
	this->rho.emplace_back();
        for (int iq = 0; iq < 2 * ik + 1; ++iq) {
          this->rho.at(this->rho.size()-1).emplace_back(0,0);
	}
      }
    }

    std::complex<double> StatTensor::Get(double k, double q)
    {
      int ik = std::round(k);
      int iq = std::round(q);
      return this->rho[ik][iq + ik];
    }

    std::complex<double> StatTensor::Set(double k, double q, std::complex<double> value)
    {
      int ik = std::round(k);
      int iq = std::round(q);
      this->rho[ik][iq + ik] = value;
      return this->rho[ik][iq+ik];
    }

    /**
       Get Bk value.

       We are using the formalism in AES NIM A 485(2002)753, as opposed to Morinaga
       and Yamazaki here
    */
    std::complex<double> StatTensor::GetBk(double k)
    {
      return sqrt(2 * k + 1) * this->rho[(int)k][(int)k];
    }

    /**
       Finds the statistical tensor for an observed transition

       Equation 4 from AES NIM A 485(2002)753

       @param ji Initial spin
       @param lambda Multipolarity 1 of the transition
       @param lambdaPrime Multipolarity 2 of the transition
       @param jf Final spin
       @param delta Mixing ratio for multipolarities
       @param Qk Solid attenuation coefficients for the detector
       @param theta Polar angle of detector in radians
       @param phi Azimuthal angle of detector in radians
       @return Statistical tensor after the radiation has been osbserved
    */
    StatTensor *StatTensor::ObservedProp(double ji, double lambda, double lambdaPrime, double jf, double delta,
                                         SolidAttenuation *Qk, double theta, double phi)
    {

      StatTensor *rhoAfter = new StatTensor(jf);
      for (int ik2 = 0; ik2 < 2 * jf + 1; ++ik2) {
        double k2 = (double)ik2;
        for (int iq2 = 0; iq2 < 2 * ik2 + 1; ++iq2) {
          double q2 = (double)iq2 - k2;
          std::complex<double> sum = 0;
          int Lmax = (int)std::max(lambda, lambdaPrime);
          for (int ik = 0; ik < 2 * Lmax + 1; ++ik) {
            double k = (double)ik;
            for (int ik1 = 0; ik1 < 2 * this->j + 1; ++ik1) {
              double k1 = (double)ik1;
              for (int iq = 0; iq < 2 * ik + 1; ++iq) {
                double q = (double)iq - k;
                for (int iq1 = 0; iq1 < 2 * ik1 + 1; ++iq1) {
                  double q1 = (double)iq1 - k1;
                  sum = sum + Get(k1, q1) * pow(-1, k1 + q1) * sqrt((2 * k + 1) * (2 * k1 + 1) / (2 * k2 + 1)) *
                    ROOT::Math::wigner_3j((int)2*k1, (int)2*k, (int)2*k2, -(int)2*q1, (int)2*q, (int)2*q2) *
                    Agen(k, k1, k2, jf, lambda, lambdaPrime, ji, delta) * Qk->Get(k) *
                    std::conj(GamR::AngDist::BigD(k, q, 0, phi, theta, 0));
                }
              }
            }
          }
          rhoAfter->Set(k2, q2, sum);
        }
      }
      return rhoAfter;
    }

    /**
       Finds the statistical tensor for an unobserved transition

       Like an observed propagation, but with only k = 0.  See text in AES NIM A
       485(2002)753, pg 756

       @param ji Initial spin
       @param lambda Multipolarity 1 of the transition
       @param lambdaPrime Multipolarity 2 of the transition
       @param jf Final spin
       @param delta Mixing ratio for multipolarities
       @param Qk Solid attenuation coefficients for the detector
       @return Statistical tensor after the radiation has been emitted but not
       observed
    */
    StatTensor *StatTensor::UnobservedProp(double ji, double lambda, double lambdaPrime, double jf, double delta,
                                           SolidAttenuation *Qk)
    {
      StatTensor *rhoAfter = new StatTensor(jf);
      for (int ik2 = 0; ik2 < 2 * jf + 1; ++ik2) {
        double k2 = (double)ik2;
        for (int iq2 = 0; iq2 < 2 * ik2 + 1; ++iq2) {
          double q2 = (double)iq2 - k2;
          std::complex<double> sum = 0;
          double k = 0;
          double q = 0;
          for (int ik1 = 0; ik1 < 2 * this->j + 1; ++ik1) {
            double k1 = (double)ik1;
            for (int iq1 = 0; iq1 < 2 * ik1 + 1; ++iq1) {
              double q1 = (double)iq1 - k1;
              sum = sum + Get(k1, q1) * pow(-1, k1 + q1) * sqrt((2 * k + 1) * (2 * k1 + 1) / (2 * k2 + 1)) *
                ROOT::Math::wigner_3j((int)2*k1, (int)2*k, (int)2*k2, -(int)2*q1, (int)2*q, (int)2*q2) *
                Agen(k, k1, k2, jf, lambda, lambdaPrime, ji, delta) * Qk->Get(k);
            }
          }
          rhoAfter->Set(k2, q2, sum);
        }
      }
      return rhoAfter;
    }
    /**
       Calculates the perturbation due to a time-dependent perturbation factor Gk

       Equation 12 in AES NIM A 485(2002)753, pg 756
  
       @param Gk perturbation factor function, which takes argurments q, q', k, k', t
       @return Statistical tensor after the perturbation for time t
    */
    StatTensor *StatTensor::Perturbation(std::function<std::complex<double>(double, double, double, double, double)> &Gk, double t)
    {
      //std::cout << "PERTURBATION" << std::endl;
      StatTensor *rhoAfter = new StatTensor(this->j);
      double j = this->j;
      for (int ik2 = 0; ik2 < 2*j + 1; ik2 = ik2 + 2) {
        double k2 = (double)ik2;
        for (int iq2 = 0; iq2 < 2*ik2 + 1; ++iq2) {
          double q2 = (double)iq2 - k2;
          //std::cout << "=====" << std::endl;
          //std::cout << k2 << "   " << q2 << std::endl;
          std::complex<double> sum = 0;
          for (int ik1 = 0; ik1 < 2*j + 1; ik1 = ik1 + 2) {
            double k1 = (double)ik1;
            for (int iq1 = 0; iq1<2*ik1 + 1; ++iq1) {
              double q1 = (double)iq1 - k1;
              std::complex<double> rhokq = Get(k1, q1);
              std::complex<double> Gkk = std::conj(Gk(q1, q2, k1, k2, t));
              sum = sum + rhokq * sqrt((2*k1 + 1)/(2*k2 + 1)) * Gkk;
              // if (k2==k1) {                
              //   std::cout << "   " << q1 << "   " << q2 << std::endl;
              //   printf("   Gkk = (%15.14f, %15.14f)\n", Gkk.real(), Gkk.imag());
              //   printf("   rhokq = (%15.14f, %15.14f)\n", rhokq.real(), rhokq.imag());
              // }                            
            }
          }
          //std::cout << "final = " << sum << std::endl;
          rhoAfter->Set(k2, q2, sum);
        }
      }
      return rhoAfter;
    }

    /**
       Calculates the angular distriubtion from a statistical tensor for any angle

       Equation 10 in AES NIM A 485(2002)753

       @param ji Initial spin
       @param lambda Multipolarity 1 of the transition
       @param lambdaPrime Multipolarity 2 of the transition
       @param jf Final spin
       @param delta Mixing ratio for multipolarities
       @param Qk Solid attenuation coefficients for the detector
       @param theta Polar angle of detector in radians
       @param phi Azimuthal angle of detector in radians
       @return Angular distriubtion intensity at the detector position
    */
    double StatTensor::W(double ji, double lambda, double lambdaPrime, double jf, double delta, SolidAttenuation *Qk,
                         double theta, double phi)
    {
      std::complex<double> W = 0;
      for (int ik2 = 0; ik2 < 2 * (this->j) + 1; ik2 = ik2 + 2) {
        double k2 = (double)ik2;
        for (int iq2 = 0; iq2 < 2 * ik2 + 1; ++iq2) {
          double q2 = (double)iq2 - k2;
          //std::cout << k2 << "   " << q2 << std::endl;
          //std::cout << W << std::endl;
          W = W + Get(k2, q2) * sqrt(2 * k2 + 1) * Ak(k2, ji, lambda, lambdaPrime, jf, delta) * Qk->Get(k2) *
          std::conj(GamR::AngDist::BigD(k2, q2, 0, phi, theta, 0));

          //std::cout << Get(k2, q2) * sqrt(2 * k2 + 1) * Ak(k2, ji, lambda, lambdaPrime, jf, delta) * Qk->Get(k2) *
          //  std::conj(GamR::AngDist::BigD(k2, q2, 0, phi, theta, 0)) << std::endl;

          //printf("%16.15f\n", W.real());
        }
      }
      //std::cout << W << std::endl;
      if (abs(W.imag()) >= 1e-15) {
        std::cout << "Warning: imaginary parts of statistical tensor do not cancel! " << std::endl;
        std::cout << W.real() << "  " << W.imag() << std::endl;
      }
      return W.real();
    }

    void StatTensor::Print()
    {
      printf("  k    q  rho_k (real)                                    rho_k (imaginary)\n");
      for (int ik = 0; ik < (int)this->rho.size(); ++ik) {
        for (int iq = 0; iq < (int)this->rho[ik].size(); ++iq) {
          printf("%3d  %3d  %16.15f       %16.15f\n", ik, iq - ik, this->rho[ik][iq].real(), this->rho[ik][iq].imag());
          //std::cout << ik << "  " << iq-ik << "     " << this->rho[ik][iq].real() << "   " << this->rho[ik][iq].imag() << std::endl;
        }
      }
    }
  } /* namespace AngDist */
} /* namespace GamR */
