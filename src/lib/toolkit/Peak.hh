#ifndef GAMR_TOOLKIT_PEAK_HH
#define GAMR_TOOLKIT_PEAK_HH

#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include <string>

/* ROOT */
#include <Rtypes.h>
#include <TBrowser.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TNamed.h>

#include <TF1.h>
#include <TMath.h>

#include "Gate.hh"

namespace GamR {
    /**
     \addtogroup TK (Toolkit)
     @{
  */

  //! Library for low-level but user-focused analysis.  A toolbox for generally
  //! useful physics analysis tools.
  namespace TK {
    
    enum PeakType { Gaussian, StepGaussian, OneTailGaussian, OneTailStepGaussian, TwoTailGaussian, TwoTailStepGaussian};  

    //Peak: something with area, amplitude, a centroid, and a width.
    class Peak {      
    public:
      virtual double GetArea() { return 0; }
      virtual double GetAreaError() { return 0; }
      virtual double GetAmp() { return 0; }
      virtual double GetAmpError() { return 0; }
      virtual double GetCent() { return 0; }
      virtual double GetCentError() { return 0; }
      virtual double GetWidth() { return 0; }
      virtual double GetWidthError() { return 0; }

      virtual void SetAmp(double amp) {}
      virtual void SetAmpError(double error) {}
      virtual void SetCent(double cent) {}
      virtual void SetCentError(double error) {}
      virtual void SetWidth(double width) {}
      virtual void SetWidthError(double error) {}      
    };

    //Basic peak : no functional form
    class BPeak : public Peak, public TNamed, public TAttLine {
    private:
      double Area;
      double AreaError;
      double Counts;
      double CountsError;
      double Amp;
      double AmpError;
      double Cent;
      double CentError;
      double Width;
      double WidthError;

      GamR::TK::Gate mPeak;
      std::vector<GamR::TK::Gate > mBackgrounds;

      TF1 *linear;
      TF1 *backlow;
      TF1 *backhigh;

      double Lowest;
      double Highest;
      
      void Set(TH1 *hist, GamR::TK::Gate peak, TF1 *background); //actually calculates area     
      
      void Paint(Option_t *option = "same");
      Int_t DistancetoPrimitive(Int_t px, Int_t py);
      void ExecuteEvent(Int_t event, Int_t px, Int_t py);

      //helper class
      class LFit {
        TH1D *back;
      public: 
        LFit(TH1D *background) { back = background; }        
        double operator() (double *x, double *p) { return back->GetBinContent(back->FindBin(x[0])) + p[0] + x[0]*p[1]; }
      };
      
    public :      
      BPeak();
      ~BPeak();
      double GetArea() { return Area; }
      double GetAreaError() { return AreaError; }
      double GetCounts() { return Counts; }
      double GetCountsError() { return CountsError; }
      double GetAmp() { return Amp; }
      double GetAmpError() { return AmpError; }
      double GetCent() { return Cent; }
      double GetCentError() { return CentError; }
      double GetWidth() { return Width; }
      double GetWidthError() { return WidthError; }
      void Set(TH1 *hist, double x1, double y1, double x2, double y2);
      void Set(TH1 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background, Option_t *foption="", Option_t *option="sl");
      void Set(TH1 *hist, GamR::TK::Gate peak, GamR::TK::Gate background, Option_t *foption="", Option_t *option="sl");

      void SetCont(TH1 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background, Option_t *foption="", Option_t *option=""); //for continuous
      void SetPoint(TH1 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background, Option_t *foption="", Option_t *option=""); //for point
      void SetStep(TH1 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background, Option_t *foption="", Option_t *option=""); //for step
      
      
      void Set(TH1 *hist, Option_t *foption="", Option_t *option="sl");
      void Set(TH2 *hist, Option_t *foption="", Option_t *option="sl");
      void Print();

      void Delete(Option_t *option) { this->~BPeak(); } // *MENU*

      ClassDef(BPeak, 1);
    };

    //"Function Peak" - a peak with a pre-defined shape
    class FPeak : public Peak {
    protected :
      //int iTails1;
      //int iTails2;
      //int iStep;
      
