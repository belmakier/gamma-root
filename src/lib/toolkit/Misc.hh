#ifndef GAMR_TOOLKIT_MISC_HH
#define GAMR_TOOLKIT_MISC_HH

namespace GamR {
  namespace TK {
    const std::string Elements[93] { "n", "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U" };
    // Convert an isotope identifier string, e.g. 3He or Li5 into corresponding Z and A. Returns 0 on success, and 1 on failure setting Z=-1 and A=0.
		int GetZA(std::string Nuclide, int &Z, double &A);
    std::string GetElement(int Z, float A);
  }
}
    

#endif
