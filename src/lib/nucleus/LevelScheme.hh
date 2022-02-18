#ifndef GAMR_NUCLEUS_LEVELSCHEME_HH
#define GAMR_NUCLEUS_LEVELSCHEME_HH

#include <map>

#include <TArrow.h>
#include <TText.h>
#include <TGaxis.h>

namespace GamR {
  namespace Nucleus {
    namespace LevelScheme {
      class State : public TNamed, public TAttLine {
      public:
        int index;
        Double_t fEnergy;
        Double_t fUncertainty;
        Double_t fDrawPos;
        Double_t fLabelPos;
        TText *fLabel = NULL;
        State() : fEnergy(0), fUncertainty(0), fDrawPos(0), fLabelPos(0) { SetLineColor(kBlack); fLabel = new TText(); }
        State(std::string name, double energy, EColor color=kBlack) : TNamed(name, name), fEnergy(energy), fUncertainty(0.01*energy), fDrawPos(energy), fLabelPos(energy) { SetLineColor(color); fLabel = new TText(); }
        ~State() { }
        Int_t DistancetoPrimitive(Int_t px, Int_t py);
        void ExecuteEvent(Int_t event, Int_t px, Int_t py);
        void Paint(Option_t *option="");
        bool operator<(const State &rhs) const { return fEnergy < rhs.fEnergy; }
        bool operator==(const State &rhs) const { return fEnergy == rhs.fEnergy; }
        ClassDef(State, 1);
      };
      class Transition : public TArrow {
      public:
        State *fInitial;
        State *fFinal;
        //these are experimentally observed things
        Double_t fEnergy;
        Double_t fUncertainty;
        TText *fLabel = NULL;
        Transition() : fInitial(NULL), fFinal(NULL), fEnergy(0), fUncertainty(0), TArrow() { SetLineColor(kBlack); SetFillColor(kBlack); SetArrowSize(0.02); SetOption("|>"); fLabel = new TText(); }
        Transition(State *initial, State *final, double energy, double uncertainty, EColor color) :
          fInitial(initial),
          fFinal(final),
          fEnergy(energy),
          fUncertainty(uncertainty)
        { SetLineColor(color); SetFillColor(color); SetArrowSize(0.01); SetOption("|>"); fLabel = new TText(); }
        ~Transition() {}
        void Paint(Option_t *option = "");
        Int_t DistancetoPrimitive(Int_t px, Int_t py);
        void ExecuteEvent(Int_t event, Int_t px, Int_t py);
        void Draw(Option_t *option = "") { TArrow::Draw(option); }

        bool operator<(const Transition &rhs) const { return fEnergy < rhs.fEnergy; }
        
        ClassDef(Transition, 1);
      };
      class Scheme : public TNamed {
      public:
        std::map<std::string, State> fStates;
        std::vector<Transition> fTransitions;
        double drawLow = 0;
        double drawHigh = 1e9;
        TH2F *fDrawHist = NULL;
        TGaxis *fAxis = NULL;
        Scheme() { fDrawHist = new TH2F("", "", 100, 0.0, 1.0, 100, drawLow, drawHigh); }
        Scheme(std::string name) : TNamed(name, name) { fDrawHist = new TH2F(name.c_str(), name.c_str(), 100, 0.0, 1.0, 100, drawLow, drawHigh); }
        State* GetStateByIndex(int i);
        void AddState(std::string name, double energy, EColor color=kBlack) { State state(name, energy, color); fStates[name]=state; }
        void SetIndices();
        void AddTransition(std::string initState, std::string finState, double energy, double uncertainty, EColor color=kBlack) {
          Transition transition(&fStates[initState], &fStates[finState], energy, uncertainty, color);
          fTransitions.push_back(transition);
          
        }
        void SetDrawRange(double eLow, double eHigh) { drawLow = eLow; drawHigh = eHigh; }
        double GetChiSquared();
        void Fit();
        void PrintStates();
        void PrintTransitions();
        void Print();
        void SaveTable(std::string filename);
        void PrintState(std::string name);
        void Paint(Option_t *option="");

        ClassDef(Scheme, 1);
      private:
        class GlobalChiSquare;      

      };
    }
  }
}


#endif
