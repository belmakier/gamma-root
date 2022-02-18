#ifndef GAMR_NUCLEUS_TRANSITION_HH
#define GAMR_NUCLEUS_TRANSITION_HH

#include <map>
#include <iostream>
#include <string>

/* ROOT */
#include <Rtypes.h>
#include <TNamed.h>

/* GAMR */
#include <toolkit/Gate.hh>

namespace GamR {
  namespace Nucleus {

    class Transition : public TNamed {
    protected:
      GamR::TK::Gate fPeak;
      std::vector<GamR::TK::Gate> fBackground;
      double fEnergy = 0;
    public:
      Transition(double E=0, double PL=0, double PH=4096, double BL=0, double BH=4096) :
        fPeak(PL,PH), fEnergy(E) {if (BL!=0 || BH!=4096) {fBackground.push_back(GamR::TK::Gate(BL,BH));}}
      void SetEnergy(double E) { fEnergy = E; }
      void SetPeak() { std::cout << "Setting peak: " << std::endl; fPeak.SetGate(); }
      void SetPeak(double Low, double High) { fPeak.SetGate(Low, High); }
      void SetBackground() { std::cout << "Setting background: " << std::endl; GamR::TK::Gate tempgate; tempgate.SetGate(); fBackground.push_back(tempgate); }      
      void SetBackground(double Low, double High) { GamR::TK::Gate tempgate; tempgate.SetGate(Low, High); fBackground.push_back(tempgate); }
      void AddBackground();
      void AddBackground(double Low, double High);
      void SetTransition() { SetPeak(); SetBackground(); }
      double Apply(TH1D *hist) const;
      double ApplyError(TH1D *hist) const;
      double ApplyCounts(TH1D *hist) const;
      double ApplyCountsError(TH1D *hist) const;
      double GetEnergy() { return fEnergy; }
      const GamR::TK::Gate* GetGate() const { return &fPeak; }
      const GamR::TK::Gate* GetGateBG() const { return &(fBackground[0]); }
      const std::vector<GamR::TK::Gate>* GetGateBGs() const { return &fBackground; }

      ClassDef(Transition, 2);
    };

    class TransitionMap: public TNamed {
    private:
      std::map<std::string, Transition > fMap;
    public:
      TransitionMap() {};
      TransitionMap(const char *name) : TNamed(name, name) {};
      TransitionMap(const char *name, std::string asciimapfilename);
      Transition& operator[] (std::string key){ return fMap[key]; }
      std::map<std::string, Transition > *GetMap() { return &fMap; }
      void ReadFile(std::string asciimapfilename);
      void WriteFile(std::string asciimapfilename);
      void ls(Option_t *option = "") const
      {
        (void)option;
        printf("Key                 Peak Low    Peak High   Background Low    Background High\n");
        for (auto i = fMap.begin(); i != fMap.end(); ++i) {
          for (int ibackgate = 0; ibackgate<(i->second.GetGateBGs())->size(); ++ibackgate ) {
            printf("%-20s%-12.2f%-12.2f%-18.2f%-18.2f\n", (i->first).c_str(),
                   (double)((i->second).GetGate()->GetLow()),
                   (double)((i->second).GetGate()->GetHigh()),
                   (double)((*(i->second).GetGateBGs())[ibackgate].GetLow()),
                   (double)((*(i->second).GetGateBGs())[ibackgate].GetHigh()));
          }
        }
      }

      /// \cond CLASSIMP
      ClassDef(TransitionMap, 2)
      /// \endcond
    };

  }
}

#endif
