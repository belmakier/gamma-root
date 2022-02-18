/**
   @file
   @author Brendan McCormick <brendan.mccormick@anu.edu.au>
   @section DESCRIPTION

   This file provides a C++ interface to FORTRAN Winther de Boer (WDB) coulex codes
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>

#include <TMath.h>

#include <angdist/AngDist.hh>
#include <toolkit/Misc.hh>
#include <utils/Utilities.hh>
#include "Eloss.hh"
#include "WDBSubs.hh"
#include "Coulex.hh"

namespace GamR {
	namespace Coulex {
    /**
       Routine to get reaction kinematics based on Marion and Young's solutions, writted in FORTRAN by A.E. Stuchbery.

       @param A1I projectile mass
       @param A2I target mass
       @param A3I light recoil mass
       @param A4I heavy recoil mass
       @param E1I projectile energy
       @param QEFFI reaction energy
       @param PSII light recoil angle
       @param E3I light mass energy (output)
       @param E3AI alternative solution (output)
       @param E4I heavy mass energy (output)
       @param E4AI alerternative solution (output)
       @param ZETAI heavy recoil angle (output)
       @param ZETAAI alternative solution (output)
       @param thetaI light CM angle (output)
       @param thetaI alternative solution (output)
       @param PHII heavy CM angle (output)
       @param PHIAI alternative solution (output)
       @return 1 = unique solution, 0 = two solutions, -1 = bad light recoil angle
    */
		int Kinematics(double A1I, double A2I, double A3I, double A4I, double E1I, double QEFFI, double PSII, double &E3I, double &E3AI, double &E4I, double &E4AI, double &ZETAI, double &ZETAAI, double &thetaI, double &thetaaI, double &PHII, double &PHIAI)
		{
		/*
		C
		C     SUBROUTINE TO CALCULATE REACTION KINEMATICS
		C     SEE MARION AND YOUNG
		C     THIS CODE WAS ORIGINALLY WRITTEN BY ANDREW STUCHBERY CIRCA 1980
		* 					  converted to 'C' by Brendan McCormick 01/2019
		C
		C     A1=INCIDENT MASS
		C     A2=TARGET MASS
		C     A3="LIGHT" PRODUCT MASS
		C     A4="HEAVY" PRODUCT MASS
		C     E1=INCIDENT BEAM ENERGY
		C     QEFF=EFFECTIVE Q VALUE FOR REACTION (INCLUDE ENERGY LEVEL)
		C     PSI=LAB RECOIL(BACKSCATTER) ANGLE OF "LIGHT" PRODUCT (RADIANS)
		C     E3=LAB ENERGY OF "LIGHT" PRODUCT
		C     E3A=OTHER POSSIBLE E3 FOR B.GT.D (SEE BELOW)
		C     E4=LAB ENERGY OF "HEAVY" PRODUCT
		C     E4A=OTHER POSSIBLE E4
		C     ZETA=LAB RECOIL ANGLE OF HEAVY PRODUCT (RADIANS)
		C     ZETAA=OTHER POSSIBLE ZETA
		C     THETA=CM ANGLE OF LIGHT (I.E. DETECTED) PRODUCT (RADIANS)
		C     THETAA = OTHER POSSIBLE THETA
		C     PHI=CM ANGLE OF HEAVY (I.E. UNDETECTED) PRODUCT (RADIANS)
		C     PHIA = OTHER POSSIBLE PHI
		C     IFLAG (now return value) = +1 NORMAL CASE - UNIQUE SOLUTION
		C             					  0 CASE WHERE B>D (E.G. IF A1>A2) - TWO POSSIBLE SOLUTIONS
		C					             -1 AS FOR 0 BUT AN IMPOSSIBLE SCATTERING ANGLE (PSI) HAS
		C               				    BEEN REQUESTED
		C
		*/
			int iFlag = 1;
			
			if(A1I==0 || A2I==0 || A3I==0 || A4I==0) {
				std::cerr << "!!ERROR!! One or more of the particles in the kinematics routine has no mass." << std::endl;
				return -1;
			}

			double A1,A2,A3,A4,E1,QEFF,PSI,E3,E3A,E4,E4A;
			double ZETA,ZETAA,THETA,THETAA,PHI,PHIA,ET,AD,ED,QD;
			double A,B,C,D,CPSI,SPSI,DUM1,DUM2,DUM3,E3T,E3TA;
			double SZETA,SZA,CTHETA,CTHETAA,PSIMX,DUM0;

		//	INPUT PARAMETERS
			A1=A1I;
			A2=A2I;
			A3=A3I;
			A4=A4I;
			E1=E1I;
			QEFF=QEFFI;
			PSI=PSII;
			
			ET=E1+QEFF;
			AD=(A1+A2)*(A3+A4);
			ED=A1*E1/(ET*AD);
			QD=(A2+A1*QEFF/ET)/AD;

			A=A4*ED;
			B=A3*ED;
			C=A3*QD;
			D=A4*QD;

			SPSI=std::sin(PSI);
			CPSI=std::cos(PSI);
			iFlag=1;
			DUM0=(D/B-SPSI*SPSI);
			if(DUM0<0)DUM0=0.;
			DUM1=std::sqrt(DUM0);
			if(B>D) {				// Two solutions, set flag to 0 and check recoil angle is possible.
				PSIMX=std::asin(std::sqrt(D/B));
				if(PSI>PSIMX) return -1;		// PSI greater than max possible
				else iFlag = 0;
			}
			DUM2=CPSI+DUM1;
			DUM3=CPSI-DUM1;
			E3T=B*DUM2*DUM2;
			E3TA=B*DUM3*DUM3;
			E3=ET*B*DUM2*DUM2;
			E3A=ET*B*DUM3*DUM3;
			E4=ET-E3;
			E4A=ET-E3A;
		//  CALCULATE ZETA
			SZETA=std::sqrt(A3*E3/(A4*E4))*SPSI;
			if(E4A>0) SZA=std::sqrt(A3*E3A/(A4*E4A))*SPSI;
			if(E4A<0) SZA=0;
			ZETA=std::asin(SZETA);
			ZETAA=std::asin(SZA);
		//	CALCULATE THETA
			CTHETA=(E3T-B-D)/(2.*std::sqrt(A*C));
			CTHETAA=(E3TA-B-D)/(2.*std::sqrt(A*C));
			if(CTHETA>1.) CTHETA=1.;
			if(CTHETAA>1.) CTHETAA=1.;
			if(CTHETA<-1.) CTHETA=-1.;
			if(CTHETAA<-1.) CTHETAA=-1.;
			THETA=std::acos(CTHETA);
			THETAA=std::acos(CTHETAA);
		//	CALCULATE PHI
			PHI=TMath::Pi()-THETA;
			PHIA=TMath::Pi()-THETAA;

		//	OUTPUT PARAMETERS
			E3I=E3;
			E3AI=E3A;
			E4I=E4;
			E4AI=E4A;
			ZETAI=ZETA;
			ZETAAI=ZETAA;
			thetaI=THETA;
			thetaaI=THETAA;
			PHII=PHI;
			PHIAI=PHIA;

			return iFlag;
		}

		// :: DEPRECIATED See Eloss.cc for new routine :: Simplified interface to the fortran-based eloss routine by A.E. Stuchbery based on Ziegler's stopping powers. Accepts a monoelemental target only. Dfoil can be 0 and will pull a value from SCOEF.dat.
		/*void Eloss(float Ein, float Abeam, int Zbeam, float Afoil, int Zfoil, float &Dfoil, float FoilThickness, float &Eout, float &transittime, float &range)
		{
			int strips = round(FoilThickness * 100 / Dfoil);
			float racc = 0.001;
			float eacc = 0.001;
			int Zf[10];
			Zf[0] = Zfoil;
			float Af[10];
			Af[0] = Afoil;
			int nsp = 1;	// Number of species = 1
			float form[10];
			form[0] = 1.;	// Molecular forula = 1
			eloss_(Ein,Abeam,Zbeam,Af,Zf,nsp,form,Dfoil,FoilThickness,strips,racc,eacc,Eout,transittime,range);
		}*/

		double xcmlr(double anglab, double angCM, double Ap, double At, double Ep, double Q, bool Tgtex)
		{
		/*	computes solid angle correction for cm to lab transformation
		c	XCLR = (cm cross section)/(lab cross section) (now return value)
		c	Tlab = lab scattering angle
		c	Tcm = centre of mass scattering angle
		c
		c	Added extra April 2006 to get case where 180 degrees CM correct
		c
		c
		c	Ap = projectile mass
		c	At = target mass
		c	Ep = beam energy
		c	Q = Q value in same units as beam energy
		c	pt = p or t character to specify if it is the target or projectile
		c	            solid angle that is required
		c
		c	Reference: Marion and Young              Andrew Stuchbery May 2004
								 converted to 'C' by Brendan McCormick 01/2019
		c
		c	******************** angles in radians *******************/
			double tau, taubar, Etp;
			
			if(angCM==0 && !Tgtex) return 1.;
			if(anglab==0) {
			// CM angle for projectile must be 180 degrees. For target it can be zero:
			// See AW 1975 p 267 for formulas
				if(Tgtex) {
					Etp = Ep + Q * (1. + Ap/At);
					taubar = std::sqrt(Ep/Etp);
					return 1. / std::pow(1.+taubar,2);
				}
				else {
					Etp = Ep + Q * (1. + Ap/At);
					tau = (Ap/At) * std::sqrt(Ep/Etp);
					return 1. / std::pow(1.-tau,2);
				}
			}
			return std::pow(std::sin(anglab)/std::sin(angCM),2) * std::fabs(std::cos(angCM-anglab));
		}

		/* Creates the data file which FREADER will read to setup the common block variables for the coulex calculation. 
		 * Total states is the total number of nuclear states to be considered in all level schemes, Z_P is projectile Z, A_P is projectile mass, Z_T is target Z, A_T is target mass, nucgroups is the number of different nuclear level schemes,
		 * grouptype[nucgroups] specifies whether the group is a projectile(1) or target(2), nuclvls[nucgroups] specifies how many levels are in the level scheme provided for a scheme, nuclvl[nucgroups][nuclvls] is a struct containing level information,
		 * nucEMtrans[nucgroups] is the number of reduced matrix elements between transitions provided, nucEMtran[nucgroups][nucE/Mtrans] is a structure containing sqrt(B(EM/MM)) values, and filename is an optional output name for the data file.
		 * Function returns 0 on success, 1 on a file access error.
		 */
		int MakeDatafile(int Zbeam, float Abeam, int Ztgt, float Atgt, int grouptype, std::vector<WDB_nuclvl> &nuclvls, std::vector<WDB_nuctrans> &nucEtrans, std::vector<WDB_nuctrans> &nucMtrans, std::string filename /*= ""*/)
		{
			int nlvls = nuclvls.size();
			int nEtrans = nucEtrans.size();
			int nMtrans = nucMtrans.size();
			
			std::string strout;
			std::ofstream datafile;
			
			if(filename.empty()) filename = "coulex.dat";
			datafile.open(filename.c_str());
			if(datafile.fail()) return 1;
			
			strout = "1 " + std::to_string(nlvls) +"\n";
			datafile.write(strout.c_str(),strout.size());
			strout = "7 0\n";			
			datafile.write(strout.c_str(),strout.size());
			strout = "8 0\n";
			datafile.write(strout.c_str(),strout.size());
			strout = "12 1\n";
			datafile.write(strout.c_str(),strout.size());
			strout = "17 " + std::to_string(Zbeam) + ' ' + std::to_string(Abeam) + '\n';
			datafile.write(strout.c_str(),strout.size());
			strout = "18 " + std::to_string(Ztgt) + ' ' + std::to_string(Atgt) + '\n';
			datafile.write(strout.c_str(),strout.size());
			strout = "19 1.0 \n";
			datafile.write(strout.c_str(),strout.size());
			strout = "21 1.0 \n";
			datafile.write(strout.c_str(),strout.size());
			for(int l=0;l<nlvls;l++) {
				if(nuclvls[l].par) strout = "22 " + std::to_string(l+1) + ' ' + std::to_string(nuclvls[l].spin) + ' ' + std::to_string(nuclvls[l].E) + " +1 " + std::to_string(nuclvls[l].K_Band) + '\n';
				else strout = "22 " + std::to_string(l+1) + ' ' + std::to_string(nuclvls[l].spin) + ' ' + std::to_string(nuclvls[l].E) + " -1 " + std::to_string(nuclvls[l].K_Band) + '\n';
				datafile.write(strout.c_str(),strout.size());
			}
			for(int tE=0;tE<nEtrans;tE++) {
				strout = "23 " + std::to_string(nucEtrans[tE].lvl1) + ' ' + std::to_string(nucEtrans[tE].lvl2) + ' ' + std::to_string(nucEtrans[tE].B) + ' ' + std::to_string(nucEtrans[tE].M) + '\n';
				datafile.write(strout.c_str(),strout.size());
			}
			for(int tM=0;tM<nMtrans;tM++) {
				strout = "24 " + std::to_string(nucMtrans[tM].lvl1) + ' ' + std::to_string(nucMtrans[tM].lvl2) + ' ' + std::to_string(nucMtrans[tM].B) + ' ' + std::to_string(nucMtrans[tM].M) + '\n';
				datafile.write(strout.c_str(),strout.size());
			}
			strout = "26 1\n";
			datafile.write(strout.c_str(),strout.size());
			//strout = "27 1 1 " + std::to_string(nuclvls) + ' ' + std::to_string(nuclvl[nlvls-1].spin) + '\n';
			//datafile.write(strout.c_str(),strout.size());
			strout = "29 1 " + std::to_string(grouptype) + '\n';
			datafile.write(strout.c_str(),strout.size());
			strout = "0\n";
			datafile.write(strout.c_str(),strout.size());
			strout = "1000\n";
			datafile.write(strout.c_str(),strout.size());
			
			datafile.close();
			return 0;
		}

		// Calls the coulex setup and data file reading routines that are part of the Winther-DeBoer codes. This only needs to be done once. Use Makedatafile to setup the data file.
		int ReadDatafile(std::string datafile/*=""*/)
		{
			// Error code returned by the freader routine. If non-zero, there was a problem with the data file.
			int ierr;
			
			WDB::setup_coulex_();
			
			// Check if user supplied a data file name and call freader to setup values for coulex routine
			if(datafile.empty()) datafile = "coulex.dat";
			char *df = GamR::Utils::c_to_f_str(datafile);
			WDB::freader_(df,ierr);
			delete[] df;
			
			return ierr;
		}

		// This function is a wrapper to handle datafile construction, reading and removal. Returns 0 on success, 1 on file write error, 2 on read error, and 3 on removal error.
		int setupcoulex(int Zbeam, float Abeam, int Ztgt, float Atgt, int grouptype, std::vector<WDB_nuclvl> &nuclvls, std::vector<WDB_nuctrans> &nucEtrans, std::vector<WDB_nuctrans> &nucMtrans)
		{
			int retval = MakeDatafile(Zbeam,Abeam,Ztgt,Atgt,grouptype,nuclvls,nucEtrans,nucMtrans);
			if(retval) return retval;
			retval = ReadDatafile();
			if(retval) return 2;
			retval = remove("coulex.dat");
			if(retval) return 3;
			return 0;
		}

		// Gives the Winther-DeBoer codes a projectile energy and target scattering angle (CM) which calculates nuclear stat tensors after coulex, then copies the tensors and reaction cross-section for your chosen level into the variables provided (whether the target or projectile tensors are calculated is determined in the MakeDatafile routine).
		// Please ensure rho is dimensioned [3][5] (k=0,2,4 q<=0 to 2*k)
		void GP_AC_Tensors(float Ebeam, float CMAng, int lvl, std::complex<double> **rho, float &xsect)
		{
			float rhor[3][5];
			
			WDB::coulparcm_(Ebeam, CMAng);
			
			WDB::coulex_();

			int lvl1 = lvl+1;  //+1 because FORTRAN doesn't 0 index
			WDB::getcoulex_(lvl1, rhor, xsect);
			
			for(int k=0; k<3; k++) {
				for(int q=0; q<=2*k; q++) {
					rho[k][q] = std::complex<double>(double(rhor[k][q]/rhor[0][0]), 0.);
				}
			}
		}
		
		// Draws particle detector configuration which tensors will be calculated for
		void DrawSetup()
		{
			std::cout << " _________________________" << std::endl;
			std::cout << "|  --- Top-down view ---  |" << std::endl;
			std::cout << "|  Phi angle rotates      |" << std::endl;
			std::cout << "|  particle detector      |" << std::endl;
			std::cout << "|  counter-clockwise      |" << std::endl;
			std::cout << "|  around beam direction  |" << std::endl;
			std::cout << "|  in the x-y plane.      |" << std::endl;
			std::cout << "|  Theta angle rotates    |" << std::endl;
			std::cout << "|  gamma-ray detector     |" << std::endl;
			std::cout << "|  clockwise around tgt   |" << std::endl;
			std::cout << "|  in x-z plane.          |" << std::endl;
			std::cout << "|_________________________|" << std::endl;
			std::cout << "|                         |" << std::endl;
			std::cout << "|Beam  Tgt            stop|" << std::endl;
			std::cout << "|=======|---------------[]|" << std::endl;
			std::cout << "|        <   z   >^       |" << std::endl;
			std::cout << "|                 r       |" << std::endl;
			std::cout << "|                 v       |" << std::endl;
			std::cout << "|    x           |\\y      |" << std::endl;
			std::cout << "|    |     Ptcle | \\      |" << std::endl;
			std::cout << "|    |     dtctr | |      |" << std::endl;
			std::cout << "|    ----z       \\ |x     |" << std::endl;
			std::cout << "|     \\           \\|      |" << std::endl;
			std::cout << "|      \\                  |" << std::endl;
			std::cout << "|       y                 |" << std::endl;
			std::cout << "|_________________________|" << std::endl;
		}
		
	

    /*
		//NOTE pass Qks vector by reference, nullptr is acceptable and results in no return value.
		void ExperimentalSetup(int &Zbeam, double &Abeam, int &Ztgt, double &Atgt, bool &ProjectileDetected, bool &TargetExcited, double &Ebeam, double &Qex, double &TargetThickness, double &TargetDensity, double &PDetx, double &PDety, double &PDetz, double &PDetr, int &ngamma, int &nstates, std::vector<WDB_nuclvl> &NucLevels, int &Tenslevel, int &nEtrans, std::vector<WDB_nuctrans> &Etrans, int &nMtrans, std::vector<WDB_nuctrans> &Mtrans, std::vector<GamR::AngDist::SolidAttenuation> *Qks )
		{
      
			// Beam and target (charges, masses in AMU, beam energy in MeV and target thickness in mg/cm2, excited-state energy in MeV, excited-state spin, ground-state spin, B(E2) in eb, specify if target excites [or projectile], specify if projectile is detected [or target], excited-state partiy and ground-state parity)
			int ttrans;
			float *SE;
			float *SS;
			bool *SP;
			float *B;
			int *Bl1;
			int *Bl2;
			int *M;
			//Gamma-ray detector info for Qk calculation
			float *gL, *gR, *gD, *gr;
			int trans1;
			// Input handling
			std::string inp;
			std::vector<std::string> allinp;
			
			// Answer save file
			std::ifstream ansfile;
			std::string ans;
			std::string ansstr = "Wtheta.ans";
			
			// Get all the inputs necessary to calculate the stat tensors
			std::cout << "This routine will assist you to setup the variables required for the CoulexNucTensors routine for a given target and detector geometry." << std::endl << std::endl;
		retryansfile:
			std::cout << "Answer file name [" << ansstr << "]: ";
			std::getline(std::cin, inp);
			if(ansstr.empty() && inp.empty()) ansstr = "Wtheta.ans";
			else {
				if(!inp.empty()) ansstr = inp;
				ansfile.open(ansstr.c_str());
				if(ansfile.fail()) {
					std::cout << "Could not open answer file! Please try again or leave blank to skip." << std::endl;
					ansstr = "";
					goto retryansfile;
				}
			}
			std::cout << "Beam and target details -" << std::endl;
			ans = readans(ansfile);
		retryBeam:
			std::cout << "\tBeam nucleus [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			if(GamR::TK::GetZA(inp,Zbeam,Abeam)) {
				std::cout << "\tInvalid nucleus. Ensure nucleus is in the format AEl, ElA or El-A e.g. 3He, Li-5." << std::endl;
				goto retryBeam;
			}
			allinp.push_back(inp);
			ans = readans(ansfile);
		retryE:
			std::cout << "\tBeam energy in MeV [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			if(catcherr(inp, Ebeam)) goto retryE;
			allinp.push_back(inp);
			ans = readans(ansfile);
		retryTgt:
			std::cout << "\tTarget nucleus [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			if(GamR::TK::GetZA(inp,Ztgt,Atgt)) {
				std::cout << "\tInvalid nucleus. Ensure nucleus is in the format AEl, ElA or El-A e.g. 3He, Li5, C-13." << std::endl;
				goto retryTgt;
			}
			allinp.push_back(inp);
			ans = readans(ansfile);
		retryTargetThickness:
			std::cout << "\tTarget thickness in mg/cm2 [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			if(catcherr(inp, TargetThickness)) goto retryTargetThickness;
			allinp.push_back(inp);
			ans = readans(ansfile);
		retryTargetDensity:
			std::cout << "\tTarget density in g/cm3 (leave blank to get from SCOEF.DAT) [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			if(inp.empty()) {
				TargetDensity = 0.;
				inp = "0";
			}
			else {
				if(catcherr(inp, TargetDensity, true)) goto retryTargetDensity;
			}
			allinp.push_back(inp);
			ans = readans(ansfile);
		retryEx:
			std::cout << "\tProjectile(1) or target(2) excitation [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			switch(inp[0]) {
				case '1':
					TargetExcited = false;
					break;
				case '2':
					TargetExcited = true;
					break;
				default:
					goto retryEx;
			}
			allinp.push_back(inp);
			ans = readans(ansfile);
		retryDet:
			std::cout << "\tProjectile(1) or target(2) detection [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			switch(inp[0]) {
				case '1':
					ProjectileDetected = true;
					break;
				case '2':
					ProjectileDetected = false;
					break;
				default:
					goto retryDet;
			}
			allinp.push_back(inp);
			ans = readans(ansfile);
			int pread = 0;
			if(!ans.empty()) pread = std::stoi(ans);
		retryStates:
			std::cout << "\tTotal states including ground state [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			if(catcherr(inp,nstates)) goto retryStates;
			if(nstates<2) {
				std::cout << "\tInvalid entry. Must be >1." << std::endl;
				goto retryStates;
			}
			allinp.push_back(inp);
			SE = new float[nstates];
			SS = new float[nstates];
			SP = new bool[nstates];
			for(int i=0; i<nstates; i++) {
				if(pread) ans = readans(ansfile);
		retrySE:
				std::cout << "\tState " << i+1 << " energy in MeV [" << ans << "]: ";
				std::getline(std::cin,inp);
				if(inp.empty()) inp = ans;
				try { SE[i] = stof(inp); }
				catch(const std::invalid_argument& ia) {
					std::cout << "Invalid entry. Must be numerical." << std::endl;
					goto retrySE;
				}
				if(SE[i]<0) {
					std::cout << "Invalid entry. Must be >=0." << std::endl;
					goto retrySE;
				}
				allinp.push_back(inp);
				if(pread) {
					ans = readans(ansfile);
					pread--;
				}
		retrySS:
				std::cout << "\tState " << i+1 << " spin and parity [" << ans << "]: ";
				std::getline(std::cin,inp);
				if(inp.empty()) inp = ans;
				if(inp[inp.size()-1]=='+') SP[i] = true;
				else if(inp[inp.size()-1]=='-') SP[i] = false;
				else {
					std::cout << "\tParity not specified. Please specify spin and parity e.g. 0.5+" << std::endl;
					goto retrySS;
				}
				try { SS[i] = std::stof(inp.substr(0,inp.size()-1)); }
				catch(const std::invalid_argument& ia) {
					std::cout << "\tInvalid entry. Must be numerical." << std::endl;
					allinp.pop_back();
					goto retrySS;
				}
				if(SS[i]<0) {
					std::cout << "\tInvalid entry. Must be >=0." << std::endl;
					allinp.pop_back();
					goto retrySS;
				}
				allinp.push_back(inp);
			}
			if(pread) {
				for(int i=0; i<pread; i++) {
					ans = readans(ansfile);
					ans = readans(ansfile);
				}
			}
			ans = readans(ansfile);
		retryTenslevel:
			std::cout << "\tCalculate tensors for state [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			if(catcherr(inp, Tenslevel)) goto retryTenslevel;
			allinp.push_back(inp);
			ans = readans(ansfile);
			if(!ans.empty()) pread = std::stoi(ans);
			else pread = 0;
		retryTrans:
			std::cout << "\tTotal transitions between states [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			if(catcherr(inp,ttrans)) goto retryTrans;
			allinp.push_back(inp);
			B = new float[ttrans];
			Bl1 = new int[ttrans];
			Bl2 = new int[ttrans];
			M = new int[ttrans];
			for(int i=0; i<ttrans; i++) {
				if(pread) ans = readans(ansfile);
		retryl1:
				std::cout << "\tTransition " << i+1 << " lower state number [" << ans << "]: ";
				std::getline(std::cin,inp);
				if(inp.empty()) inp = ans;
				if(catcherr(inp, Bl1[i])) goto retryl1;
				allinp.push_back(inp);
				if(pread) ans = readans(ansfile);
		retryl2:
				std::cout << "\tTransition " << i+1 << " upper state number [" << ans << "]: ";
				std::getline(std::cin,inp);
				if(inp.empty()) inp = ans;
				if(catcherr(inp, Bl2[i])) goto retryl2;
				allinp.push_back(inp);
				if(pread) ans = readans(ansfile);
		retryB:
				std::cout << "\tTransition " << i+1 << " B up in eb [" << ans << "]: ";
				std::getline(std::cin,inp);
				if(inp.empty()) inp = ans;
				if(catcherr(inp, B[i])) goto retryB;
				allinp.push_back(inp);
				if(pread) {
					ans = readans(ansfile);
					pread--;
				}
		retryM:
				std::cout << "\tTransition " << i+1 << " multipolarity [" << ans << "]: ";
				std::getline(std::cin,inp);
				if(inp.empty()) inp = ans;
				if(catcherr(inp, M[i])) goto retryM;
				allinp.push_back(inp);
			}
			if(pread) {
				for(int i=0; i<pread; i++) {
					ans = readans(ansfile);
					ans = readans(ansfile);
					ans = readans(ansfile);
					ans = readans(ansfile);
				}
			}
			ans = readans(ansfile);
		retrytrans1:
			std::cout << "\tObserved transition [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			if(catcherr(inp, trans1)) goto retrytrans1;
			allinp.push_back(inp);

		// ==================================================================================================================	
		// ------------------------------------------------------------------------------------------------------------------
		// ==================================================================================================================

			std::cout << "Enter details for detector layout shown below. Rotate tensors later for phi != 0" << std::endl;
			std::cout << "NOTE! Enter a negative z for back-scattered particle detection." << std::endl;
			DrawSetup();
			std::cout << std::endl << "Particle detector details -" << std::endl;
			ans = readans(ansfile);
		retryPDetx:
			std::cout << "\tDetector width x in mm [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			if(catcherr(inp, PDetx)) goto retryPDetx;
			allinp.push_back(inp);
			ans = readans(ansfile);
		retryPDety:
			std::cout << "\tDetector height y in mm [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			if(catcherr(inp, PDety)) goto retryPDety;
			allinp.push_back(inp);
			ans = readans(ansfile);
		retryPDetz:
			std::cout << "\tHorizontal distance from target to detector z in mm [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			try { PDetz = stof(inp); }
			catch(const std::invalid_argument& ia) {
				std::cout << "\tInvalid distance. Must be numerical." << std::endl;
				goto retryPDetz;
			}
			if(!PDetz) {
				std::cout << "\tInvalid distance. Must be non-zero." << std::endl;
				goto retryPDetz;
			}
			allinp.push_back(inp);
			ans = readans(ansfile);
		retryPDetr:
			std::cout << "\tRadial distance from centre to detector edge r in mm [" << ans << "]: ";
			std::getline(std::cin,inp);
			if(inp.empty()) inp = ans;
			try { PDetr = stof(inp); }
			catch(const std::invalid_argument& ia) {
				std::cout << "\tInvalid distance. Must be numerical." << std::endl;
				goto retryPDetr;
			}
			allinp.push_back(inp);
			if(Qks!=nullptr) {
				std::cout << "Finally, enter details for Ge(Li) gamma-ray detectors." << std::endl;
				ans = readans(ansfile);
		retrygtotal:
				std::cout << "\tTotal number of gamma-ray detectors [" << ans << "]: ";
				std::getline(std::cin,inp);
				if(inp.empty()) inp = ans;
				if(catcherr(inp, ngamma)) goto retrygtotal;
				allinp.push_back(inp);
				if(!ans.empty()) pread = stoi(ans);
				else pread = 0;
				gD = new float[ngamma];
				gR = new float[ngamma];
				gL = new float[ngamma];
				gr = new float[ngamma];
				for(int i=0; i<ngamma; i++) {
					if(pread) ans = readans(ansfile);
		retrygD:
					std::cout << "\tGe crystal " << i+1 << " distance from source in mm [" << ans << "]: ";
					std::getline(std::cin,inp);
					if(inp.empty()) inp = ans;
					if(catcherr(inp, gD[i])) goto retrygD;
					gD[i] *= 0.1;
					allinp.push_back(inp);
					if(pread) ans = readans(ansfile);
		retrygL:
					std::cout << "\tGe crystal " << i+1 << " length in mm [" << ans << "]: ";
					std::getline(std::cin,inp);
					if(inp.empty()) inp = ans;
					if(catcherr(inp, gL[i])) goto retrygL;
					gL[i] *= 0.1;
					allinp.push_back(inp);
					if(pread) ans = readans(ansfile);
		retrygR:
					std::cout << "\tGe crystal " << i+1 << " outer radius in mm [" << ans << "]: ";
					std::getline(std::cin,inp);
					if(inp.empty()) inp = ans;
					if(catcherr(inp, gR[i])) goto retrygR;
					gR[i] *= 0.1;
					allinp.push_back(inp);
					if(pread) {
						ans = readans(ansfile);
						pread--;
					}
		retrygr:
					std::cout << "\tGe crystal " << i+1 << " inner radius in mm [" << ans << "]: ";
					std::getline(std::cin,inp);
					if(inp.empty()) inp = ans;
					if(catcherr(inp, gr[i])) goto retrygr;
					gr[i] *= 0.1;
					allinp.push_back(inp);
				}
				if(pread) {
					for(int i=0; i<pread; i++) {
						ans = readans(ansfile);
						ans = readans(ansfile);
						ans = readans(ansfile);
						ans = readans(ansfile);
					}
				}
			}
			
			// Write user answers to file
			ansfile.close();
			std::ofstream ansout;
			ansout.open(ansstr.c_str());
			if(!ansout.fail()) {
				for(auto outp : allinp) ansout << outp << std::endl;
			}
			ansout.close();
			
			for(int i=0; i<nstates; i++) {
				WDB_nuclvl nlvl;
				nlvl.spin = SS[i];
				nlvl.E = SE[i];
				nlvl.par = SP[i];
				nlvl.K_Band = 0;
				NucLevels.push_back(nlvl);
			}
			
			nMtrans = 0;
			nEtrans = 0;
			for(int i=0; i<ttrans; i++) {
				int m = 0;
				int e = 0;
				bool oddm = M[i] % 2;
				int l1 = Bl1[i];
				int l2 = Bl2[i];
				WDB_nuctrans ntran;
				ntran.lvl1 = Bl1[i];
				ntran.lvl2 = Bl2[i];
				ntran.B = std::sqrt(B[i]);
				ntran.M = M[i];
				if(!oddm && SP[l2-1]==SP[l1-1] || oddm && SP[l1-1]!=SP[l2-1]) {
					Etrans.push_back(ntran);
					nEtrans++;
				}
				else {
					Mtrans.push_back(ntran);
					nMtrans++;
				}
			}
			
			// Calculate Qk for each detector
			if(Qks!=nullptr) {
				for(int g=0; g<ngamma; g++) {
					int l2 = Bl2[trans1-1] - 1;
					int l1 = Bl1[trans1-1] - 1;
					double Et = NucLevels[l2].E - NucLevels[l1].E;
					std::vector<double> Qk;
					for(int k=0; k<=4; k++) {
						if(k%2) Qk.push_back(0.);
						else Qk.push_back(getQk(Et, gL[g], gR[g], gr[g], gD[g], double(k)));
					}
					GamR::AngDist::SolidAttenuation GamRQk(Qk);
					Qks->push_back(GamRQk);
				}
			}
			
			delete[] Bl1;
			delete[] Bl2;
			delete[] B;
			delete[] M;
			if(Qks!=nullptr) {
				delete[] gL;
				delete[] gR;
				delete[] gD;
				delete[] gr;
			}
		}
*/

    /*
		// Routine to facilitate stat tensors calculation. Calls ExperimentalSetup and then passes inputs to CoulexNucTensors to return the tensors. Returns a nullptr if there was an error.
		// Pass getQk by reference, or leave null to not get Qks.
		GamR::AngDist::StatTensor *DoCoulex(std::vector<GamR::AngDist::SolidAttenuation> *getQk = nullptr)
		{
			int Zp, Zt, ngam, nstates, tenslvl, nEt, nMt;
			double Ap, At, E, Q, Tt, Td, Px, Py, Pz, Pr;
			std::vector<WDB_nuclvl> nlvl;
			std::vector<WDB_nuctrans> Etrans, Mtrans;
			bool ProjDet, TgtEx;
			if(getQk==nullptr) ExperimentalSetup(Zp, Ap, Zt, At, ProjDet, TgtEx, E, Q, Tt, Td, Px, Py, Pz, Pr, ngam, nstates, nlvl, tenslvl, nEt, Etrans, nMt, Mtrans);
			else ExperimentalSetup(Zp, Ap, Zt, At, ProjDet, TgtEx, E, Q, Tt, Td, Px, Py, Pz, Pr, ngam, nstates, nlvl, tenslvl, nEt, Etrans, nMt, Mtrans, getQk);
			return CoulexNucTensors(Zp, Ap, Zt, At, ProjDet, TgtEx, E, Q, Td, Tt, tenslvl-1, nstates, nlvl, nEt, Etrans, nMt, Mtrans, Px, Py, Pz, Pr);
		}
  */
	}
}
