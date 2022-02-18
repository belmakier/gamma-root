/*
 * The stopping-power routines below were derived from SRModule.exe of the SRIM-2013 software package (www.srim.org), copyright to J. L. Zeigler.
 * The data upon which they are based (SCOEF03.dat and SNUC03.dat) are also copied from the SRIM2013 software, copyright to J. L. Zeigler.
 * These routines and data have been replicated as per article 3 of the SRIM.com user agreement. The relevant legal notices are reproduced below and must be abided by when using this code: 
  
 *  Program name: SRIM  (PC version only)
 *    Copyright: SRIM.com, 1984 , 1986, 1989, 1991, 1992, 1994, 1995, 1998, 2000, 2003, 2008, 2011. All Rights Reserved
 *
 *  SRIM.com Research Software Disclaimer
 *    As experimental, research software, this program is provided free of charge on an "as is" basis without warranty of any kind, either expressed or implied, including but not limited to implied warranties of merchantability and fitness for a particular purpose. SRIM.com does not warrant that the functions contained in this program will meet the user's requirements or that the operation of this program will be uninterrupted or error-free. Acceptance and use of this program constitutes the user's understanding that he will have no recourse to SRIM.com for any actual or consequential damages, including, but not limited to, lost profits or savings, arising out of the use or inability to use this program. Even if the user informs SRIM.com of the possibility of such damages, SRIM.com expects the user of this program to accept the risk of any harm arising out of the use of this program, or the user shall not attempt to use this program for any purpose.
 *
 *  User agreement:
 *    By acceptance and use of this experimental program the user agrees to the following:
 *      This program is provided for the user's personal, non-commercial, experimental use and the user is granted permission to copy this program to the extent reasonably required for such use.
 *      All title, ownership and rights to this program and its associated files and any copies remain with SRIM.com, irrespective of the ownership of the media on which the program resides.
 *      The user is permitted to create non-commercial derivative works to this program. However, all copies of the program and its derivative works must contain the SRIM.com copyright notice, the Experimental Software Disclaimer and this User Agreement.
 *      By furnishing this program to the user, SRIM.com does NOT grant either directly or by implication, estoppel, or otherwise any license under any patents, patent applications, trademarks, copyrights or other rights belonging to SRIM.com or to any third party, except as expressly provided herein.
 *      The user understands and agrees that this program and its associated files, and any derivative works, are to be used solely for experimental uses and are not to be sold, distributed to a commercial organization, or be commercially exploited in any manner.
 */

#ifndef GAMR_COULEX_ELOSS_HH
#define GAMR_COULEX_ELOSS_HH
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>

namespace GamR {
	namespace Coulex {
		extern bool SCOEFloaded;					// Switch to indicate SCOEF data status
		extern double Eldat[92][5];                 // Element properties, where [0] = A (Most Abundant Isotope), [1] = mass (M.A.I), [2] = mass (atomic), [3] = density (g/cm^3), [4] = density (atoms/cm^3).

		// Combined SCOEF03.dat and SNUC03.dat from SRIM2013
		void loadSCOEF();

		// Electron energy loss. E is ion energy in keV/u, Z is the nuclear charge of the (b)eam and (t)arget.
		double S_e(double E, int Zb, int Zt);

		// Nuclear energy loss. E is ion energy in keV, Z is the nuclear charge of the (b)eam and (t)arget, and M is the mass of the (b)eam and (t)arget in Daltons.
		double S_n(double E, int Zb, int Zt, double Mb = 0, double Mt = 0);

		// Returns electronic and nuclear stopping in units of MeV/(mg cm^-2). E is the ion energy in MeV, Z is the nuclear charge of the (b)eam and (t)arget, M is the mass in u of the (b)eam and (t)arget (Mt is optional and will obtain value from SCOEF is set to 0).
		double dEdx(double E, int Zb, int Zt, double Mb = 0, double Mt = 0);

		/* Energy in MeV, Z is (b)eam and (t)arget nuclear charge, Tt is target thickness in mg/cm2, M is the mass in u of the (b)eam and (t)arget (can be set to zero, in which case beam will be most abundant isotope and target will be average atomic mass). acc determines the steps in the Runge-Kutta integration.
		 * Returns the exit energy from the foil, if provided the transit/stopping time into ttime, and if the ion stops and the pointer provided, puts the ion range into the pointer passed to range.*/
		double ELoss(double E, int Zb, int Zt, double Tt, double Mb = 0, double* ttime = nullptr, double* range = nullptr, double Mt = 0, double denst = 0, long acc = 1000);
	}
}
#endif
