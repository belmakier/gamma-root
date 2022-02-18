#include <string>
#include <stdexcept>

#include "Misc.hh"

namespace GamR {
  namespace TK {
    // Convert an isotope identifier string, e.g. 3He or Li5 into corresponding Z and A. Returns 0 on success, and 1 on failure setting Z=-1 and A=0.
		int GetZA(std::string Nuclide, int &Z, double &A)
		{			
			std::string Elm;
			std::string mass = "0";
			for(int i=0;i<Nuclide.size();i++) {
				if(Nuclide[i]=='-') continue;
				else if(int(Nuclide[i])<58) mass += Nuclide[i];
				else Elm += Nuclide[i];
			}
			Z=0;
			// Check for particle IDs before going through the element list
			if(Elm=="p") {
				Z = 1;
				A = 1;
				return 0;
			}
			if(Elm=="d") {
				Z = 1;
				A = 2;
				return 0;
			}
			if(Elm=="t") {
				Z = 1;
				A = 3;
				return 0;
			}
			if(Elm=="a") {
				Z = 2;
				A = 4;
				return 0;
			}
			while(Elements[Z]!=Elm) {
				Z++;
				if(Z>92) {
					Z=-1;
					A=0;
					return 1;
				}
			}
			if(Z==0) mass = "1";
			try { A=stof(mass); }
			catch (const std::invalid_argument& ia) { A = 0.; }
			return 0;
		}

    std::string GetElement(int Z, float A) {
      if (Z < 93) {
        return Elements[Z]+std::to_string((int)A);
      }
      else {
        return "Invalid Z";
      }
    }    

  }
}
