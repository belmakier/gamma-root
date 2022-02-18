/**
   @file
   @author Timothy Gray <timothy.gray@anu.edu.au>
   @section DESCRIPTION

   This file relates to the statistical tensor formalism.
*/

#ifndef STATTENS_HH
#define STATTENS_HH

#include <cmath>
#include <complex>
#include <vector>
#include <functional>

#include "PopulationParameter.hh"
#include "SolidAttenuation.hh"

namespace GamR {
  namespace AngDist {
    class StatTensor {
      /**
         Statistical tensor object, for specific spin
      */
    private:
      double j;
      std::vector<std::vector<std::complex<double> > > rho;

    public:
      StatTensor(double j);
      StatTensor(std::vector<double> Pm, double j);
      StatTensor(double j, double sigmaj) : StatTensor(j) { GamR::AngDist::PopulationParameter pp(j, sigmaj); Set(pp.GetPm()); }
      void Clear();
      void Set(std::vector<double> Pm);
      std::complex<double> Get(double k, double q);
      std::complex<double> Set(double k, double q, std::complex<double> value);
      std::complex<double> GetBk(double k);
      StatTensor *ObservedProp(double ji, double lambda, double lambdaPrime, double jf, double delta, SolidAttenuation *Qk,
                               double theta, double phi);
      StatTensor *UnobservedProp(double ji, double lambda, double lambdaPrime, double jf, double delta,
                                 SolidAttenuation *Qk);
      StatTensor *Perturbation(std::function<std::complex<double>(double, double, double, double, double) > &Gk, double t);
      double W(double ji, double lambda, double lambdaPrime, double jf, double delta, SolidAttenuation *Qk, double theta,
                                        double phi);

                               void Print();
                               };
    } /* namespace AngDist */
  } /* namespace GamR */

#endif /* STATTENS_HH */
