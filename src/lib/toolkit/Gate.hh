#ifndef GAMR_TOOLKIT_GATE_HH
#define GAMR_TOOLKIT_GATE_HH

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <iostream>

/* ROOT */
#include <Rtypes.h>
#include <TBrowser.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TNamed.h>

namespace GamR {
  /**
     \addtogroup TK (Toolkit)
     @{
  */

  //! Library for low-level but user-focused analysis.  A toolbox for generally
  //! useful physics analysis tools.
  namespace TK {

    /**
       Basic 1D gate object for analysis
    */
    class Gate : public TNamed, public TAttLine, public TAttFill {
    private:
      double Low;
      double High;

    public:
      Gate()
      {
        SetLineColor(8);
        SetFillStyle(3003);
        SetFillColor(8);
      };
      Gate(const char *name);
      Gate(const char *name, const char *title);
      Gate(const char *name, TVirtualPad *canvas, Option_t *opt="");
      Gate(const char *name, const char *title, TVirtualPad *canvas, Option_t *opt="");
      Gate(TVirtualPad *canvas, Option_t *opt="");
      Gate(double l, double h) : Gate()
      {
        Low = l;
        High = h;
        Valid();
      };
      ~Gate() { };
      
      int SetGate(); // *MENU*
      int SetGate(TVirtualPad *canvas, Option_t *opt="");
      void SetGate(double l, double h)
      {
        Low = l;
        High = h;
        Valid();
      };
      void SetLow(double l) { Low = l; Valid(); }; // *MENU* *ARGS={l=>Low}
      void SetLow(std::string l) { std::stringstream(l) >> Low; Valid();};
      void SetHigh(double h) { High = h; Valid();}; // *MENU* *ARGS={h=>High}
      void SetHigh(std::string h) { std::stringstream(h) >> High; Valid();};
      double GetLow() const { return Low; };
      double GetHigh() const { return High; };
      double GetWidth() const { return High - Low; };
      int GetBinLow(TH1 *hist) const { return hist->FindBin(Low); }
      int GetBinHigh(TH1 *hist) const { return hist->FindBin(High); }
      int GetBinWidth(TH1 *hist) const { return hist->FindBin(High) - hist->FindBin(Low) + 1; };
      double GetTrueWidth(TH1 *hist) const { return hist->GetBinLowEdge(GetBinHigh(hist)+1) - hist->GetBinLowEdge(GetBinLow(hist)); }
        
      double GetIntegral(TH1 *hist) const;
      double GetIntegral(TH1 *hist, Gate background) const;
      double GetIntegral(TH1 *hist, Gate backLow, Gate backHigh) const;
      double GetIntegral(TH1 *hist, std::vector<Gate> background) const;
      double GetIntegralError(TH1 *hist) const;
      double GetIntegralError(TH1 *hist, Gate background) const;
      double GetIntegralError(TH1 *hist, std::vector<Gate> background) const;
      double GetCounts(TH1 *hist) const;
      double GetCounts(TH1 *hist, Gate background) const;
      double GetCounts(TH1 *hist, std::vector<Gate> background) const;
      double GetCountsError(TH1 *hist) const;
      double GetCountsError(TH1 *hist, Gate background) const;
      double GetCountsError(TH1 *hist, std::vector<Gate> background) const;
      void Browse(TBrowser *b);
      Bool_t Pass(double x)
      {
        return ((x >= Low) && (x <= High));
      }
      Bool_t Pass(double x) const
      {
        return ((x >= Low) && (x <= High));
      }
      template <size_t Meas, class TDetector>
      Bool_t PassDetector(TDetector det, Bool_t calibrated = kTRUE, Int_t id = -1);
      TH1D *ApplyX(TH2 *hist) const;                   // don't know if there's a way to return the same
      TH1D *ApplyX(TH2 *hist, const char *name) const; // kind of histogram as passed?
      TH1D *ApplyY(TH2 *hist) const;
      TH1D *ApplyY(TH2 *hist, const char *name) const;
      void Norm(TH1 *hist, TH1 *ref);
      void NormBackSub(TH1 *hist, TH1 *ref, Gate background);
      void Paint(Option_t *option = "same");
      Int_t DistancetoPrimitive(Int_t px, Int_t py);
      void ExecuteEvent(Int_t event, Int_t px, Int_t py);
      Bool_t IsFolder() const { return kTRUE; };
      void ls(Option_t *option = "") const;

      Bool_t Valid() {
        if (this->Low > this->High) {
          std::cout << "Warning! Gate low edge is higher than high edge" << std::endl;
        }
        return false;
      }

      /// \cond CLASSIMP
      ClassDef(Gate, 2);
      // version 1: no inheritance from TAttLine or TAttFill, not drawing
      /// \endcond
    };

    std::ostream &operator<<(std::ostream &os, Gate const &g);

    /**
       ROOT wrapper for a std::map of GamR::TK::Gates, with std::string keys. Allows
       users to save a single object to a ROOT file which contains an arbitrary
       number of gates which can then be fetched easily later in analysis or by
       different macros and programs.
    */
    class GateMap : public TNamed {
    private:
      std::map<std::string, Gate > fMap;

    public:
      GateMap(){};
      GateMap(const char *name) : TNamed(name, name){};
      GateMap(const char *name, const char *title) : TNamed(name, title){};
      Gate &operator[](std::string key) { return fMap[key]; };
      Bool_t IsFolder() const { return kTRUE; };
      void Browse(TBrowser *b);
      void ls(Option_t *option = "") const;
      Bool_t PassAny(double x) const
      {
        return std::any_of(fMap.cbegin(), fMap.cend(),
                           [&x](const std::pair<std::string, Gate> &g) { return g.second.Pass(x); });
      }

      /// \cond CLASSIMP
      ClassDef(GateMap, 1)
      /// \endcond
    };
  } // namespace TK
  /* @} */
} // namespace GamR

#endif
