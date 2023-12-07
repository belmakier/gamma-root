#ifndef GAMR_SPECT_FITGUESSES_HH
#define GAMR_SPECT_FITGUESSES_HH

#include <vector>
#include <iostream>                             
#include <string>
#include <fstream>

#include <RtypesCore.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TROOT.h>
#include <TSpectrum.h>

namespace GamR {
  namespace Spect {
    struct Parameter {
      double val;
      double low;
      double high;
    };
    
    class PeakFitGuesses {
    public:
      Parameter fWidth;
      Parameter fStepAmp;
      Parameter fSkewAmp;
      Parameter fSkewWidth;
      Parameter fSkewAmp2;
      Parameter fSkewWidth2;
      Parameter fScale; //goes between area and counts, only used for printing


    public:
      PeakFitGuesses() {
        //default values
        fStepAmp = {1.,0.,20.};
        fSkewAmp = {10,0,100};
        fSkewWidth = {2.5,0,10};
        fSkewAmp2 = {5,0,100};
        fSkewWidth2 = {5,0,10};
        fScale = {1.0, 1.0, 1.0};
      }      

      int Load(std::string filename);

      void Print();
      void Save(std::string filename);
      void Save();
      void Set(int i, double val, double low, double high);
      void Set();

    };

    extern PeakFitGuesses *gFitGuesses;
    
    int LoadGuesses(std::string path);

    void Init();
  }
}

#endif