      TF1 *fPeakFunc;
      double fLow;
      double fHigh;
      PeakType fPeakType;
      //double fArea;
      //double fAreaError;

    public :
      FPeak() {}
      FPeak(double Low, double High, PeakType Type) : fLow(Low), fHigh(High), fPeakType(Type) {}
      virtual ~FPeak() {};
      //Peak(int Tails1, int Tails2, int Step) { iTails1 = Tails1; iTails2 = Tails2; iStep = Step; }
      TF1 *GetFunc() { return fPeakFunc; }
      PeakType GetPeakType() { return fPeakType; }

      virtual TF1 *GetStepFunc() { return NULL; }
      virtual TF1 *GetGaussFunc() { return NULL; }
      virtual void SetParameters(std::vector<double> params) {}
      virtual void SetParErrors(std::vector<double> errors) {}

      //void SetFunc(TF1 *func) { fPeakFunc = func; }
      //void SetArea(double area) { fArea = area; }
      //void SetAreaError(double area_error) { fAreaError = area_error; }
    };

    class GaussianPeak : public FPeak {
    public :
      GaussianPeak () {};
      GaussianPeak (double Low, double High);
      ~GaussianPeak() {};
      double GetArea() { return sqrt(2 * TMath::Pi()) * fPeakFunc->GetParameter(0) *
          fabs(fPeakFunc->GetParameter(2)); }
      double GetAreaError() { return sqrt(2 * TMath::Pi() *
                                   (pow(fPeakFunc->GetParError(0) * fPeakFunc->GetParameter(2), 2) +
                                    pow(fPeakFunc->GetParError(2) * fPeakFunc->GetParameter(0), 2))); }
      double GetAmp() { return fPeakFunc->GetParameter(0); }
      double GetAmpError() { return fPeakFunc->GetParError(0); }
      double GetCent() { return fPeakFunc->GetParameter(1); }
      double GetCentError() { return fPeakFunc->GetParError(1); }
      double GetWidth() { return 2.3548*fPeakFunc->GetParameter(2); }
      double GetWidthError() { return 2.3548*fPeakFunc->GetParError(2); }

      void SetParameters(std::vector<double> params) { for (int i=0; i<(int)params.size(); ++i) { fPeakFunc->SetParameter(i, params[i]); } }
      void SetParErrors(std::vector<double> errors) { for (int i=0; i<(int)errors.size(); ++i) { fPeakFunc->SetParError(i, errors[i]); } }
      void SetAmp(double amp) { fPeakFunc->SetParameter(0, amp); }
      void SetAmpError(double error) { fPeakFunc->SetParError(0, error); }
      void SetCent(double cent) { fPeakFunc->SetParameter(1, cent); }
      void SetCentError(double error) { fPeakFunc->SetParError(1, error); }
      void SetWidth(double width) { fPeakFunc->SetParameter(2, width/2.3548); }
      void SetWidthError(double error) { fPeakFunc->SetParError(2, error/2.3548); }

      TF1 *GetStepFunc() { return NULL; }
      TF1 *GetGaussFunc() { TF1 *gaussfunc = new TF1("GaussFunc", "[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))", fLow, fHigh);
        gaussfunc->SetParameter(0, fPeakFunc->GetParameter(0));
        gaussfunc->SetParameter(1, fPeakFunc->GetParameter(1));
        gaussfunc->SetParameter(2, fPeakFunc->GetParameter(2));
        return gaussfunc;
      }
    };

    class StepGaussianPeak : public FPeak {
    public:
      StepGaussianPeak () {};
      StepGaussianPeak (double Low, double High);
      ~StepGaussianPeak() {};
      double GetArea() { return sqrt(2 * TMath::Pi()) * fPeakFunc->GetParameter(0) *
          fabs(fPeakFunc->GetParameter(2)); }
      double GetAreaError() { return sqrt(2 * TMath::Pi() *
                                          (pow(fPeakFunc->GetParError(0) * fPeakFunc->GetParameter(2), 2) +
                                           pow(fPeakFunc->GetParError(2) * fPeakFunc->GetParameter(0), 2))); }
      double GetAmp() { return fPeakFunc->GetParameter(0); }
      double GetAmpError() { return fPeakFunc->GetParError(0); }
      double GetCent() { return fPeakFunc->GetParameter(1); }
      double GetCentError() { return fPeakFunc->GetParError(1); }
      double GetWidth() { return 2.3548*fPeakFunc->GetParameter(2); }
      double GetWidthError() { return 2.3548*fPeakFunc->GetParError(2); }

