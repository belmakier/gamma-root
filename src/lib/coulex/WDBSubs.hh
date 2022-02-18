#ifndef WDBSUBS
#define WDBSUBS

namespace GamR {
	namespace Coulex {
		namespace WDB {
			extern "C" {
				void coulparcm_(float &eb, float &tcmdeg);			//Beam energy and centre-of-mass scattering angle.
				void setup_coulex_();						//Initialises common blocks and default values for coulex routine
				void coulex_();							//Calculates AD statistical tensors.
				void getcoulex_(int &lvl, float rho_cre[3][5], float &xsect);		//Get AD statistical tensors.
				void freader_(char readfile[], int &inperr);			//Coulex card file name, error flag.
			}
		}
	}
}
#endif
