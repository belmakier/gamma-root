/**
   @file
   @author Timothy Gray <timothy.gray@anu.edu.au>
   @section DESCRIPTION

   This file provides framework for defining Coulex experiments to do calculations using the WDB codes
*/

#ifndef GAMR_COULEX_COULEXCALCULATION_HH
#define GAMR_COULEX_COULEXCALCULATION_HH

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
#include "Coulex.hh"

namespace GamR {
	namespace Coulex {
    /**
       Nucleus struct
    */
    struct Nucleus {
      int Z;
      float A;
    };

    /**
       Target struct
    */
    struct Target {
      Nucleus isotope;
      float density;
      float thickness;      
    };

    /**
       Enum for excited/detected species
    */
    enum Species { kNone = 0, kProjectile = 1, kTarget = 2 };

    class Level {
    public:
      int fIndex;
      std::string fName;
      float fEnergy;
      float fSpin;
      bool fParity;
      int fKBand;
      float fCrossSection;
      GamR::AngDist::StatTensor *fStatTensor;
      
      Level(std::string name, float energy, float spin, bool parity, int kband) :
        fName(name),
        fIndex(0),
        fEnergy(energy),
        fSpin(spin),
        fParity(parity),
        fKBand(kband),
	fCrossSection(0)
      {
	fStatTensor = new GamR::AngDist::StatTensor(2.);
      };
                                                                                                        
      bool operator<(const Level &rhs) const { return fEnergy < rhs.fEnergy; }
      std::string PrintSP();
    };

    /**
       Transition class.  Only pure transitions - i.e. mixed transitions should be considered two separate transitions.
    */
    class Transition {
    public:
      Level *fInitial;
      Level *fFinal;
      float fMatEl;
      int fMult;

      Transition(Level* initial, Level* final, float mat_el, int mult) :
        fInitial(initial),
        fFinal(final),
        fMatEl(mat_el),
        fMult(mult) {}
      void SetMatEl(float mat_el) { fMatEl = mat_el; }
      /**
         Sets the internally stored matrix element by specifying the transition strength B(final->initial)

         @param b_up transition strength B(final->initial)
      */
      void SetBUp(float b_up) { fMatEl = std::sqrt(b_up*(2*fFinal->fSpin+1.0)); }
      /**
         Gets the B(final->initial) strength from the matrix element

         @return B(final->initial) transition strength
      */
      float GetBUp() { return fMatEl*fMatEl/(2*fFinal->fSpin+1.0); }
      /**
         Gets transition energy
         
         @return Transition energy in MeV
      */
      float Energy() {return fInitial->fEnergy - fFinal->fEnergy;}
      bool Character();
      std::string Type();
    };

    /** 
        LevelScheme class to contain the (previously known) level scheme
    */
    class LevelScheme {
    public:
      std::map<std::string, Level*> fLevels;
      std::vector<Transition*> fTransitions;

      void AddLevel(std::string name, float energy, float spin, bool parity);
      void AddLevel(float energy, float spin, bool parity);
      void AddTransition(std::string initial, std::string final, float mat_el, float multipolarity);
      void SetIndices();
      void PrintLevels(int loi=-1);
      void PrintTransitions(int toi=-1);
      void Print(int loi=-1, int toi=-1);
      Level* GetLevelByIndex(int i);
      int GetNLevels() { return (int)fLevels.size(); }
      int GetNTransitions() { return (int)fTransitions.size(); }
      std::vector<WDB_nuclvl> GetLevels();
      std::vector<WDB_nuctrans> GetETransitions();
      std::vector<WDB_nuctrans> GetMTransitions();
    };

    /**
       Rudimentary particle detector - at this stage only rectangular, with very fixed geometry
    */
    class ParticleDetector {
    public:
      float fWidth;
      float fHeight;
      float fDistanceZ;
      float fDistanceR;

      void Print();
      void DrawSetup();
    };

    class CoulexCalculation {
    public:
      Nucleus fBeam;
      Target fTarget;
      Species fDetected = Species::kNone;
      Species fExcited = Species::kNone;
      float fBeamEnergy;
      LevelScheme fLevelScheme;
      ParticleDetector fParticleDetector;
      int fLevelOfInterest;
      int fTransitionOfInterest;

      void SetBeam(int Z, float A, float energy) {fBeam.Z = Z; fBeam.A = A; fBeamEnergy = energy; }
      void SetBeam(std::string isotope, float energy) { int Z; double A; GamR::TK::GetZA(isotope, Z, A); SetBeam(Z, A, energy); }
      
      void SetTarget(int Z, float A, float density, float thickness) {fTarget.isotope.Z = Z; fTarget.isotope.A = A; fTarget.density = density; fTarget.thickness = thickness; }
      void SetTarget(std::string isotope, float density, float thickness) { int Z; double A; GamR::TK::GetZA(isotope, Z, A); SetTarget(Z, A, density, thickness); }
      void SetDetected(Species detected) { fDetected = detected; }
      void SetExcited(Species excited) { fExcited = excited; }
      void SetParticleDet(float width, float height, float z, float r) { fParticleDetector.fWidth = width;
        fParticleDetector.fHeight = height; fParticleDetector.fDistanceZ = z; fParticleDetector.fDistanceR = r; }
      void SetInterests(int loi, int toi) { fLevelOfInterest = loi; fTransitionOfInterest = toi; }

      int ReadFromFile(std::string file_name = "Wtheta.ans");
      void SaveToFile(std::string file_name = "Wtheta.ans");
      
      //interactive versions
      void SetBeam();
      void SetTarget();
      void SetDetected();
      void SetExcited();
      void SetLevelScheme();
      void SetInterests();
      void SetParticleDet();
      
      void ExperimentalSetup();

      void Print();      
      GamR::AngDist::StatTensor *CalcTensor();
    };

    GamR::Coulex::CoulexCalculation ExperimentalSetup(std::string file_name = "Wtheta.ans");
    GamR::AngDist::StatTensor *DoCoulex(std::string file_name = "Wtheta.ans");
  }
}

#endif