      void SetParameters(std::vector<double> params) { for (int i=0; i<(int)params.size(); ++i) { fPeakFunc->SetParameter(i, params[i]); } }
      void SetParErrors(std::vector<double> errors) { for (int i=0; i<(int)errors.size(); ++i) { fPeakFunc->SetParError(i, errors[i]); } }
      void SetAmp(double amp) { fPeakFunc->SetParameter(0, amp); }
      void SetAmpError(double error) { fPeakFunc->SetParError(0, error); }
      void SetCent(double cent) { fPeakFunc->SetParameter(1, cent); }
      void SetCentError(double error) { fPeakFunc->SetParError(1, error); }
      void SetWidth(double width) { fPeakFunc->SetParameter(2, width/2.3548); }
      void SetWidthError(double error) { fPeakFunc->SetParError(2, error/2.3548); }

      TF1 *GetStepFunc() { TF1 *stepfunc = new TF1("StepFunc", "[0]*([3]/100)*std::erfc((x-[1])/(sqrt(2)*[2]))", fLow, fHigh);
        stepfunc->SetParameter(0, fPeakFunc->GetParameter(0));
        stepfunc->SetParameter(1, fPeakFunc->GetParameter(1));
        stepfunc->SetParameter(2, fPeakFunc->GetParameter(2));
        stepfunc->SetParameter(3, fPeakFunc->GetParameter(3));
        return stepfunc;
      }

      TF1 *GetGaussFunc() { TF1 *gaussfunc = new TF1("GaussFunc", "[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))", fLow, fHigh);
        gaussfunc->SetParameter(0, fPeakFunc->GetParameter(0));
        gaussfunc->SetParameter(1, fPeakFunc->GetParameter(1));
        gaussfunc->SetParameter(2, fPeakFunc->GetParameter(2));
        return gaussfunc;
      }

    };

    class OneTailGaussianPeak : public FPeak {
    public:
      OneTailGaussianPeak ();
      OneTailGaussianPeak (double Low, double High);
      ~OneTailGaussianPeak();
      double GetArea() { return fPeakFunc->Integral(fLow, fHigh); }
      double GetAreaError();
      double GetAmp() { return fPeakFunc->GetParameter(0); }
      double GetAmpError() { return fPeakFunc->GetParError(0); }
      double GetCent() { return fPeakFunc->GetParameter(1); }
      double GetCentError() { return fPeakFunc->GetParError(1); }
      double GetWidth() { return 2.3548*fPeakFunc->GetParameter(2); }
      double GetWidthError() { return 2.3548*fPeakFunc->GetParError(2); }

      void SetParameters(std::vector<double> params) { for (int i=0; i<(int)params.size(); ++i) { fPeakFunc->SetParameter(i, params[i]); } }
      void SetParErrors(std::vector<double> errors) { for (int i=0; i<(int)errors.size(); ++i) { fPeakFunc->SetParError(i, errors[i]); } }
      void SetAmp(double amp) { fPeakFunc->SetParameter(0, amp); }
      void SetAmpError(double error) { fPeakFunc->SetParError(0, error); }
      void SetCent(double cent) { fPeakFunc->SetParameter(1, cent); }
      void SetCentError(double error) { fPeakFunc->SetParError(1, error); }
      void SetWidth(double width) { fPeakFunc->SetParameter(2, width/2.3548); }
      void SetWidthError(double error) { fPeakFunc->SetParError(2, error/2.3548); }

      TF1 *GetStepFunc() { return NULL; }
      TF1 *GetGaussFunc() { TF1 *gaussfunc = new TF1("GaussFunc", "[0]*(1-[3]/100)*exp(-pow(x-[1],2)/(2*pow([2],2)))", fLow, fHigh);
        gaussfunc->SetParameter(0, fPeakFunc->GetParameter(0));
        gaussfunc->SetParameter(1, fPeakFunc->GetParameter(1));
        gaussfunc->SetParameter(2, fPeakFunc->GetParameter(2));
        gaussfunc->SetParameter(3, fPeakFunc->GetParameter(3));
        return gaussfunc;
      }
    };

