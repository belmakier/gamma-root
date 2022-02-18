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

#include <iostream>

#include <utils/Utilities.hh>
#include "SolidAttenuation.hh"


#include <Math/SpecFunc.h> /* legendre polynomials */
#include <TF1.h>

namespace GamR {
  namespace AngDist {
    /**
       SolidAttenuation constructor by explicit setting.

       @param Qk Vector containing desired Qk coefficients
    */
    SolidAttenuation::SolidAttenuation(std::vector<double> Qk)
    {
      this->Qk = Qk;
    }

    /**
       SolidAttenuation constructor for simple geometry and absorption.

       Calculates solid attenuation coefficients assuming a cylindrical geometry
       and optionally a simple 1-exp(-mu*x) absorption. See Appendix 9 of Alpha-
       Beta- Gamma-Ray Spectroscopy, Kai Siegbahn for details.

       @param distance Distance of the face of the crystal from the source
       @param radius Radius of the circular face of the detector
       @param kmax Maximum k to calculate
       @param absorbCoeff Absorption coefficient
    */

    SolidAttenuation::SolidAttenuation(double distance, double radius, int kmax /*=4*/, double absorbCoeff /*=-1*/)
    {
      double maxOpenAngle = atan(radius / distance);
      TF1 *func;
      if (absorbCoeff > 0) {
        func = new TF1("SolidAttenuationFunc",
                       "((x==0)*1 + (x>0)*(1-exp(-[1]*(([2]-[3]*sin(x))/sin(x)))))*"
                       "ROOT::Math::legendre([0], cos(x)) * sin(x)",
                       0, maxOpenAngle);
        func->SetParameter(2, radius);
        func->SetParameter(3, distance);
        func->SetParameter(1, absorbCoeff);
      } else {
        func = new TF1("SolidAttenuationFunc", "ROOT::Math::legendre([0], cos(x)) * sin(x)", 0, maxOpenAngle);
      }
      double J0 = 0;
      func->SetParameter(0, 0);

      J0 = func->Integral(0, maxOpenAngle);
      this->Qk.clear();
      this->Qk.push_back(1.);
      for (int ik = 1; ik <= kmax; ++ik) {
        func->SetParameter(0, ik);
        this->Qk.push_back(func->Integral(0, maxOpenAngle) / J0);
      }
      delete func;
    }

    //Estimates the attenuation coefficient of a typical Ge(Li) detector from a fit to data in Krane (1972) NIM 98, 205. Qk is rather insensitive to this value so an estimate is OK.
    double GetTauG(double E)
    {
      return 0.009425*std::pow(E,-2.5);
    }

    //Routine for calculating Qk coefficients for a coaxial Ge crystal detector with a 'dead' core. Translated from FORTRAN in Krane (1972) NIM 98, 205.
		//XL = detector length, R = active outer radius, A = active inner radius (or dead radius), D = detector distance from source, tau = gamma-ray absorption coefficient. Units are all in cm.
    //calculates for even k
		//PROVIDE UNITS IN mm!! XL = detector length, R = active outer radius, A = active inner radius (or dead radius), D = detector distance from source, tau = gamma-ray absorption coefficient.
    SolidAttenuation::SolidAttenuation(double distance, double length, double outer_radius, double inner_radius, double energy, int kmax/*=4*/)
		{
      this->Qk.clear();
      this->Qk.push_back(1.);
      distance /= 10.;
      length /= 10.;
      outer_radius /= 10.;
      inner_radius /= 10.;

      for (int k=1; k<=kmax; ++k) {
        if(k%2) {
            Qk.push_back(0.);
            continue;
        }
        double TAU = GetTauG(energy);
        double F[101];
        double B[4];
        double XJ[2] { 0 };
        double Qk;
        // Detector solid angles
        B[0] = std::atan2(inner_radius, distance+length);
        B[1] = std::atan2(inner_radius, distance);
        B[2] = std::atan2(outer_radius, distance+length);
        B[3] = std::atan2(outer_radius, distance);
        for(int n=0; n<2; n++) {
          double N = n + 1.;
          if(k==0 && N==2) break;
          int KA = int(k) * (2 - int(N)) + 1;
          for(int j=0; j<3; j++) {
            double J = j+1.;
            double YL = B[j];
            double YU = B[j + 1];
            double DL = (YU - YL) / 100.;
            for(int m=0; m<101; m++) {
              // Trigonometry and attenuation
              double M = m + 1.;
              double XM = YL + DL * (M - 1);
              double EX;
              switch(j) {
							case 0:
								EX = TAU * ( inner_radius - (distance + length) * std::tan(XM) ) / std::sin(XM);
								break;
							case 1:
								EX = -TAU * length / std::cos(XM);
								break;
							case 2:
								EX = TAU * ( distance * std::tan(XM) - outer_radius) / std::sin(XM);
              }
              // Legendre polynomials
              F[m] = std::sin(XM) * (1. - std::exp(EX));
              if(J==1) F[m] *= std::exp(-TAU * ( inner_radius / std::sin(XM) - distance / std::cos(XM)));
              F[m] *= ROOT::Math::legendre(KA-1, std::cos(XM));
            }
            // Simpson's rule integral
            XJ[n] += GamR::Utils::Simps(F, 100, DL);
          }
        }
        Qk = XJ[0] / XJ[1];
        this->Qk.push_back(Qk);
      }
		}


  } /* namespace AngDist */
} /* namespace GamR */
