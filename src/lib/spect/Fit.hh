#ifndef GAMR_SPECT_FIT_HH
#define GAMR_SPECT_FIT_HH

#include <vector>

#include <RtypesCore.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraph.h>
#include <TROOT.h>
#include <TSpectrum.h>

#include <toolkit/Peak.hh>
#include "FitGuesses.hh"

namespace GamR {
  namespace Spect {
        
    class PeakFit {
    public:
      struct PeakParams {   //for storing indices
        int iAmplitude;
        int iCentroid;
        int iWidth;
        int iSkewWidth;        // Beta        
        int iSkewAmplitude;    // R           
        int iSkewWidth2;       // Beta for tail 2
        int iSkewAmplitude2;   // R for tail 2
        int iStepAmplitude;    // Step        
      };
      
      struct Parameters {
        int iQuiet;
        int iFixWidths;
        int iFixWidthsFile;
        int iQuadBack;
        int iConstantBack;
        int iStep;
        int iTails1;
        int iTails2;        
        int iFixEnergy;
        int iNoFit;
      };

    private :
      TF1 *fBackground;
      TF1 *fTotal;
      double fChi2;
      double fLow;
      double fHigh;
      int fNData;
      int fNPars;

      TGraph *gWidth = NULL;
      TGraph *gStep = NULL;
      TGraph *gSkew = NULL;
      TGraph *gSkewAmp = NULL;
      TGraph *gSkew2 = NULL;
      TGraph *gSkewAmp2 = NULL;
      
      GamR::TK::PeakType fPeakType;
      //std::vector<GamR::TK::Peak*> fPeaks;
      std::map<std::string,GamR::TK::FPeak*> fPeaks;      
      std::map<int, std::string> fPeakKeys;
      std::map<std::string,int> fPeakEnFix;

      int iParamCount;

      Parameters parameters;
      
      //std::vector<PeakParams> fPeakParamInds;
      std::map<std::string,PeakParams> fPeakParamInds; 
      GamR::TK::FPeak *FindPeak (int i) {
        int k=0;
        for (auto &peak : fPeaks) {
          auto key = peak.first;
          auto val = peak.second;
          if (i==k) {
            return val;
          }
          ++k;
        }
        return NULL;
      }
    public:
      PeakFitGuesses *fFitGuesses;
      
    public:
      PeakFit();
      PeakFit(double Low, double High);
      PeakFit(double Low, double High, PeakFitGuesses *FitGuesses);
      void GetClick(Int_t,Int_t,Int_t,TObject* selected);
      GamR::TK::PeakType GetPeakType() { return fPeakType; }
      TF1 *GetBackground() { return fBackground; }
      TF1 *GetTotal() { return fTotal; }
      double GetChi2() { return fChi2; }
      double GetLow() { return fLow; }
      double GetHigh() { return fHigh; }
      size_t GetNPeaks() { return fPeaks.size(); }

      int GetParamCount() { return iParamCount ; }
      //option flags
      int GetFixWidths() { return parameters.iFixWidths ; }
      int GetQuadBack() { return parameters.iQuadBack ; }
      int GetStep() { return parameters.iStep ; }
      int GetTails1() { return parameters.iTails1 ; }
      int GetTails2() { return parameters.iTails2 ; }
      
      void SetParamCount(int i) { iParamCount = i; }
      //option flags
      void SetFixWidths(int i) { parameters.iFixWidths = i; }
      void SetQuadBack(int i) { parameters.iQuadBack = i; }
      void SetStep(int i) { parameters.iStep = i; }
      void SetTails1(int i) { parameters.iTails1 = i; }
      void SetTails2(int i) { parameters.iTails2 = i; }
      
      void SetOpts(Option_t *option);
      void SetBackground();
      void SetPeaks(std::vector<double> Peaks);
      void SetPeaks(std::map<std::string,double> Peaks);
      void SetGuesses();
      void SetGuesses(TH1* hist, std::map<std::string,GamR::TK::FPeak*> Peaks, std::vector<std::string> FixPeaks={});
      void SetGuesses(TH1* hist, std::map<std::string,double> Peaks, std::vector<std::string> FixPeaks={});
      void SetIndices(std::map<std::string,GamR::TK::FPeak*> Peaks);
      void SetLimit(std::string peakKey, std::string parameterKey, double lowerLimit, double upperLimit);

      void SetLow(double Low) { fLow = Low; }
      void SetHigh(double High) { fHigh = High; }
      void SetChi2(double Chi2) { fChi2 = Chi2; }
      void SetUp(TH1 *hist, std::map<std::string,double> Peaks, Option_t *option, std::vector<std::string> FixPeaks={}) {
        SetOpts(option);
        SetBackground();
        SetPeaks(Peaks);
        SetIndices(fPeaks);
        SetGuesses(hist, Peaks, FixPeaks);
      }
      void Fit(TH1* hist, Option_t *foption);
      void SetResults(TH1 *hist);      
      void SetFunction();
      void PrintResults();
      