    class OneTailStepGaussianPeak : public FPeak {
    public:
      OneTailStepGaussianPeak () {};
      OneTailStepGaussianPeak (double Low, double High);
      ~OneTailStepGaussianPeak() {};
      double GetArea();
      double GetAreaError();
      double GetAmp() { return fPeakFunc->GetParameter(0); }
      double GetAmpError() { return fPeakFunc->GetParError(0); }
      double GetCent() { return fPeakFunc->GetParameter(1); }
      double GetCentError() { return fPeakFunc->GetParError(1); }
      double GetWidth() { return 2.3548*fPeakFunc->GetParameter(2); }
      double GetWidthError() { return 2.3548*fPeakFunc->GetParError(2); }

      void SetParameters(std::vector<double> params) { for (int i=0; i<(int)params.size(); ++i) { fPeakFunc->SetParameter(i, params[i]); } }
      void SetParErrors(std::vector<double> errors) { for (int i=0; i<(int)errors.size(); ++i) { fPeakFunc->SetParError(i, errors[i]); } }
      void SetAmp(double amp) { fPeakFunc->SetParameter(0, amp); }
      void SetAmpError(double error) { fPeakFunc->SetParError(0, error); }
      void SetCent(double cent) { fPeakFunc->SetParameter(1, cent); }
      void SetCentError(double error) { fPeakFunc->SetParError(1, error); }
      void SetWidth(double width) { fPeakFunc->SetParameter(2, width/2.3548); }
      void SetWidthError(double error) { fPeakFunc->SetParError(2, error/2.3548); }

      TF1 *GetStepFunc() { TF1 *stepfunc = new TF1("StepFunc", "[0]*([3]/100)*std::erfc((x-[1])/(sqrt(2)*[2]))", fLow, fHigh);
        stepfunc->SetParameter(0, fPeakFunc->GetParameter(0));
        stepfunc->SetParameter(1, fPeakFunc->GetParameter(1));
        stepfunc->SetParameter(2, fPeakFunc->GetParameter(2));
        stepfunc->SetParameter(3, fPeakFunc->GetParameter(5));
        return stepfunc;
      }
      TF1 *GetGaussFunc() { TF1 *gaussfunc = new TF1("GaussFunc", "[0]*(1-[3]/100)*exp(-pow(x-[1],2)/(2*pow([2],2)))", fLow, fHigh);
        gaussfunc->SetParameter(0, fPeakFunc->GetParameter(0));
        gaussfunc->SetParameter(1, fPeakFunc->GetParameter(1));
        gaussfunc->SetParameter(2, fPeakFunc->GetParameter(2));
        gaussfunc->SetParameter(3, fPeakFunc->GetParameter(3));
        return gaussfunc;
      }
    };

    class TwoTailGaussianPeak : public FPeak {
    public:
      TwoTailGaussianPeak () {};
      TwoTailGaussianPeak (double Low, double High);
      ~TwoTailGaussianPeak() {};
      double GetArea() { return fPeakFunc->Integral(fLow, fHigh); }
      double GetAreaError();
      double GetAmp() { return fPeakFunc->GetParameter(0); }
      double GetAmpError() { return fPeakFunc->GetParError(0); }
      double GetCent() { return fPeakFunc->GetParameter(1); }
      double GetCentError() { return fPeakFunc->GetParError(1); }
      double GetWidth() { return 2.3548*fPeakFunc->GetParameter(2); }
      double GetWidthError() { return 2.3548*fPeakFunc->GetParError(2); }

      void SetParameters(std::vector<double> params) { for (int i=0; i<(int)params.size(); ++i) { fPeakFunc->SetParameter(i, params[i]); } }
      void SetParErrors(std::vector<double> errors) { for (int i=0; i<(int)errors.size(); ++i) { fPeakFunc->SetParError(i, errors[i]); } }
      void SetAmp(double amp) { fPeakFunc->SetParameter(0, amp); }
      void SetAmpError(double error) { fPeakFunc->SetParError(0, error); }
      void SetCent(double cent) { fPeakFunc->SetParameter(1, cent); }
      void SetCentError(double error) { fPeakFunc->SetParError(1, error); }
      void SetWidth(double width) { fPeakFunc->SetParameter(2, width/2.3548); }
      void SetWidthError(double error) { fPeakFunc->SetParError(2, error/2.3548); }

