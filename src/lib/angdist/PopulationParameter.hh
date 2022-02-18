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

#ifndef POPPAR_HH
#define POPPAR_HH

#include <vector>

namespace GamR {
namespace AngDist {

class PopulationParameter {
   /**
      PopulationParameter object - see Section 2.2.1 of Morinaga and Yamazaki
   */
private:
   std::vector<double> Pm;

public:
  PopulationParameter(double j); /* no alignment */
   PopulationParameter(double j, double sigmaj); /* assuming oblate alignment and
                                                   Gaussian distribution */
  
   std::vector<double> GetPm() { return Pm; }
};
} /* namespace AngDist */
} /* namespace GamR */

#endif /* POPPAR_HH */
