#ifndef GAMR_NUCLEUS_DRAWLEVELSCHEME_HH
#define GAMR_NUCLEUS_DRAWLEVELSCHEME_HH

#include <map>

#include <TArrow.h>
#include <TText.h>
#include <TLatex.h>
#include <TBox.h>
#include <TGaxis.h>
#include <TPolyLine.h>
#include <TLine.h> 

namespace GamR {
  namespace Nucleus {
    namespace LevelSchemeDraw {
      class Scheme;
      
      class State : public TNamed, public TAttLine {
      public:
        Scheme *fScheme;
        int index;
        Double_t fEnergy;
        Double_t fDrawPos;
        Double_t fLabelPos;
        Double_t fLeft;
        Double_t fRight;
        Double_t fExtLeft;
        Double_t fExtRight;
        
        double textsize = 0.05;
        std::string fLeftLab;
        std::string fRightLab;

        bool extension;
        TLine *extline = NULL;

        TLatex *fLeftLabel = NULL;
        TLatex *fRightLabel = NULL;
        State() : fEnergy(0), fDrawPos(0), fLabelPos(0), fLeft(0), fRight(1), extension(false) { SetLineColor(kBlack); fLeftLabel = new TLatex(); fRightLabel = new TLatex();}
        State(std::string name, Scheme *scheme, double energy, double left, double right, std::string leftlabel, std::string rightlabel, EColor color=kBlack) :
          TNamed(name, name),
          fEnergy(energy),
          fDrawPos(energy),
          fLabelPos(energy),
          fLeft(left),
          fRight(right),
          fScheme(scheme),
          fLeftLab(leftlabel),
          fRightLab(rightlabel),
          extension(false)
        { SetLineColor(color); SetLineWidth(3); fLeftLabel = new TLatex(); fRightLabel = new TLatex(); }
        ~State() { }
        void SetLeftRight(double left, double right) { fLeft = left; fRight = right; } // *MENU* *ARGS={left=>fLeft right=>fRight}
        void SetWidth(double width) { double cent = (fLeft + fRight)/2.0; fLeft = cent - width/2.0; fRight = cent + width/2.0; } // *MENU* *ARGS={width=>fRight-fLeft}
        void SetLabels(const char *leftlab, const char *rightlab) { fLeftLab = (std::string)leftlab; fRightLab = (std::string)rightlab; } // *MENU*
        void SetExtension(double left, double right) { fExtLeft = left; fExtRight = right; extension = true; extline = new TLine(); } // *MENU*
        void AddTransition(const char* name_fin, double width, double start, double stop, double labelpos = 0.5, EColor color=kBlack); // *MENU*
        Int_t DistancetoPrimitive(Int_t px, Int_t py);
        void ExecuteEvent(Int_t event, Int_t px, Int_t py);
        void Paint(Option_t *option="");
        bool operator<(const State &rhs) const { return fEnergy < rhs.fEnergy; }
        bool operator==(const State &rhs) const { return fEnergy == rhs.fEnergy; }

      private:
        bool p1;
        int px1, px2, pxold;
        ClassDef(State, 1);
      };
      class Transition : public TPolyLine {
      public:
        Scheme *fScheme;
        State *fInitial;
        State *fFinal;
        //these are experimentally observed things
        Double_t fStart;
        Double_t fStop;
        Double_t fWidth;
        Double_t fLabelPos;
        TText *fLabel = NULL;
        TBox *fLabelBox = NULL;
        double textsize = 0.05;
        Transition() : fInitial(NULL), fFinal(NULL), TPolyLine(), fStart(0.5), fStop(0.5), fLabelPos(0.5) { SetLineColor(kBlack); SetFillColor(kBlack); fLabel = new TText(); fLabelBox = new TBox(); SetPolyLine(7); }
        Transition(Scheme *scheme, State *initial, State *final, double width, double start, double stop, double labelpos, EColor color) :
          fScheme(scheme),
          TPolyLine(),
          fInitial(initial),
          fFinal(final),
          fWidth(width),
          fStart(start),
          fStop(stop),
          fLabelPos(labelpos)
        { SetLineColor(color); SetFillColor(color); fLabel = new TText(); fLabelBox = new TBox(); SetPolyLine(7); }
        ~Transition() {}
        void SetStartStop(double start, double stop) { fStart = start; fStop = stop; } // *MENU* *ARGS={start=>fStart stop=>fStop}
        void Paint(Option_t *option = "");
        Int_t DistancetoPrimitive(Int_t px, Int_t py);
        void ExecuteEvent(Int_t event, Int_t px, Int_t py);
        void Draw(Option_t *option = "") { TPolyLine::Draw(option); }
        double GetX1();
        double GetX2();
        double GetY1();
        double GetY2();
        double GetPerpTheta();
        double GetLength();
        double GetWidth();
        double GetWidthX();
        double GetWidthY();
        double GetHeadWidth();
        double GetHeadWidthX();
        double GetHeadWidthY();
        double GetHeadLength();
        void PaintArrow();

      private:
        bool p1,p2;
        int px1, px2, px1old, px2old;
        int py1, py2, py1old, py2old;
        double XtoAbsPixel(double x);
        double YtoAbsPixel(double y);
        double AbsPixeltoX(double xpix);
        double AbsPixeltoY(double ypix);

        ClassDef(Transition, 1);
      };
      class Scheme : public TNamed {
      public:
        std::map<std::string, State> fStates;
        std::vector<Transition> fTransitions;
        double ylo = 0;
        double yhi = 1e9;
        double xlo = 0.0;
        double xhi = 1.0;
        double textsize = 0.05;
        double fWidthScale = 0.01;
        
        TH2F *fDrawHist = NULL;
        TGaxis *fAxis = NULL;
        Scheme() { fDrawHist = new TH2F("", "", 100, xlo, xhi, 100, ylo, yhi); }
        Scheme(std::string name) : TNamed(name, name) { fDrawHist = new TH2F(name.c_str(), name.c_str(), 100, xlo, xhi, 100, ylo, yhi); }
        void AddState(std::string name, double energy, double left, double right, std::string leftlab, std::string rightlab, EColor color=kBlack) { State state(name, this, energy, left, right, leftlab, rightlab, color); state.textsize = textsize; fStates[name]=state; }
        void AddTransition(std::string initState, std::string finState, double width, double start, double stop, double labelpos=0.5, EColor color=kBlack) {
          Transition transition(this, &fStates[initState], &fStates[finState], width, start, stop, labelpos, color);
          transition.textsize = textsize;
          fTransitions.push_back(transition);
          
        }
        void SetDrawRange(double xlow, double xhigh, double eLow, double eHigh) { ylo = eLow; yhi = eHigh; xlo = xlow; xhi = xhigh; fDrawHist->SetBins(100, xlo, xhi, 100, ylo, yhi); }
        void SetTextSize(double size) {
          textsize = size;
          for (auto &state : fStates) {
            state.second.textsize = textsize;
          }
          for (auto &transition : fTransitions) {
            transition.textsize = textsize;
          }
        }
        void PaintArrow();
        void Paint(Option_t *option="");

        void ReadScheme(std::string filename);
        void WriteScheme(std::string filename);

        ClassDef(Scheme, 1);

      };
    }
  }
}


#endif