      TF1 *GetStepFunc() { return NULL; }
      TF1 *GetGaussFunc() { TF1 *gaussfunc = new TF1("GaussFunc", "[0]*(1 - [3]/100 - [4]/100)*exp(-pow(x-[1],2)/(2*pow([2],2)))", fLow, fHigh);
        gaussfunc->SetParameter(0, fPeakFunc->GetParameter(0));
        gaussfunc->SetParameter(1, fPeakFunc->GetParameter(1));
        gaussfunc->SetParameter(2, fPeakFunc->GetParameter(2));
        gaussfunc->SetParameter(3, fPeakFunc->GetParameter(3));
        gaussfunc->SetParameter(4, fPeakFunc->GetParameter(5));
        return gaussfunc;
      }
    };
    
    class TwoTailStepGaussianPeak : public FPeak {
    public:
      TwoTailStepGaussianPeak () {};
      TwoTailStepGaussianPeak (double Low, double High);
      ~TwoTailStepGaussianPeak() {};
      double GetArea();
      double GetAreaError();
      double GetAmp() { return fPeakFunc->GetParameter(0); }
      double GetAmpError() { return fPeakFunc->GetParError(0); }
      double GetCent() { return fPeakFunc->GetParameter(1); }
      double GetCentError() { return fPeakFunc->GetParError(1); }
      double GetWidth() { return 2.3548*fPeakFunc->GetParameter(2); }
      double GetWidthError() { return 2.3548*fPeakFunc->GetParError(2); }

      void SetParameters(std::vector<double> params) { for (int i=0; i<(int)params.size(); ++i) { fPeakFunc->SetParameter(i, params[i]); } }
      void SetParErrors(std::vector<double> errors) { for (int i=0; i<(int)errors.size(); ++i) { fPeakFunc->SetParError(i, errors[i]); } }
      void SetAmp(double amp) { fPeakFunc->SetParameter(0, amp); }
      void SetAmpError(double error) { fPeakFunc->SetParError(0, error); }
      void SetCent(double cent) { fPeakFunc->SetParameter(1, cent); }
      void SetCentError(double error) { fPeakFunc->SetParError(1, error); }
      void SetWidth(double width) { fPeakFunc->SetParameter(2, width/2.3548); }
      void SetWidthError(double error) { fPeakFunc->SetParError(2, error/2.3548); }
      
      TF1 *GetStepFunc() { TF1 *stepfunc = new TF1("StepFunc", "[0]*([3]/100)*std::erfc((x-[1])/(sqrt(2)*[2]))", fLow, fHigh);
        stepfunc->SetParameter(0, fPeakFunc->GetParameter(0));
        stepfunc->SetParameter(1, fPeakFunc->GetParameter(1));
        stepfunc->SetParameter(2, fPeakFunc->GetParameter(2));
        stepfunc->SetParameter(3, fPeakFunc->GetParameter(7));
        return stepfunc;
      }
      TF1 *GetGaussFunc() { TF1 *gaussfunc = new TF1("GaussFunc", "[0]*(1 - [3]/100 - [4]/100)*exp(-pow(x-[1],2)/(2*pow([2],2)))", fLow, fHigh);
        gaussfunc->SetParameter(0, fPeakFunc->GetParameter(0));
        gaussfunc->SetParameter(1, fPeakFunc->GetParameter(1));
        gaussfunc->SetParameter(2, fPeakFunc->GetParameter(2));
        gaussfunc->SetParameter(3, fPeakFunc->GetParameter(3));
        gaussfunc->SetParameter(4, fPeakFunc->GetParameter(5));
        return gaussfunc;
      }
    };

    BPeak* FitBPeak(TCanvas *canvas = gPad->GetCanvas(), Option_t *foption="", Option_t *option="sl");
    BPeak* ClickBPeak(TCanvas *canvas = gPad->GetCanvas());
  }  
}

#endif
        
