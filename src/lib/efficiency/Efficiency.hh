#ifndef EFFICIENCY_HH
#define EFFICIENCY_HH

#include <vector>
#include <map>
#include <string>

#include <TH1.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>

#include <nucleus/Transition.hh>

namespace GamR {
  /*!
  \addtogroup Efficiency
  @{
  */

  //! Library to calculate relative efficiencies for HPGe detectors
  namespace Efficiency {
    double EffCFunc(double *x, double *pars);
    
    class DataSet {
    private:
      std::vector<std::string> fKeys;
      std::vector<double> fEnergies;
      std::vector<double> fPeakAreas;
      std::vector<double> fPeakErrors;
      std::vector<double> fIntensities;
      double fNormalisation;
      std::vector<double> fEfficiencies;
      std::vector<double> fEfficiencyErrors;
      bool fAbsolute;
      double fAbsScale;
    public:
      DataSet() { fNormalisation = 1.0; fAbsolute = true; }
      DataSet(const char *effFile);
      DataSet(const char *histFile, const char *histName, const char *gateFile, const char *mapName, const char *intensityFile);
      DataSet(TH1D *fHist, GamR::Nucleus::TransitionMap* fTransitionMap, std::map<std::string, std::pair<double, double> > fIntensityMap);
      DataSet(std::string areaFile, const char *intensityFile);
      void SetData(const char *effFile);
      void SetData(TH1D *fHist, GamR::Nucleus::TransitionMap* fTransitionMap, std::map<std::string, std::pair<double, double> > fIntensityMap);
      void SetData(std::string areaFile, std::map<std::string, std::pair<double, double> > fIntensityMap);
      void SetNorm(double fNorm) { fNormalisation = fNorm; }
      void SetAbsolute(bool fAbs) { fAbsolute = fAbs; }
      void SetAbsScale(double fScale) { fAbsScale = fScale; }
      int GetIndex(std::string key);
      bool GetAbsolute() { return fAbsolute; }
      std::string GetKey(int i) { return fKeys[i]; }
      double GetEnergy(int i) { return fEnergies[i]; }
      double GetPeak(int i) { return fPeakAreas[i]; }
      double GetIntensity(int i) { return fIntensities[i]; }
      double GetNorm() { return fNormalisation; }
      double GetEfficiency(int i) { return fEfficiencies[i]; }
      double GetNData() { return fEnergies.size(); }
      void EraseData(std::string key);
      void Print(const char *fileName);
      void Clear();
      TGraphErrors *GetGraph();
      TGraphErrors *GetGraphErrors();
    };

    class FitParams {
    public:
      std::vector<TFormula> params;
      std::vector<TFormula> limlow;
      std::vector<TFormula> limhigh;
      std::vector<int> fixed;
    public:
      FitParams(int nParams) : params(nParams), fixed(nParams), limlow(nParams), limhigh(nParams) {}
      void SetParams(std::vector<std::string> sParams, std::vector<std::string> sFixed, std::vector<std::string> sLimLow, std::vector<std::string> sLimHigh);
    };
    
    class EffFit {
    private:
      class GlobalChiSquare;      
      
    public:
      std::vector<DataSet> fDataSets;
      double fAbsScale;
      bool EqualWeights = false;
      TF1 *EffFunc;      
      EffFit();
      void AddData(DataSet dataset) { fDataSets.push_back(dataset); }
      void EraseData(int iDataSet, std::string key) { fDataSets[iDataSet].EraseData(key); }
      void SetParams(FitParams params);
      void PrintParams(const char *fileName);
      void Fit(int quiet = 0);
      TMultiGraph* Draw(TCanvas *canvas, int detID=0, double xlow=-1, double xhigh=-1);
      void WriteGraph(std::string outDir);
      TMultiGraph* DrawRes(TCanvas *canvas, int detID=0, double xlow=-1, double xhigh=-1);
      void Draw(const char *outFile, double xlow=-1, double xhigh=-1);
    };

    class MultiDataSet {
    private:
      std::map<int, DataSet> fDataSets;
    public:
      MultiDataSet() {};
      MultiDataSet(const char *histFile, const char *histName, const char *gateFile, const char *mapName, const char *intensityFile);
      DataSet& operator[] (int key) { return fDataSets[key]; }
      std::map<int, DataSet> *GetDataSets() { return &fDataSets; }
      int GetNPoints(int i) { return fDataSets[i].GetNData(); }
    };

    class MultiEffFit {
    private:      
      std::map<int, EffFit> fEffFits;
      std::map<int, double> fDetNorm;
    public:
      MultiEffFit() {}
      void AddData(const char *histFile, const char *histName, const char *gateFile, const char *mapName, const char *intensityFile);
      void AddData(DataSet dataSet, int ID);
      void SetAbsScale(double absScale, int ID) { fEffFits[ID].fAbsScale = absScale; }
      void SetData(const char *effFile, int i, int ID);
      void SetDetNorms(int ID, int iDataSet, std::string key);
      void SetNorm(int iDataSet, double factor);
      void SetNorm(int ID, int iDataSet, double factor);
      void SetParams(FitParams params);
      void SetParams(int ID, FitParams params);
      void EraseData(int ID, int iDataSet, std::string key) { fEffFits[ID].EraseData(iDataSet, key); }
      void EraseData(int iDataSet, std::string key);
      void Fit();
      void Fit(int ID);
      void WriteGraphs(std::string outDir);
      void Draw(const char *outFile, double xlow=-1, double xhigh=-1);
      void PrintDataSet(int i, const char *fileNameBase);
      void PrintDataSet(int i, int ID, const char *fileNameBase);
      void PrintParams(const char *outFile);
    };   
  }
  /*! @} */
}

#endif
