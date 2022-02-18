/**
   @file
   @author Timothy Gray <timothy.gray@anu.edu.au>
   @section DESCRIPTION

   This file provides framework for defining Coulex experiments to do calculations using the WDB codes
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>

#include <angdist/AngDist.hh>
#include <toolkit/Misc.hh>
#include <utils/Utilities.hh>
#include "Eloss.hh"
#include "WDBSubs.hh"
#include "Coulex.hh"
#include "CoulexCalculation.hh"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

namespace GamR {
  namespace Coulex {
    /** 
        Print particle detector information
    */
    void ParticleDetector::Print() {
      printf("Dimensions: " ANSI_COLOR_BLUE "%3.1f" ANSI_COLOR_RESET "x" ANSI_COLOR_BLUE "%3.1f " ANSI_COLOR_RESET "mm\n", fWidth, fHeight);
      printf("Z = " ANSI_COLOR_BLUE "%5.2f" ANSI_COLOR_RESET " mm\n", fDistanceZ);
      printf("R = " ANSI_COLOR_BLUE "%5.2f" ANSI_COLOR_RESET " mm\n", fDistanceR);
    }

    /** 
        Draw particle detector setup
    */
    void ParticleDetector::DrawSetup() {
			std::cout << " ________________________" << std::endl;
			std::cout << "|     Top-down view      |" << std::endl;
			std::cout << "| Euler angle a rotates  |" << std::endl;
			std::cout << "| particle detector.     |" << std::endl;
			std::cout << "| Euler angle b rotates  |" << std::endl;
			std::cout << "| gamma detector.        |" << std::endl;
			std::cout << "|________________________|" << std::endl;
			std::cout << "|                        |" << std::endl;
			std::cout << "|Beam  Tgt           stop|" << std::endl;
			std::cout << "|=======|--------------[]|" << std::endl;
			std::cout << "|        <   z   >^      |" << std::endl;
			std::cout << "|                 r      |" << std::endl;
			std::cout << "|                 v      |" << std::endl;
			std::cout << "|                |\\y     |" << std::endl;
			std::cout << "|                | \\     |" << std::endl;
			std::cout << "|                | |     |" << std::endl;
			std::cout << "|                \\ |x    |" << std::endl;
			std::cout << "|                 \\|     |" << std::endl;
			std::cout << "|________________________|" << std::endl;
		}

    /**
       Format spin and parity nicely

       @return string containing spin and parity, i.e. 2+
    */
    std::string Level::PrintSP() {
      char out[10];
      if (fParity) {
        sprintf(out, "%5.1f+" , fSpin);
      }
      else {
        sprintf(out, "%5.1f-", fSpin);
      }
      std::string sout(out);
      return sout;
    }

    /**
       Gets character of transition.  

       @return true = electric, false = magnetic
    */
    bool Transition::Character() {
      bool diff_parity = (fInitial->fParity == fFinal->fParity);
      return ((pow(-1, fMult)==1)==diff_parity);  //E is true, M is false
    }

    /**
       Formats kind of transition nicely

       @return string containing type of transition, i.e. E2
    */    
    std::string Transition::Type() {
      if (Character()) {
        return "E"+std::to_string(fMult);
      }
      else {
        return "M"+std::to_string(fMult);
      }
    }

    Level* LevelScheme::GetLevelByIndex(int i) {
      for (auto &level : fLevels) {
        if (level.second->fIndex==i) {
          return level.second;
        }
      }
      return NULL;
    }

    /**
       Adds a level with specified name

       @param name Name of level
       @param energy Energy of level in MeV
       @param spin Spin of energy.  Make sure only integers or half integers are input, there's no check
       @param parity true = positive, false = negative
    */
    void LevelScheme::AddLevel(std::string name, float energy, float spin, bool parity) {
      fLevels[name] = new Level(name, energy, spin, parity, 0);
      fLevels[name]->fIndex = (int)fLevels.size()-1;
    }

    /** 
        Adds a level with name "l"+index

       @param energy Energy of level in MeV
       @param spin Spin of energy.  Make sure only integers or half integers are input, there's no check
       @param parity true = positive, false = negative
    */
    void LevelScheme::AddLevel(float energy, float spin, bool parity) {
      std::string name = "l"+std::to_string((int)fLevels.size());
      AddLevel(name, energy, spin, parity);
    }

    /** 
        Adds a transition

        @param initial string corresponding to name of initial (higher) state
        @param final string corresponding to name of final (lower) state
        @param mat_el matrix element in eb^(lambda - 1) for electric, not sure about magnetic
        @param multipolarity multipolarity of transition
    */
    void LevelScheme::AddTransition(std::string initial, std::string final, float mat_el, float multipolarity) {
      Level *init = fLevels[initial];
      Level *fin = fLevels[final];
      if (!init) {
        std::cout << "Warning! Initial state does not exist!" << std::endl;
        return;
      }
      if (!fin) {
        std::cout << "Warning! Final state does not exist!" << std::endl;
        return;
      }
        
      Transition* transition = new Transition(init, fin, mat_el, multipolarity);
      fTransitions.push_back(transition);      
    }    

    /** 
        Sets indices of every level in the scheme, ascending in energy order, starting from 0
    */
    void LevelScheme::SetIndices() {
      std::vector<Level*> levels;
      for (auto &level : fLevels) {
        levels.push_back(level.second);
      }

      std::sort(levels.begin(), levels.end(),
                [](const Level *a, const Level *b)
                { 
                  return *a < *b;
                });

      for (int i=0; i<(int)levels.size(); ++i) {
        fLevels[levels[i]->fName]->fIndex = i;
      }        
    }    

    /**
       Prints the states in the level scheme

       @param loi State index to highlight
    */
    void LevelScheme::PrintLevels(int loi/*=-1*/) {
      SetIndices();
      for (int i=0; i<(int)fLevels.size(); ++i) {
        Level *level = GetLevelByIndex(i);
        if (!level) { std::cout << "no level " << i << "?" << std::endl; }
        if (level->fIndex == loi) { std::cout <<  ANSI_COLOR_GREEN; }
        std::cout << level->fIndex << "     " << level->PrintSP() << "     " << level->fEnergy << std::endl;
        std::cout <<  ANSI_COLOR_RESET ;
      }
    }
    
    /**
       Prints the transitions in the level scheme

       @param toi Transition index to highlight
    */
    void LevelScheme::PrintTransitions(int toi/*=-1*/) {
      SetIndices();
      for (int i=0; i<(int)fTransitions.size(); ++i) {
        Transition *transition = fTransitions[i];
        if (i==toi) { std::cout <<  ANSI_COLOR_GREEN;}
        std::cout << "Transition " << i << " from " <<
          transition->fInitial->fIndex << " to " <<
          transition->fFinal->fIndex << std::endl;
        std::cout << "Energy       : " << transition->Energy() << std::endl;
        std::cout << "Type         : " << transition->Type() << std::endl;
        std::cout << "Reduced M.E. : " << transition->fMatEl << std::endl;
        std::cout <<  ANSI_COLOR_RESET ;
      }
    }

    /**
       Prints the states and transitions in the level scheme

       @param loi State index to highlight
       @param toi Transition index to highlight
    */
    void LevelScheme::Print(int loi/*=-1*/, int toi/*=-1*/) {
      std::cout << "Levels: " << std::endl;
      PrintLevels(loi);
      std::cout << "Transitions: " << std::endl;
      PrintTransitions(toi);
    }

    /**
       Gets a vector of levels in the format required by the WDB codes

       @return vector of WDB_nuclvl structs
    */
    std::vector<WDB_nuclvl> LevelScheme::GetLevels() {
      std::vector<Level*> levels;
      for (auto &level : fLevels) {
        levels.push_back(level.second);
      }
      std::sort(levels.begin(), levels.end(),
                [](const Level *a, const Level *b)
                { 
                  return *a < *b;
                });

      std::vector<WDB_nuclvl> wdb_lvls;
      for (int i=0; i<(int)levels.size(); ++i) {
        WDB_nuclvl lvl;
        lvl.spin = levels[i]->fSpin;
        lvl.E = levels[i]->fEnergy;
        lvl.par = levels[i]->fParity;
        lvl.K_Band = levels[i]->fKBand;
        wdb_lvls.push_back(lvl);
      }
      return wdb_lvls;
    }

    /**
       Gets a vector of electric transitions for the WDB codes

       @return vector of WDB_nuctrans structs containing electric transitions only
    */
    std::vector<WDB_nuctrans> LevelScheme::GetETransitions() {
      std::vector<WDB_nuctrans> wdb_trans;
      for (auto &transition : fTransitions) {
        if (transition->Character()==true) {
          WDB_nuctrans trans;
          trans.lvl2 = transition->fInitial->fIndex+1;
          trans.lvl1 = transition->fFinal->fIndex+1;
          trans.B = transition->fMatEl;
          trans.M = transition->fMult;
          wdb_trans.push_back(trans);
        }
      }
      return wdb_trans;
    }

    /**
       Gets a vector of magnetic transitions for the WDB codes

       @return vector of WDB_nuctrans structs containing magnetic transitions only
    */
    std::vector<WDB_nuctrans> LevelScheme::GetMTransitions() {
      std::vector<WDB_nuctrans> wdb_trans;
      for (auto &transition : fTransitions) {
        if (transition->Character()==false) {
          WDB_nuctrans trans;
          trans.lvl2 = transition->fInitial->fIndex+1;
          trans.lvl1 = transition->fFinal->fIndex+1;
          trans.B = transition->fMatEl;
          trans.M = transition->fMult;
          wdb_trans.push_back(trans);
        }
      }
      return wdb_trans;
    }

    /**
       Set the beam details through an interactive CLI
    */
    void CoulexCalculation::SetBeam() {
      std::cout << "Beam details: " << std::endl;
      std::string inp;
      int Z;
      double A;
      float energy = fBeamEnergy;
      while (true) {
        std::cout << "\tBeam nucleus [" << GamR::TK::GetElement(fBeam.Z, fBeam.A) << "]: ";
        std::getline(std::cin,inp);
        if (inp.empty()) { break; }
        if(GamR::TK::GetZA(inp,Z,A)) {
          std::cout << "\tInvalid nucleus. Ensure nucleus is in the format AEl, ElA or El-A e.g. 3He, Li5, C-13." << std::endl;        
        }
        else { 
          fBeam.Z = Z;
          if(A>0) fBeam.A = A;
          else {
			  if(!SCOEFloaded) loadSCOEF();
			  if(!SCOEFloaded) fBeam.A = A;
			  else fBeam.A = Eldat[Z-1][1];
	      }
          break;
        }
      }

      GamR::Utils::GetInput("\tBeam energy in MeV", energy);
      fBeamEnergy = energy;
    }

    /**
       Set the target details through an interactive CLI
    */
    void CoulexCalculation::SetTarget() {
      std::cout << "Target details: " << std::endl;
      std::string inp;
      int Z;
      double A;
      while (true) {
        std::cout << "\tTarget nucleus [" << GamR::TK::GetElement(fTarget.isotope.Z, fTarget.isotope.A) << "]: ";
        std::getline(std::cin,inp);
        if(inp.empty()) { break; }
        if(GamR::TK::GetZA(inp,Z,A)) {
          std::cout << "\tInvalid nucleus. Ensure nucleus is in the format AEl, ElA or El-A e.g. 3He, Li5, C-13." << std::endl;
        }
        else {
          fTarget.isotope.Z = Z;
          if(A>0) fTarget.isotope.A = A;
          else {
			  if(!SCOEFloaded) loadSCOEF();
			  if(!SCOEFloaded) fTarget.isotope.A = A;
			  fTarget.isotope.A = Eldat[Z-1][2];
          }
          break;
        }
			}
      float thickness = fTarget.thickness;
      GamR::Utils::GetInput("\tTarget thickness in mg/cm2", thickness);
      fTarget.thickness = thickness;

      float density = fTarget.density;
      GamR::Utils::GetInput("\tTarget density in g/cm3 (set 0 to get from SCOEF.DAT)", density, false);
      fTarget.density = density;
    }

    /**
       Set the details about which species is detected through an interactive CLI interface
    */
    void CoulexCalculation::SetDetected() {
      std::cout << "Detection details: " << std::endl;
      std::string inp;
      while (true) {
        std::cout << "\tProjectile(1) or target(2) detection [" << fDetected << "]: ";
        std::getline(std::cin,inp);
        if(inp.empty()) { break; }
        switch(inp[0]) {
				case '1':
					fDetected = Species::kProjectile;
					break;
				case '2':
					fDetected = Species::kTarget;
					break;
				default:
					continue;
        }
        if(fDetected==Species::kProjectile || fDetected==Species::kTarget) break;
      }
    }

    /**
       Set the details about which species is excited through an interactive CLI interface
    */
    void CoulexCalculation::SetExcited() {
      std::cout << "Excitation details: " << std::endl;
      std::string inp;
      while (true) {
        std::cout << "\tProjectile(1) or target(2) excitation [" << fExcited << "]: ";
        std::getline(std::cin,inp);
        if(inp.empty()) { break; }
        switch(inp[0]) {
        case '1':
          fExcited = Species::kProjectile;
          break;
        case '2':
          fExcited = Species::kTarget;
          break;
        default:
          continue;
        }
        if(fExcited==Species::kProjectile || fExcited==Species::kTarget) break;
      }
    }

    /**
       Set the level scheme through an interactive CLI interface
    */
    void CoulexCalculation::SetLevelScheme() {
      std::cout << "Level scheme details: " << std::endl;
      std::string inp;
      int nstates = fLevelScheme.GetNLevels();
      while (true) {
        GamR::Utils::GetInput("\tTotal states including ground state", nstates);
        if(nstates<2) {
          std::cout << "\tInvalid entry. Must be >1." << std::endl;
          continue;
        }
        break;
			}
      
			for(int i=0; i<nstates; i++) {
        Level *state = fLevelScheme.GetLevelByIndex(i);
        std::string sp;
        float energy = 0.0;
        bool parity = true;
        float spin = 0.0;        
        if (state) {
          energy = state->fEnergy;
          parity = state->fParity;
          spin = state->fSpin;          
        }
        
        if (parity) { sp = std::to_string(spin) + "+"; }
        else { sp = std::to_string(spin) + "-"; }

        GamR::Utils::GetInput("\tState "+std::to_string(i)+" energy in MeV", energy);

        while (true) {
          std::cout << "\tState " << i << " spin and parity [" << sp << "]: ";
          std::getline(std::cin,inp);
          if(inp.empty()) { break; }
          if(inp[inp.size()-1]=='+') parity = true;
          else if(inp[inp.size()-1]=='-') parity = false;
          else {
            std::cout << "\tParity not specified. Please specify spin and parity e.g. 0.5+" << std::endl;
            continue;
          }				
          try { spin = std::stof(inp.substr(0,inp.size()-1)); }
          catch(const std::invalid_argument& ia) {
            std::cout << "\tInvalid entry. Must be numerical." << std::endl;
            continue;
          }          
          if(spin<0) {
            std::cout << "\tInvalid entry. Must be >=0." << std::endl;
            continue;
          }
          break;
        }
        if (!state) {
          fLevelScheme.AddLevel(energy, spin, parity);
        }
        else {
          state->fEnergy = energy;
          state->fSpin = spin;
          state->fParity = parity;
        }
      }

      std::cout << std::endl;
      std::cout << "Levels: " << std::endl;
      fLevelScheme.PrintLevels();
      std::cout << std::endl;

      std::cout << "Transition details: " << std::endl;
      int ntrans = fLevelScheme.GetNTransitions();

      GamR::Utils::GetInput("\tTotal transitions between states", ntrans);
      
      for(int i=0; i<ntrans; i++) {
        Transition *transition = NULL;
        int isi = 0;
        int fsi = 0;
        float bup = 0;
        float mult = 0;
        if (i < (int)fLevelScheme.fTransitions.size()) {
          transition = fLevelScheme.fTransitions[i];
          isi = transition->fInitial->fIndex;
          fsi = transition->fFinal->fIndex;
          bup = transition->GetBUp();
          mult = transition->fMult;          
        }
          
        GamR::Utils::GetInput("\tTransition "+std::to_string(i)+" lower state number", fsi);
        GamR::Utils::GetInput("\tTransition "+std::to_string(i)+" upper state number", isi);

        Level *initial = fLevelScheme.GetLevelByIndex(isi);
        Level *final = fLevelScheme.GetLevelByIndex(fsi);

        GamR::Utils::GetInput("\tTransition "+std::to_string(i)+" B up in eb", bup);
        GamR::Utils::GetInput("\tTransition "+std::to_string(i)+" multipolarity", mult);

        if (!transition) {
          fLevelScheme.AddTransition(initial->fName, final->fName, 0, mult);
          fLevelScheme.fTransitions[(int)fLevelScheme.fTransitions.size()-1]->SetBUp(bup);
        }
        else {
          transition->fInitial = initial;
          transition->fFinal = final;
          transition->SetBUp(bup);
          transition->fMult = mult;
        }
      }
    }

    /**
       Set level and transition of interest through an interactive CLI interface
    */
    void CoulexCalculation::SetInterests() {
      std::cout << "State/transition of interest: " << std::endl;
      std::string inp;
      int loi = fLevelOfInterest;
      GamR::Utils::GetInput("\tState of interest", loi);
      fLevelOfInterest = loi;

      int toi = fTransitionOfInterest;
      GamR::Utils::GetInput("\tTransition of interest", toi);
      fTransitionOfInterest = toi;
    }
    
    void CoulexCalculation::SetParticleDet() {
	  DrawSetup();
      std::cout  << "Particle detector details:" << std::endl;
      std::string inp;
      float width = fParticleDetector.fWidth;
      float height = fParticleDetector.fHeight;
      float z = fParticleDetector.fDistanceZ;
      float r = fParticleDetector.fDistanceR;

      GamR::Utils::GetInput("\tDetector width x in mm", width);
      fParticleDetector.fWidth = width;
      GamR::Utils::GetInput("\tDetector height y in mm", height);
      fParticleDetector.fHeight = height;
      GamR::Utils::GetInput("\tHorizontal distance from target to detector z in mm", z, false);
      fParticleDetector.fDistanceZ = z;
      GamR::Utils::GetInput("\tRadial distance from the centre to detector edge r in mm", r, false);
      fParticleDetector.fDistanceR = r;
    }

    /**
       Read experimental information from a text "*.ans" file

       @param file_name File to read
       @return <0 means an error, 0 is success
    */
    int CoulexCalculation::ReadFromFile(std::string file_name /*= "Wtheta.ans"*/) {
      std::ifstream ansfile;
      ansfile.open(file_name.c_str());
      if(ansfile.fail()) {
        std::cout << "Could not open answer file " << file_name << std::endl;
      }
      std::string ans;
      ans = GamR::Utils::getline(ansfile);

      
      //Beam details

      //isotope
      int Z;
      double A;
      if(GamR::TK::GetZA(ans,Z,A)) {
				std::cout << "\tInvalid beam nucleus. Ensure nucleus is in the format AEl, ElA or El-A e.g. 3He, Li-5." << std::endl;
        return -1;
      }
      fBeam.Z = Z;
      if(A>0) fBeam.A = A;
      else {
		  if(!SCOEFloaded) loadSCOEF();
		  if(!SCOEFloaded) fBeam.A = A;
		  fBeam.A = Eldat[Z-1][1];
	  }

      //energy
      float energy;
			ans = GamR::Utils::getline(ansfile);
      if (GamR::Utils::catcherr(ans, energy)) {
        std::cout << "\tInvalid beam energy" << std::endl;
        return -2;
      }
      fBeamEnergy = energy;

      //Target details
      //isotope
      ans = GamR::Utils::getline(ansfile);
      if(GamR::TK::GetZA(ans,Z,A)) {
				std::cout << "\tInvalid taget nucleus. Ensure nucleus is in the format AEl, ElA or El-A e.g. 3He, Li-5." << std::endl;
        return -3;
      }
      fTarget.isotope.Z = Z;
      if(A>0) fTarget.isotope.A = A;
      else {
		  if(!SCOEFloaded) loadSCOEF();
		  if(!SCOEFloaded) fTarget.isotope.A = A;
		  fTarget.isotope.A = Eldat[Z-1][2];
	  }

      //thickness
      float thickness;
      ans = GamR::Utils::getline(ansfile);
      if(GamR::Utils::catcherr(ans, thickness)) {
        std::cout << "\tInvalid target thickness" << std::endl;
        return -4;
      }
      fTarget.thickness = thickness;
      
      //density
      float density;
      ans = GamR::Utils::getline(ansfile);
      if(GamR::Utils::catcherr(ans, density, false)) {
        std::cout << "\tInvalid target density" << std::endl;
        return -5;
      }
      fTarget.density = density;

      //species       
      ans = GamR::Utils::getline(ansfile);
			switch(ans[0]) {
      case '1':
        fExcited = Species::kProjectile;
        break;
      case '2':
        fExcited = Species::kTarget;
        break;
      default:
        std::cout << "\tInvalid projectile(1) or target(2) excitation" << std::endl;
        return -6;
      }

      ans = GamR::Utils::getline(ansfile);
			switch(ans[0]) {
      case '1':
        fDetected = Species::kProjectile;
        break;
      case '2':
        fDetected = Species::kTarget;
        break;
      default:
        std::cout << "\tInvalid projectile(1) or target(2) detection" << std::endl;
        return -7;
      }

      ans = GamR::Utils::getline(ansfile);
      int pread = 0;
      if(!ans.empty()) pread = std::stoi(ans);

      int nstates = 0;
      if (GamR::Utils::catcherr(ans, nstates)) {
        std::cout << "\nInvalid number of states" << std::endl;
        return -8;
      }
      
      if (nstates < 2) {
        std::cout << "\nInvalid number of states" << std::endl;
        return -9;
      }

      for (int i=0; i<nstates; ++i) {
        //energy
        if (pread) ans = GamR::Utils::getline(ansfile);
        float energy;
        try { energy = stof(ans); }
				catch(const std::invalid_argument& ia) {
					std::cout << "Invalid state energy. Must be numerical." << std::endl;
          return -10;
				}
				if(energy<0) {
					std::cout << "Invalid state energy. Must be >=0." << std::endl;
          return -11;
				}

        //spin and parity
        float spin;
        bool parity;
				if(pread) {
					ans = GamR::Utils::getline(ansfile);
					pread--;
        }
        if(ans[ans.size()-1]=='+') parity = true;
				else if(ans[ans.size()-1]=='-') parity = false;
				else {
					std::cout << "\tState parity not specified. " << std::endl;
          return -12;
				}
				try { spin = std::stof(ans.substr(0,ans.size()-1)); }
				catch(const std::invalid_argument& ia) {
					std::cout << "\tState spin invalid. Must be numerical." << std::endl;
          return -13;
				}
				if(spin<0) {
					std::cout << "\tState spin invalid. Invalid entry. Must be >=0." << std::endl;
          return -14;
				}

        fLevelScheme.AddLevel(energy, spin, parity);
      }    

      if(pread) {
        for(int i=0; i<pread; i++) {
          ans = GamR::Utils::getline(ansfile);
          ans = GamR::Utils::getline(ansfile);
        }
      }

      //level of interest
      ans = GamR::Utils::getline(ansfile);
      int loi = 0;
      if(GamR::Utils::catcherr(ans, loi)) {
        std::cout << "\tInvalid level of interest" << std::endl;
        return -15;
      }
      fLevelOfInterest = loi-1;

      //transitions
      int ntrans;
			ans = GamR::Utils::getline(ansfile);
			if(!ans.empty()) pread = std::stoi(ans);
			else pread = 0;

      if(GamR::Utils::catcherr(ans,ntrans)) {
        std::cout << "\tInvalid number of transitions" << std::endl;
        return -16;
      }

      for (int i=0; i<ntrans; ++i) {
        int i1, i2;
        float bup, mult;
        if(pread) ans = GamR::Utils::getline(ansfile);
        if(GamR::Utils::catcherr(ans, i1)) {
          std::cout << "\tInvalid lower state index" << std::endl;
          return -17;
        }

        if(pread) ans = GamR::Utils::getline(ansfile);
        if(GamR::Utils::catcherr(ans, i2)) {
          std::cout << "\tInvalid upper state index" << std::endl;
          return -18;
        }

        if(pread) ans = GamR::Utils::getline(ansfile);          
        if(GamR::Utils::catcherr(ans, bup)) {
          std::cout << "\tInvalid transition strength" << std::endl;
          return -19;
        }

        if(pread) {
          ans = GamR::Utils::getline(ansfile);
          pread--;
        }        
        if(GamR::Utils::catcherr(ans, mult)) {
          std::cout << "\tInvalid transition multiplicity" << std::endl;
          return -20;
        }

        fLevelScheme.AddTransition("l"+std::to_string(i2-1),
                                   "l"+std::to_string(i1-1),
                                   0,
                                   mult);
        fLevelScheme.fTransitions[(int)fLevelScheme.fTransitions.size()-1]->SetBUp(bup);
      }

      if(pread) {
				for(int i=0; i<pread; i++) {
					ans = GamR::Utils::getline(ansfile);
					ans = GamR::Utils::getline(ansfile);
					ans = GamR::Utils::getline(ansfile);
					ans = GamR::Utils::getline(ansfile);
				}
      }

      //transition of interest
      int toi;
      ans = GamR::Utils::getline(ansfile);
      if(GamR::Utils::catcherr(ans, toi)) {
        std::cout << "\tInvalid transition of interest" << std::endl;
        return -21;        
      }
      fTransitionOfInterest = toi-1;

      //particle detector
      float pdetx, pdety, pdetz, pdetr;
      ans = GamR::Utils::getline(ansfile);
      if(GamR::Utils::catcherr(ans, pdetx)) {
        std::cout << "\tInvalid particle detector X" << std::endl;
        return -22;
      }

      ans = GamR::Utils::getline(ansfile);
      if(GamR::Utils::catcherr(ans, pdety)) {
        std::cout << "\tInvalid particle detector Y" << std::endl;
        return -23;
      }

      ans = GamR::Utils::getline(ansfile);
			try { pdetz = stof(ans); }
			catch(const std::invalid_argument& ia) {
				std::cout << "\tInvalid particle detector Z distance. Must be numerical." << std::endl;
        return -24;
			}
			if(!pdetz) {
				std::cout << "\tInvalid particle detector Z distance. Must be non-zero." << std::endl;
        return -25;
			}

      ans = GamR::Utils::getline(ansfile);
      try { pdetr = stof(ans); }
			catch(const std::invalid_argument& ia) {
				std::cout << "\tInvalid particle detector R distance. Must be numerical." << std::endl;
        return -26;
			}
      fParticleDetector.fWidth = pdetx;
      fParticleDetector.fHeight = pdety;
      fParticleDetector.fDistanceZ = pdetz;
      fParticleDetector.fDistanceR = pdetr;

      fLevelScheme.SetIndices();

      return 0;
    }

    /**
       Save experimental details to a "*.ans" text file

       @param file_name File name to save to.  Existing file will be overwritten
    */
    void CoulexCalculation::SaveToFile(std::string file_name) {
      std::ofstream ansout;
      ansout.open(file_name.c_str());
      ansout << GamR::TK::GetElement(fBeam.Z, fBeam.A) << std::endl;
      ansout << fBeamEnergy << std::endl;
      ansout << GamR::TK::GetElement(fTarget.isotope.Z, fTarget.isotope.A) << std::endl;
      ansout << fTarget.thickness << std::endl;
      ansout << fTarget.density << std::endl;
      int Ex = 1;
      int Det = 1;
      if (fExcited==Species::kTarget) { Ex = 2; }
      if (fDetected==Species::kTarget) { Det = 2; }
      ansout << Ex << std::endl;
      ansout << Det << std::endl;
      ansout << fLevelScheme.GetNLevels() << std::endl;
      fLevelScheme.SetIndices();
      for (int i=0; i<fLevelScheme.GetNLevels(); ++i) {
        Level *level = fLevelScheme.GetLevelByIndex(i);
        ansout << level->fEnergy << std::endl;
        ansout << level->PrintSP() << std::endl;
      }
      ansout << fLevelOfInterest+1 << std::endl;
      ansout << fLevelScheme.GetNTransitions() << std::endl;
      for (int i=0; i<fLevelScheme.GetNTransitions(); ++i) {
        Transition *trans = fLevelScheme.fTransitions[i];
        ansout << trans->fFinal->fIndex+1 << std::endl;
        ansout << trans->fInitial->fIndex+1 << std::endl;
        ansout << trans->GetBUp() << std::endl;
        ansout << trans->fMult << std::endl;
      }
      ansout << fTransitionOfInterest+1 << std::endl;
      ansout << fParticleDetector.fWidth << std::endl;
      ansout << fParticleDetector.fHeight << std::endl;
      ansout << fParticleDetector.fDistanceZ << std::endl;
      ansout << fParticleDetector.fDistanceR << std::endl;
      ansout.close();
    }

    /**
       Set all information through interactive CLI interface.  Defaults are existing data
    */
    void CoulexCalculation::ExperimentalSetup() {
      SetBeam();
      SetTarget();
      SetDetected();
      SetExcited();
      SetLevelScheme();
      SetInterests();
      SetParticleDet();
    }

    /** 
        Print experiment summary
    */
    void CoulexCalculation::Print() {
      std::cout << "=====================================================" << std::endl;
      std::cout << "          COULEX CALCULATION PARAMETERS              " << std::endl;
      std::cout << "=====================================================" << std::endl;
      printf("Beam: " ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET ", " ANSI_COLOR_BLUE "%4.1f" ANSI_COLOR_RESET " MeV\n", GamR::TK::GetElement(fBeam.Z, fBeam.A).c_str(), fBeamEnergy);
      printf("Target: " ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "\n", GamR::TK::GetElement(fTarget.isotope.Z, fTarget.isotope.A).c_str());
      printf("        thickness = " ANSI_COLOR_BLUE "%5.2f" ANSI_COLOR_RESET " mg/cm^2\n", fTarget.thickness);
      printf("          density = " ANSI_COLOR_BLUE "%5.2f" ANSI_COLOR_RESET " g/cm^3\n", fTarget.density);
      if (fExcited==Species::kTarget) {
        printf( ANSI_COLOR_BLUE "Target" ANSI_COLOR_RESET " excitation, ");
      }
      else {
        printf( ANSI_COLOR_BLUE "Projectile" ANSI_COLOR_RESET " excitation, ");
      }

      if (fDetected==Species::kTarget) {
        printf("detecting the " ANSI_COLOR_BLUE "target" ANSI_COLOR_RESET "\n");
      }
      else {
        printf("detecting the " ANSI_COLOR_BLUE "projectile" ANSI_COLOR_RESET "\n");
      }
      std::cout << std::endl;
      std::cout << "Level Scheme: " << std::endl;
      fLevelScheme.Print(fLevelOfInterest, fTransitionOfInterest);
      std::cout << std::endl;
      std::cout << "Particle Detector: " << std::endl;
      fParticleDetector.Print();
      std::cout << "=====================================================" << std::endl;
      
    }

    /**
       Calculates the statistical tensor for the state of interest following Coulex Excitation

       @return statistical tensor of state of interest
    */
    GamR::AngDist::StatTensor *CoulexCalculation::CalcTensor() {
      bool ProjDet = false;
      bool TgtEx = false;
      std::vector<WDB_nuclvl> levels = fLevelScheme.GetLevels();
      std::vector<WDB_nuctrans> Etrans = fLevelScheme.GetETransitions();
      std::vector<WDB_nuctrans> Mtrans = fLevelScheme.GetMTransitions();
      double Q = -levels[fLevelOfInterest].E;  // Used in reaction kinematics, should be equal to the negative energy of the level of interest (state populated by coulex).
      
      if (fDetected==Species::kProjectile) { ProjDet = true; }
      if (fExcited==Species::kTarget) { TgtEx = true; }

      bool failbit = false;	// Keep track of whether a component of the routine has failed and return nullptr if it has after memory cleanup
	  
	  if(fBeam.A==0) {
		  if(!SCOEFloaded) loadSCOEF();
		  if(SCOEFloaded) fBeam.A = Eldat[fBeam.Z-1][1];
	  }
	  if(fTarget.isotope.A==0) {
		  if(!SCOEFloaded) loadSCOEF();
		  if(SCOEFloaded) fTarget.isotope.A = Eldat[fTarget.isotope.Z-1][2];
	  }
      int grouptype = int(TgtEx) + 1;
      int flag = setupcoulex(fBeam.Z, fBeam.A, fTarget.isotope.Z, fTarget.isotope.A, grouptype, levels, Etrans, Mtrans);
      // Check the setupcoulex routine was successful and post relevant errors
      switch(flag)
	{
	case 1:
	  std::cerr << "CRITICAL Could not create data file for coulex routine. Ensure you have write access to the working directory." << std::endl;
	  return nullptr;
	case 2:
	  std::cerr << "CRITICAL There was a problem reading the coulex data file. Please check you have read access to the working directory, and your inputs for the data file." << std::endl;
	  return nullptr;
	case 3:
	  std::cout << "NON-CRITICAL Could not remove the coulex routine data file. You may need to manually remove the file or it may already have been deleted." << std::endl;
	}

      // set stored cross sections to zero
      for (auto &mlevel: fLevelScheme.fLevels) {
	auto key = mlevel.first;
	auto level = mlevel.second;
	level->fCrossSection=0;
      }
      GamR::AngDist::StatTensor *retST = new GamR::AngDist::StatTensor(levels[fLevelOfInterest].spin);	// The GamR library stat tensor to return

      for (auto &mlevel: fLevelScheme.fLevels) {
	auto key = mlevel.first;
	auto level = mlevel.second;
			
	// Setup memory for stat tensors and cross-sections from coulex routine, calculate and get values.
	// Memory is delcared to 11 due to Simpson's rule integration requirement (n = 10 equal cuts = 11 values)
	float xsect;												// To get cross-section from coulex routine. Coulex routine uses floats and this is passed by reference.
	double *sfctrx = new double[11];							// Scaling factor for each x piece involving the cross-section and solid angle.
	double *sfctry = new double[11];							// Scaling factor for each y strip (x integral).
	double *sfctrz = new double[11];							// Scaling factor for each z plane (xy integral).
	double sfctr;												// Integral scaling factor.
	std::complex<double> ***rhox = new std::complex<double>**[11];			// Stat tensors for each x piece.
	std::complex<double> ***rhoy = new std::complex<double>**[11];			// Stat tensors for each y strip (x integral). Remaining memory is declared later in the Simps function.
	std::complex<double> ***rhoz = new std::complex<double>**[11];			// Stat tensors for each z plane (xy integral). Remaining memory is declared later in the Simps function.
	std::complex<double> **rhoi;												// Stat tensors for integral of x, y and z with only positive q values.
	for(int i=0; i<=10; i++) {
	  rhox[i] = new std::complex<double>*[3];
	  for(int k=0; k<3; k++) rhox[i][k] = new std::complex<double>[5];
	}
			
	// Use Eloss routine to get projectile energy at 10 target depths (z).
	double Tout, range;
	float Eint[11];
	Eint[0] = fBeamEnergy;
	float Tstep = fTarget.thickness / 10.;
	for(int i=1;i<=10;i++) Eint[i] = ELoss(fBeamEnergy, fBeam.Z, fTarget.isotope.Z, Tstep*float(i), fBeam.A, &Tout, &range, fTarget.isotope.A, fTarget.density);
	
	//std::cout << "\tCalculating tensors..." << std::endl;
	// Setup step segments and iterate over particle detector dimensions (x and y) and depth energies (z) to get rho values for integration
	double xstep = fParticleDetector.fWidth / 10.;		// Divide width into 10 steps
	double ystep = fParticleDetector.fHeight / 10.;		// Divide height into 10 steps
	for(int z=0; z<=10; z++) {							// z step calculated with Eloss routine
	  for(int y=0; y<=10; y++) {						// y step from bottom to top (relative to 0)
	    double ydist = (5-y) * ystep;
	    for(int x=0; x<=10; x++) {					// x step from left to right
	      double xdist = fParticleDetector.fDistanceR + x * xstep;
	      // Get lab scattering angle for coulex calculation and phi angle at this segment, then use Kinematics routine to determine CM angle.
	      double angh1, angh2, anglCM1, anglCM2, anghCM1, anghCM2, angCM;	// Angles
	      double Eh1, Eh2, El1, El2;										// Energies
	      double r = std::sqrt(ydist*ydist + xdist*xdist + fParticleDetector.fDistanceZ*fParticleDetector.fDistanceZ);			// Radial distance from target to segment
	      if(r<fParticleDetector.fDistanceZ) r = fParticleDetector.fDistanceZ;		// BUG FIX FOR PRECISION ERROR (when angle=0 r < Z???)
	      double angdet = std::acos(std::fabs(fParticleDetector.fDistanceZ)/r);							// Lab angle of particle detection segment
	      double angphi = std::atan2(ydist,xdist);												// Phi angle of particle detection segment
	      if(angphi>TMath::Pi()) angphi -= 2*TMath::Pi();											// If angle is > 180 deg change to negative equivalent
	      if(fParticleDetector.fDistanceZ<0) angdet = TMath::Pi() - angdet;						// Check if particles are detected back-scattered and correct angle if so
	      int flag;
	      if(ProjDet && fBeam.A < fTarget.isotope.A) {		// Light projectile is detected, get light CM angle for coulex.
		flag = Kinematics(fBeam.A,fTarget.isotope.A,fBeam.A,fTarget.isotope.A,Eint[z],Q,angdet,El1,El2,Eh1,Eh2,angh1,angh2,anglCM1,anglCM2,anghCM1,anghCM2);
		if(flag==-1) {
		  std::cerr << "Impossible particle-detection geometry! Check your values and try again (ensure horizontal detector distance is negative for back-scattered detection)." << std::endl;
		  failbit = true;
		  goto fail;
		}
		angCM = anglCM1 * rad2deg;	// The angle used for coulex calculation (projectile CM) in degrees
	      }
	      else if(!ProjDet && fBeam.A > fTarget.isotope.A) {	// Light target is detected, get heavy CM angle for coulex and rotate the phi angle by pi (heavy mass phi = detector phi + pi).
		flag = Kinematics(fBeam.A,fTarget.isotope.A,fTarget.isotope.A,fBeam.A,Eint[z],Q,angdet,El1,El2,Eh1,Eh2,angh1,angh2,anglCM1,anglCM2,anghCM1,anghCM2);
		if(flag==-1) {
		  std::cerr << "Impossible particle-detection geometry! Check your values and try again (ensure horizontal detector distance is negative for back-scattered detection)." << std::endl;
		  failbit = true;
		  goto fail;
		}
		angCM = anghCM1 * rad2deg;	// The angle used for coulex calculation (projectile CM) in degrees
		angphi += TMath::Pi();
	      }
	      else {
		std::cerr << "Bad reaction kinematics! Lighter nucleus must be detected after scattering." << std::endl;
		failbit = true;
		goto fail;
	      }
	      //if (level->fIndex==fLevelOfInterest) {
		// Calculate stat tensors at this segment
		//GP_AC_Tensors(Eint[z], angCM, fLevelOfInterest, rhox[x], xsect);
		GP_AC_Tensors(Eint[z], angCM, level->fIndex, rhox[x], xsect);
		sfctrx[x] = xsect * std::fabs(fParticleDetector.fDistanceZ) / std::pow(r,3) / xcmlr(angdet,anglCM1,fBeam.A,fTarget.isotope.A,Eint[z],Q,TgtEx);
		//level->fCrossSection += xsect * std::fabs(fParticleDetector.fDistanceZ) / std::pow(r,3) / xcmlr(angdet,anglCM1,fBeam.A,fTarget.isotope.A,Eint[z],Q,TgtEx);
		for(int k=0; k<3; k++) {
		  for(int q=0; q<=k*2; q++) {
		    std::complex<double> expqphi = std::exp(std::complex<double>(0, double(q)*angphi));
		    rhox[x][k][q] *= sfctrx[x] * expqphi;
		  }
		}
	      // } else {
	      // 	float tempxsect;
	      // 	std::complex<double> ***temprhox = new std::complex<double>**[11];
	      // 	for(int i=0; i<=10; i++) {
	      // 	  temprhox[i] = new std::complex<double>*[3];
	      // 	  for(int k=0; k<3; k++) temprhox[i][k] = new std::complex<double>[5];
	      // 	}
	      // 	GP_AC_Tensors(Eint[z], angCM, level->fIndex, temprhox[x], tempxsect);
	      // 	std::cout << key << " " << tempxsect << std::endl;
	      // 	level->fCrossSection += tempxsect * std::fabs(fParticleDetector.fDistanceZ) / std::pow(r,3) / xcmlr(angdet,anglCM1,fBeam.A,fTarget.isotope.A,Eint[z],Q,TgtEx);
	      // }
	    }
	    // Simpson's rule integral of x rows into y
	    rhoy[y] = GamR::Utils::Simps(rhox, 10, xstep);
	    sfctry[y] = GamR::Utils::Simps(sfctrx, 10, xstep);
	  }
	  // Simpson's rule integral of y strips into z
	  rhoz[z] = GamR::Utils::Simps(rhoy, 10, ystep);
	  sfctrz[z] = GamR::Utils::Simps(sfctry, 10, ystep);
	}
	// Final Simpson's rule integral of z planes then divide by integral sfctr to get average stat tensors, and assemble into GamR Stat Tensor form as return value.
	rhoi = GamR::Utils::Simps(rhoz, 10, Tstep);
	sfctr = GamR::Utils::Simps(sfctrz, 10, Tstep);
	level->fCrossSection = sfctr;
	if (level->fIndex==fLevelOfInterest) {
	  for(int k=0; k<3; k++) {
	    for(int q=0; q<=k*2; q++) { 
	      rhoi[k][q] /= sfctr;
	      retST->Set(k*2,q,rhoi[k][q]);
	      level->fStatTensor->Set(k*2,q,rhoi[k][q]);
	      if(q) {			// For each complementary negative q, correct phase factor then copy value.
		rhoi[k][q] *= std::pow(-1,q);
		retST->Set(k*2,-q,rhoi[k][q]);
		level->fStatTensor->Set(k*2,-q,rhoi[k][q]);
	      }
	    }
	  }
	} else {
	  for(int k=0; k<3; k++) {
	    for(int q=0; q<=k*2; q++) { 
	      rhoi[k][q] /= sfctr;
	      level->fStatTensor->Set(k*2,q,rhoi[k][q]);
	      if(q) {			// For each complementary negative q, correct phase factor then copy value.
		rhoi[k][q] *= std::pow(-1,q);
		level->fStatTensor->Set(k*2,-q,rhoi[k][q]);
	      }
	    }
	  }
	}
			
fail: // Goto point if there's an error in the routine so memory is cleared before exit
			// Clear heap
			for(int i=0; i<=10; i++) {
				for(int k=0; k<=2; k++) {
					if(i==0) delete[] rhoi[k];
					delete[] rhox[i][k];
					delete[] rhoy[i][k];
					delete[] rhoz[i][k];
				}
				if(i==0) delete[] rhoi;
				delete[] rhox[i];
				delete[] rhoy[i];
				delete[] rhoz[i];
			}
			delete[] rhox;
			delete[] rhoy;
			delete[] rhoz;
			delete[] sfctrx;
			delete[] sfctry;
			delete[] sfctrz;
			
			if(failbit) {
				delete retST;
				return nullptr;
			}
      }
      return retST;

    }

    GamR::Coulex::CoulexCalculation ExperimentalSetup(std::string file_name) {
      GamR::Coulex::CoulexCalculation calc;
      calc.ReadFromFile(file_name);
      calc.Print();
      calc.ExperimentalSetup();
      calc.SaveToFile(file_name);
      return calc;
    }
    
    GamR::AngDist::StatTensor *DoCoulex(std::string file_name) {
      GamR::Coulex::CoulexCalculation calc;
      calc.ReadFromFile(file_name);
      calc.Print();
      calc.ExperimentalSetup();
      calc.SaveToFile(file_name);
      return calc.CalcTensor();
    }
  }
}
