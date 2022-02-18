#ifndef GAMR_COULEX_COULEX_HH
#define GAMR_COULEX_COULEX_HH

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <complex>

#include <TMath.h>

#include <toolkit/Misc.hh>
#include <angdist/AngDist.hh>
#include "Eloss.hh"
#include "WDBSubs.hh"

namespace GamR {
	namespace Coulex {
    const double rad2deg = 360. / 2. / TMath::Pi();
		// Structure for passing level data to the MakeDatafile function    
		struct WDB_nuclvl {
			float spin;	// Spin of state
			float E;	// Energy of state
			bool par;	// Parity of state
			int K_Band;	// K number in rotor model
		};

		// Structure for passing transition data to the MakeDatafile function
		struct WDB_nuctrans {
			int lvl1;	// Lower level
			int lvl2;	// Upper level
			float B;	// Reduced matrix element in eb
			int M;		// Multipolarity
		};

		// This routine accepts beam and target information, and the dimensions and position of a square particle detector at phi=0, and calculates the average nuclear stat tensor across the detector.
		// Nuclear levels and transitions from the nucleus of interest must be passed using the WDB_nuclvls and WDB_nuctrans vectors.
		//GamR::AngDist::StatTensor *CoulexNucTensors(int Zbeam, float Abeam, int Ztgt, float Atgt, bool ProjDet, bool TgtEx, float E, float Q, float Tgtdensity, float Tgtthickness, int tenslvl, int nlvl, std::vector<WDB_nuclvl> &lvls, int nEtran, std::vector<WDB_nuctrans> &Etrans, int nMtran, std::vector<WDB_nuctrans> &Mtrans, float PDetx, float PDety, float PDetz, double PDetr);
		
		// This routine will ask a series of questions to input the information required for coulex and optionally the Qk calculation, then build the WDB_nuclvls and WDB_nuctrans one-dimensional arrays needed for the CoulexNucTens routine.
		//void ExperimentalSetup(int &Zbeam, double &Abeam, int &Ztgt, double &Atgt, bool &ProjectileDetected, bool &TargetExcited, double &Ebeam, double &Qex, double &TargetThickness, double &TargetDensity, double &PDetx, double &PDety, double &PDetz, double &PDetr, int &ngamma, int &nstates, std::vector<WDB_nuclvl> &NucLevels, int &Tenslevel, int &nEtrans, std::vector<WDB_nuctrans> &Etrans, int &nMtrans, std::vector<WDB_nuctrans> &Mtrans, std::vector<GamR::AngDist::SolidAttenuation> *Qks = nullptr);
		
		// Gives the Winther-DeBoer codes a projectile energy and target scattering angle (CM) which calculates nuclear stat tensors after coulex, then copies the tensors and reaction cross-section for your chosen level into the variables provided (whether the target or projectile tensors are calculated is determined in the MakeDatafile routine).
		// Please ensure rho is dimensioned [3][5] (k=0,2,4 q<=0 to 2*k)
		void GP_AC_Tensors(float Ebeam, float CMAng, int lvl, std::complex<double> **rho, float &xsect);
		
		// This function is a wrapper to handle datafile construction, reading and removal. Returns 0 on success, 1 on file write error, 2 on read error, and 3 on removal error.
		int setupcoulex(int Zbeam, float Abeam, int Ztgt, float Atgt, int grouptype, std::vector<WDB_nuclvl> &nuclvls, std::vector<WDB_nuctrans> &nucEtrans, std::vector<WDB_nuctrans> &nucMtrans);
		
		/* Creates the data file which FREADER will read to setup the common block variables for the coulex calculation. 
		 * Total states is the total number of nuclear states to be considered in all level schemes, Z_P is projectile Z, A_P is projectile mass, Z_T is target Z, A_T is target mass, nucgroups is the number of different nuclear level schemes,
		 * grouptype[nucgroups] specifies whether the group is a projectile(1) or target(2), nuclvls[nucgroups] specifies how many levels are in the level scheme provided for a scheme, nuclvl[nucgroups][nuclvls] is a struct containing level information,
		 * nucEMtrans[nucgroups] is the number of reduced matrix elements between transitions provided, nucEMtran[nucgroups][nucE/Mtrans] is a structure containing sqrt(B(EM/MM)) values, and filename is an optional output name for the data file.
		 * Function returns 0 on success, 1 on a file access error.
		 */
		int MakeDatafile(int Zbeam, float Abeam, int Ztgt, float Atgt, int grouptype, std::vector<WDB_nuclvl> &nuclvls, std::vector<WDB_nuctrans> &nucEtrans, std::vector<WDB_nuctrans> &nucMtrans, std::string filename = "");
		
		// Calls the coulex setup and data file reading routines that are part of the Winther-DeBoer codes. This only needs to be done once. Use Makedatafile to setup the data file.
		int ReadDatafile(std::string datafile="");
		
		// Transforms cross-section from centre-of-mass to lab
		double xcmlr(double anglab, double angCM, double Ap, double At, double Ep, double Q, bool Tgtex);
		
		// :: DEPRECIATED See Eloss.hh for new code :: Simplified interface to the fortran-based eloss routine by A.E. Stuchbery based on Ziegler's stopping powers. Accepts a monoelemental target only. Dfoil can be 0 and will pull a value from SCOEF.dat.
		// void Eloss(float Ein, float Abeam, int Zbeam, float Afoil, int Zfoil, float &Dfoil, float FoilThickness, float &Eout, float &transittime, float &range);
		
		/* Routine to get reaction kinematics based on Marion and Young's solutions, originally writted in FORTRAN by A.E. Stuchbery.
		 * Inputs: A1I is projectile mass, A2I is target mass, A3I is light recoil mass, A4I is heavy recoil mass, E1I is projectile energy, QEFFI is reaction energy and PSII is the light recoil angle.
		 * Outputs: E3I is the light mass energy, E3AI is alt solution, E4I is heavy mass energy, E4AI is alt solution, ZETAI is heavy recoil angle, ZETAAI is alt solution, thetaI is light CM angle, thetaaI is alt solution, PHII is heavy CM angle, and PHIAI is alt soluiton.
		 * The function returns a flag where 1= unique solution, 0= two solutions and -1= bad light recoil angle. */
		int Kinematics(double A1I, double A2I, double A3I, double A4I, double E1I, double QEFFI, double PSII, double &E3I, double &E3AI, double &E4I, double &E4AI, double &ZETAI, double &ZETAAI, double &thetaI, double &thetaaI, double &PHII, double &PHIAI);
		
		// Draws the particle detector geometry using ASCII characters to assist user input
		void DrawSetup();
	}
}
#endif
