/**
   @file
   @author Timothy Gray <timothy.gray@anu.edu.au>
   @section DESCRIPTION

   Library to calculate angular distributions/correlations, following the
   formalism in Morinaga and Yamazaki - In-Beam Gamma-Ray Spectroscopy, amongst
   other references.

   This file relates to the PopulationParameter object - see Morinaga and
   Yamazaki for an explanation of population parameters.
*/

#include <math.h>

#include "PopulationParameter.hh"

namespace GamR {
namespace AngDist {
/**
   PopulationParameter constructor by spin and sigma/j value (assuming a
   Gaussian distriubtion).

   See Morinaga and Yamazaki equation 2.54

   @param j Angular momentum of the state
   @param sigmaj sigma/j width parameter
 */
  PopulationParameter::PopulationParameter(double j)
  {
    for (int im = 0; im<2*j+1; ++im) {
      this->Pm.push_back(1.0/(2*j+1));
    }
  }
  
  
  PopulationParameter::PopulationParameter(double j, double sigmaj)
  /* equation 2.54 */
  {
    double sigma = sigmaj * j;
    double sum = 0;
    for (int im = 0; im < 2 * j + 1; ++im) {

      double m = (double)im - j;
      this->Pm.push_back(exp(-pow(m, 2) / (2 * pow(sigma, 2))));
      sum = sum + exp(-pow(m, 2) / (2 * pow(sigma, 2)));
    }

    for (int i = 0; i <= 2 * j + 1; ++i) {
      this->Pm[i] = this->Pm[i] / sum; /* normalise */
    }
  }
} /* namespace AngDist */
} /* namespace GamR */
