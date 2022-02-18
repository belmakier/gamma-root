/**
   @file
   @author Timothy Gray <timothy.gray@anu.edu.au>
   @section DESCRIPTION

   Library to calculate angular distributions/correlations, following the
   formalism in Morinaga and Yamazaki - In-Beam Gamma-Ray Spectroscopy, amongst
   other references.

   This file relates to the SolidAttenuation object - see Appendix 9 of Alpha-
   Beta- Gamma-Ray Spectroscopy, Kai Siegbahn for details.
*/

#ifndef SOLIDATT_HH
#define SOLIDATT_HH

#include <vector>

namespace GamR {
namespace AngDist {
  double GetTauG(double E);
class SolidAttenuation {
   /**
       Solid angle attenuation coefficient
   */
private:
   std::vector<double> Qk;

public:
   SolidAttenuation(std::vector<double> Qk);
   SolidAttenuation(double distance, double radius, int kmax = 4, double absorbCoeff = -1);
  SolidAttenuation(double distance, double length, double outer_radius, double inner_radius, double energy, int kmax = 4);
   std::vector<double> Get() { return Qk; }
  double Get(double k) { return Qk[(int)k]; }
  void Set(double k,double Qk_in) { Qk[(int)k]=Qk_in; }
  void Print() {for (int k=0; k<(int)Qk.size(); ++k) { printf("%3d    %7.5f\n", k, Qk[k]); } }
};
} /* namespace AngDist */
} /* namespace GamR */

#endif /* SOLIDATT_HH */