      double GetAmp(std::string peakKey);
      double GetAmpError(std::string peakKey);
      double GetCent(std::string peakKey);
      double GetCentError(std::string peakKey);
      double GetWidth(std::string peakKey);
      double GetWidthError(std::string peakKey);
      double GetArea(std::string peakKey) { return fPeaks[peakKey]->GetArea(); }
      double GetAreaError(std::string peakKey) { return fPeaks[peakKey]->GetAreaError(); }

      double GetAmp(int i) { return GetAmp(fPeakKeys[i]); }
      double GetAmpError(int i) { return GetAmpError(fPeakKeys[i]); }
      double GetCent(int i) { return GetCent(fPeakKeys[i]); }
      double GetCentError(int i) { return GetCentError(fPeakKeys[i]); }
      double GetWidth(int i) { return GetWidth(fPeakKeys[i]); }
      double GetWidthError(int i) { return GetWidthError(fPeakKeys[i]); }
      double GetArea(int i) { return GetArea(fPeakKeys[i]); }
      double GetAreaError(int i) { return GetAreaError(fPeakKeys[i]); }
      
      void SetAmp(std::string peakKey, double amp);
      void SetAmpError(std::string peakKey, double error);
      void SetCent(std::string peakKey, double centroid);
      void SetCentError(std::string peakKey, double error);
      void SetWidth(std::string peakKey, double width);
      void SetWidthError(std::string peakKey, double error);

      void SetAmp(int i, double amp) { SetAmp(fPeakKeys[i], amp); }
      void SetAmpError(int i, double error) { SetAmpError(fPeakKeys[i], error); }
      void SetCent(int i, double centroid) { SetCent(fPeakKeys[i], centroid); }
      void SetCentError(int i, double error) { SetCentError(fPeakKeys[i], error); }
      void SetWidth(int i, double width) { SetWidth(fPeakKeys[i], width); }
      void SetWidthError(int i, double error) { SetWidthError(fPeakKeys[i], error); }

      void FixPeakEnergy(std::string peakKey) { fPeakEnFix[peakKey] = 1; }
      
      void AddPeak(std::string peakKey, GamR::TK::FPeak* peak);
      void AddPeak(std::string peakKey, GamR::TK::PeakType peaktype);
      void AddPeak(std::string peakKey, GamR::TK::PeakType peaktype, double centroid);

      void ToText(std::string filename, std::string delimiter=" ", int nPoints=1000);

      TGraph *GetWidthGraph() { return gWidth; }
      TGraph *GetStepGraph() { return gStep; }
      TGraph *GetSkewAmpGraph() { return gSkewAmp; }
      TGraph *GetSkewGraph() { return gSkew; }
      TGraph *GetSkewAmp2Graph() { return gSkewAmp2; }
      TGraph *GetSkew2Graph() { return gSkew2; }
      
      GamR::TK::FPeak* Get(std::string peakKey) { return fPeaks[peakKey]; }
      GamR::TK::FPeak* Get(int i) { return fPeaks[fPeakKeys[i]]; }     
      std::map<std::string,GamR::TK::FPeak*> GetPeaks() { return fPeaks; }

      TF1 *GetPeakBG(std::string peakKey);      
      TF1 *GetPeakBG(int i) { return GetPeakBG(fPeakKeys[i]); }

      TF1 *GetPeakStepBG(std::string peakKey);
      TF1 *GetPeakStepBG(int i) { return GetPeakStepBG(fPeakKeys[i]); }

      TF1 *GetPeakGaussBG(std::string peakKey);
      TF1 *GetPeakGaussBG(int i) { return GetPeakGaussBG(fPeakKeys[i]); }
      
      TF1 *GetFunc(std::string peakKey) { return fPeaks[peakKey]->GetFunc(); }
    };
    
    PeakFit *FitPeaks(TH1 *hist, double Low, double High, std::map<std::string,double> Peaks, Option_t *foption = "",
                      Option_t *option = "", std::vector<std::string> FixEnergies = {});
    PeakFit *FitPeaks(TH1 *hist, double Low, double High, std::vector<double> Peaks, Option_t *foption = "",
                      Option_t *option = "", std::vector<std::string> FixEnergies = {});
    PeakFit *FitPeaks(TCanvas *canvas = gPad->GetCanvas(), Option_t *foption = "", Option_t *option = "");

    TF1 *FitGaussians(TH1 *hist, double Low, double High, std::map<std::string,double> Peaks, Option_t *foption = "",
                      Option_t *option = "");
    TF1 *FitGaussians(TH1 *hist, double Low, double High, std::vector<double> Peaks, Option_t *foption = "",
                      Option_t *option = "");
    TF1 *FitGaussians(TCanvas *canvas = gPad->GetCanvas(), Option_t *foption = "", Option_t *option = "");

    TSpectrum *FindPeaks(TCanvas *canvas = gPad->GetCanvas(), double sigma = 2, Option_t *option="", double threshold = 0.05);

  } /* namespace Spect */
} /* namespace GamR */

#endif // GAMR_SPECT_FIT_HH
