/**
   @file
   @author Timothy Gray <timothy.gray@anu.edu.au>
   @section DESCRIPTION

   Library to fit a 7-parameter relative efficiency for HPGe detectors. The parameterisation is from RadWare: https://radware.phy.ornl.gov/gf3/#5.3.
*/

#include <sstream>
#include <map>
#include <string>
#include <fstream>
#include <vector>

#include <TH1.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TFile.h>
#include <TColor.h>

#include <Math/Functor.h>
#include <Math/Factory.h>
#include <Math/Minimizer.h>
#include <Math/MinimizerOptions.h>


#include "Efficiency.hh"

// ignoring npar, gin, iflag in GlobalChiSquare::doit
// TMinuit expects these extra variables that we don't use
#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace GamR {
  namespace Efficiency {
    /** \class MultiEffFit
        \ingroup Efficiency

        An example of how to use the Efficiency library through the MultiEffFit class to fit efficiencies for multiple detectors, using multiple data sets for each one.

        First we define the MultiEffFit object - this contains everything we'll need.
        ~~~ {.cpp}
        GamR::Efficiency::MultiEffFit efffit;
        ~~~
  
        Add data sets.  Each Xe138_*.root file contains a 2D histogram gClean that has detector ID on the y-axis 
        and energy on the x-axis. The *gates.root files contain a `GamR::Nucleus::TransitionMap`, named 
        "transitionMap", which have gates for peaks and backgrounds for each transition of interest.  
        The *_intensities.txt have keys for each `GamR::Nucleus::Transition`  in the previous map, 
        energies, and standard relative intensities (normalised to a total of 100).
        ~~~ {.cpp}
        efffit.AddData("Xe138_eu152.root", "gClean", "eu152gates.root", "transitionMap", "eu152_intensities.txt");
        efffit.AddData("Xe138_am243.root", "gClean", "am243gates.root", "transitionMap", "am243_intensities.txt");
        efffit.AddData("Xe138_ta182.root", "gClean", "ta182gates.root", "transitionMap", "ta182_intensities.txt");
        efffit.AddData("Xe138_co56.root", "gClean", "co56gates.root", "transitionMap", "co56_intensities.txt");
        ~~~

        An exerpt of a possible "eu152_intensities.txt", where the keys in transitionMap are the first column, the energies the second, and the normalised intensities the third
        ~~~ 
        t122      121.7817	    28.58
        t126      125.69        0.016
        t148      148.010	      0.037
        t213      212.568       0.0198
        t245      244.6975	    7.583
        ~~~

        We create FitParams objects which will contain starting guesses, limits, and information about whether
        we wish to fix the parameter or not.  Initially, we have a general one for all detectors, but we can
        make individuals for unusual detectors as well.

        ~~~ {.cpp}
        GamR::Efficiency::FitParams fpar(7);

        GamR::Efficiency::FitParams fpar_8(7);
        GamR::Efficiency::FitParams fpar_38(7);
        ~~~

        We set the 7 parameters: starting guesses, fixing (0 for free, 1 for fixed), lower limits, and upper limits
        ~~~ {.cpp}
        fpar.SetParams({"5.0", "10.0", "0", "6.0", "-0.6", "-0.05", "15"},
        {"0", "0", "1", "0", "0", "0", "1"},
        {"-1e4", "0", "-1e4", "-1e4", "-1e4", "-1e4", "1"},
        {"1e4", "1e4", "1e4", "1e4", "1e4", "1e4", "1e4"});

        fpar_8.SetParams({"5.0", "10.0", "0", "6.0", "-0.6", "-0.05", "15"},
        {"1", "1", "1", "0", "0", "0", "1"},
        {"-1e4", "0", "-1e4", "-1e4", "-1e4", "-1e4", "1"},
        {"1e4", "1e4", "1e4", "1e4", "1e4", "1e4", "1e4"});

        fpar_38.SetParams({"10.0", "10.0", "0", "6.0", "-0.6", "-0.05", "4"},
        {"0", "0", "1", "0", "0", "0", "1"},
        {"-1e4", "0", "-1e4", "-1e4", "-1e4", "-1e4", "1"},
        {"1e4", "1e4", "1e4", "1e4", "1e4", "1e4", "1e4"});
        ~~~

        We set all detectors to have the parameters in fpar
        ~~~ {.cpp}
        efffit.SetParams(fpar);
        ~~~

        Remove some anomalous data points in detector 8, data set 2
        ~~~ {.cpp}
        efffit.EraseData(8, 2, "t100");
        efffit.EraseData(8, 2, "t179");
        efffit.EraseData(8, 2, "t198");
        ~~~

        Remove some bad data points from data sets 1 and 2 in all detectors
        ~~~ {.cpp}
        efffit.EraseData(1, "t75");
        efffit.EraseData(2, "t68");
        efffit.EraseData(2, "t68");
        ~~~

        Set parameters for detectors 8 and 38 only
        ~~~ {.cpp}
        efffit.SetParams(8, fpar_8);
        efffit.SetParams(38, fpar_38);
        ~~~

        Change normalisations for first all detectors, and data set 3, then individual detectors
        ~~~ {.cpp}
        efffit.SetNorm(3, 2.0);

        efffit.SetNorm(8, 3, 0.6);
        efffit.SetNorm(20, 3, 1.5);
        efffit.SetNorm(38, 3, 1.5);
        efffit.SetNorm(104, 3, 1.5);

        efffit.SetNorm(8, 0, 2.0);
        efffit.SetNorm(8, 1, 2.0);
        efffit.SetNorm(8, 2, 2.0);
        efffit.SetNorm(8, 3, 2.0);
        ~~~

        Print the initial guesses to "InitialGuess.pdf", and carry out the fit.
        ~~~ {.cpp}
        efffit.Draw("InitialGuess.pdf", 0, 4096);
        efffit.Fit();
        ~~~

        Now we can refine the fit parameters.  "x" here stands for the previously fitted value.
        We free the final parameter which was fixed before, and continue.
        ~~~ {.cpp}
        fpar.SetParams({"x", "x", "0", "x", "x", "x", "x"},
        {"0", "0", "1", "0", "0", "0", "0"},
        {"-1e4", "0", "-1e4", "-1e4", "-1e4", "-1e4", "10"},
        {"1e4", "1e4", "1e4", "1e4", "1e4", "1e4", "50"});

        fpar_8.SetParams({"5.0", "10.0", "0", "x", "x", "x", "x"},
        {"1", "1", "1", "0", "0", "0", "1"},
        {"-1e4", "0", "-1e4", "-1e4", "-1e4", "-1e4", "1"},
        {"1e4", "1e4", "1e4", "1e4", "1e4", "1e4", "1e4"});  
        ~~~

        Once again, set every detector to the parameters found in fpar.  Note however that each 
        detector will retain its own previous values.  Detector 8 is set to its own starting values,
        and we fit once more.
        ~~~ {.cpp}
        efffit.SetParams(fpar);
  
        efffit.SetParams(8, fpar_8);

        efffit.Fit();
        ~~~

        We might also want to know about the relative efficiencies between detectors.  To do this 
        we select a single, strong transition as a reference energy ("t847"), and a reference detector
        ID = 7. Then the normalisation is calculated as
        
        \f[
        \frac{N_i("t847")}{N_7("t847")} = \frac{\epsilon_i(847)}{\epsilon_7(847)}
        \f]

	~~~ {.cpp}
	efffit.SetDetNorms(7, 3, "t847");
	~~~

        Draw the final results to "EffFits.pdf", and print the detector IDs, relative detector 
        normalisations, and 7 parameters with their errors to "EffParams.txt"
        ~~~ {.cpp}
        efffit.Draw("EffFits.pdf", 0, 4096);
        efffit.PrintParams("EffParams.txt");
        ~~~
    */
  }
}

namespace GamR {
  namespace Efficiency {

    /** 
        HPGe relative efficiency 7-parameter form. The same as is implemented in Radware: <https://radware.phy.ornl.gov/gf3/#5.3.>.

        Used to make a TF1 in the EffFit class.
    */
    double EffCFunc(double *x, double *pars) {
      //this is basically from radware
      double x1 = log(x[0]/100.0);
      double x2 = log(x[0]/1000.0);
 
      double g = pars[6];
      double f1 = pars[0] + pars[1]*x1 + pars[2]*x1*x1;
      double f2 = pars[3] + pars[4]*x2 + pars[5]*x2*x2;
      
      double abs_scale = pars[7];
      double f = 0;
      double nf = 0;
      double r = 0;

      //if both are negative we have a problem, f1^(-g) + f2^(-g) is potentially undefined
      //--> return zero
      if (f1 < 0 && f2 < 0) {
        if (x[0] > 50 && x[0] < 8192) {
          std::cerr << "Warning! Both parabolic components of efficiency are < 0 for E_gamma = " << x[0] << " keV, consider decreasing normalization for data sets" << std::endl; 
        }
        return 0;
      }

      if (f1 <= f2 ) {
        r = f1/f2;
        f = f1;
        nf = f2;        
      }
      else {
        r = f2/f1;
        f = f2;
        nf = f1;
      }

      //if one is negative, and the other positive, or both positive but one is much smaller than the other
      //approximation where only large component matters
      if (r <= 1e-6) {
        double retval = exp(f)*abs_scale;
        /*
        if (retval > 0.05) {
          std::cout << "x = " << x[0] << ", f1, f2 = " << f1 << "  " << f2 << std::endl;
          std::cout << "exp(f) = " << exp(f) << ", abs_scale = " << abs_scale << std::endl;
          std::cout << "eff = " << retval << std::endl;
        }
        */
        return retval;
      }
      //both are positive and approximately the same size
      //full evaluation
      else {
        double y = pow(pow(r, g) + 1.0, -1.0/g);
        double retval = exp(y*f)*abs_scale;
        /*
        if (retval > 0.05) {
          std::cout << "x = " << x[0] << ", f1, f2 = " << f1 << "  " << f2 << std::endl;
          std::cout << "exp(y*f) = " << exp(y*f) << ", abs_scale = " << abs_scale << std::endl;
          std::cout << "eff = " << retval << std::endl;
          }
        */
        return retval;
      }
    }      

    void DataSet::Clear()
    {
      fKeys.clear();
      fEnergies.clear();
      fPeakAreas.clear();
      fPeakErrors.clear();
      fIntensities.clear();
      fEfficiencies.clear();
      fEfficiencyErrors.clear();
      fNormalisation = 1.0;
      fAbsScale = 1.0;
    }
    
    DataSet::DataSet(TH1D *fHist, GamR::Nucleus::TransitionMap* fTransitionMap, std::map<std::string, std::pair<double, double> > fIntensityMap)
    {
      SetData(fHist, fTransitionMap, fIntensityMap);
    }
    
    void DataSet::SetData(TH1D *fHist, GamR::Nucleus::TransitionMap* fTransitionMap, std::map<std::string, std::pair<double, double> > fIntensityMap)
    {
      Clear();
      std::map<std::string, GamR::Nucleus::Transition > *fTransMap = fTransitionMap->GetMap();
      fNormalisation = 0.0;
      double max = 0.0;
      for (auto &intensity : fIntensityMap) {
        //check if there's a corresponding transition in transitionmap
        if (fTransMap->find(intensity.first) != fTransMap->end()) {
          double area = (*fTransMap)[intensity.first].Apply(fHist);
          double areaerror = (*fTransMap)[intensity.first].ApplyError(fHist);
          double energy = intensity.second.first;
          double intens = intensity.second.second;
          double eff = area/intens;
          double efferr = areaerror/intens;
          if (area<=0) {
            continue;
          }
          fKeys.push_back(intensity.first);
          fPeakAreas.push_back(area);
          fPeakErrors.push_back(areaerror);
          fEnergies.push_back(energy);
          fIntensities.push_back(intens);
          fEfficiencies.push_back(eff);
          fEfficiencyErrors.push_back(efferr);
        
          if (eff > max) {
            max = eff;
          }
        }
      }

      fNormalisation = max/1000.0;
      
    }

    void DataSet::SetData(std::string areaFile, std::map<std::string, std::pair<double, double> > fIntensityMap)
    {
      Clear();
      std::map<std::string, std::pair<double, double> > areaMap;
      std::ifstream area_file(areaFile);
      std::string key;
      double area,area_error;
      while (area_file >> key >> area >> area_error) {
        areaMap[key] = {area, area_error};
      }      
      
      fNormalisation = 0.0;
      double max = 0.0;
      for (auto &intensity : fIntensityMap) {
        //check if there's a corresponding transition in transitionmap
        if (areaMap.find(intensity.first) != areaMap.end()) {
          double area = areaMap[intensity.first].first;
          double areaerror = areaMap[intensity.first].second;
          double energy = intensity.second.first;
          double intens = intensity.second.second;
          double eff = area/intens;
          double efferr = areaerror/intens;
          if (area<=0) {
            continue;
          }
          fKeys.push_back(intensity.first);
          fPeakAreas.push_back(area);
          fPeakErrors.push_back(areaerror);
          fEnergies.push_back(energy);
          fIntensities.push_back(intens);
          fEfficiencies.push_back(eff);
          fEfficiencyErrors.push_back(efferr);
        
          if (eff > max) {
            max = eff;
          }
        }
      }

      fNormalisation = max/1000.0;
      
    }
    void DataSet::SetData(const char *effFile)
    {
      Clear();
      double area;
      double areaerror;
      double intens;
      double energy;
      double max;
      std::string key;
      std::string line;
      std::ifstream eff_file(effFile);      
      if (!eff_file.is_open()) {
        std::cerr << "Error opening " << effFile << std::endl;
      }
      getline(eff_file, line);
      while (eff_file >> key >> energy >> intens >> area >> areaerror) {
        double eff = area/intens;
        double efferr = areaerror/intens;
        if (area <=0 ) {
          continue;
        }
        fKeys.push_back(key);
        fPeakAreas.push_back(area);
        fPeakErrors.push_back(areaerror);
        fEnergies.push_back(energy);
        fIntensities.push_back(intens);
        fEfficiencies.push_back(eff);
        fEfficiencyErrors.push_back(efferr);
        
        if (eff > max) {
          max = eff;
        }
      }

      fNormalisation = max/1000.0;      
    }

    DataSet::DataSet(const char *effFile)
    {
      SetData(effFile);
    }
    
    DataSet::DataSet(const char *histFile, const char *histName, const char *gateFile, const char *mapName, const char *intensityFile)
    {
      TFile *hisFile = new TFile(histFile);      
      TH1D *fHist = (TH1D*)hisFile->Get(histName);
      
      TFile *gatFile = new TFile(gateFile);
      GamR::Nucleus::TransitionMap *fTransitionMap = (GamR::Nucleus::TransitionMap*)gatFile->Get(mapName);


      std::ifstream intFile(intensityFile);

      std::string key;
      double energy;
      double intensity;
      std::map<std::string, std::pair<double, double> > fIntensityMap;
      while(intFile >> key >> energy >> intensity) {
        fIntensityMap[key] = std::pair<double, double>(energy, intensity);
      }
      
      SetData(fHist, fTransitionMap, fIntensityMap);

      hisFile->Close();
      gatFile->Close();
    }

    DataSet::DataSet(std::string areaFile, const char *intensityFile) {
      std::ifstream intFile(intensityFile);

      std::string key;
      double energy;
      double intensity;
      std::map<std::string, std::pair<double, double> > fIntensityMap;
      while(intFile >> key >> energy >> intensity) {
        fIntensityMap[key] = std::pair<double, double>(energy, intensity);
      }

      SetData(areaFile, fIntensityMap);
    }

    int DataSet::GetIndex(std::string key)
    {
      int index = -1;
      for (int i=0; i<GetNData(); ++i) {
        if (fKeys[i].compare(key) == 0) {
          index = i;
          break;
        }
      }
      if (index == -1) {
        std::cout << "Key " << key << " not found!" << std::endl;
        return -1;
      }
      return index;
    }
    
    void DataSet::EraseData(std::string key)
    {
      int index = GetIndex(key);

      if (index >= 0) {
        fKeys.erase(fKeys.begin()+index);
        fEnergies.erase(fEnergies.begin()+index);
        fPeakAreas.erase(fPeakAreas.begin()+index);
        fPeakErrors.erase(fPeakErrors.begin()+index);
        fIntensities.erase(fIntensities.begin()+index);
        fEfficiencies.erase(fEfficiencies.begin()+index);
        fEfficiencyErrors.erase(fEfficiencyErrors.begin()+index);
      }
    }      

    void DataSet::Print(const char *fileName)
    {
      FILE* file;
      file = fopen(fileName, "wa");

      fprintf(file, "Key        Energy     Intensity     PeakArea     Error \n");
      for (int i=0; i<GetNData(); ++i) {
        fprintf(file, "%8s  %11.2f %13.4f %12.2f %10.4f\n", fKeys[i].c_str(), fEnergies[i], fIntensities[i], fPeakAreas[i], fPeakErrors[i]);
      }

      fclose(file);
    }
    
    TGraphErrors *DataSet::GetGraph()
    {
      int nPoints = fEnergies.size();
      TGraphErrors *graph = new TGraphErrors(nPoints);

      for (int i=0; i<nPoints; ++i)
        {
          double y = fEfficiencies[i]/fNormalisation;
          double y_err = fEfficiencyErrors[i]/fNormalisation;
          if (!fAbsolute) {
            y = y * fAbsScale;
            y_err = y_err * fAbsScale;
          }
          graph->SetPoint(i, fEnergies[i], y);
          graph->SetPointError(i, 0, 0.01*fAbsScale);
        }
      return graph;
    }

    TGraphErrors *DataSet::GetGraphErrors()
    {
      int nPoints = fEnergies.size();
      TGraphErrors *graph = new TGraphErrors(nPoints);

      for (int i=0; i<nPoints; ++i)
        {
          double y = fEfficiencies[i]/fNormalisation;
          double y_err = fEfficiencyErrors[i]/fNormalisation;
          if (!fAbsolute) {
            y = y * fAbsScale;
            y_err = y_err * fAbsScale;
          }
          std::cout << fEnergies[i] << "   " << fEfficiencies[i] << "   " << fNormalisation << "   " << y << std::endl;
          graph->SetPoint(i, fEnergies[i], y);
          graph->SetPointError(i, 0, y_err);
        }
      return graph;
    }
    
    EffFit::EffFit()
    {
      EffFunc = new TF1("EffFunc", EffCFunc, 1, 4096, 8);
      EffFunc->SetNpx(1000);
      
      //sane initial values
      EffFunc->SetParameter(0, 1.);      
      EffFunc->SetParameter(1, 1.);
      EffFunc->SetParameter(2, 0.);
      EffFunc->SetParameter(3, 1.);
      EffFunc->SetParameter(4, 1.);
      EffFunc->SetParameter(5, 1.);
      EffFunc->SetParameter(6, 20.);
      EffFunc->SetParameter(7, 1.0);

      for (int i=0; i<7; ++i)
        {          
          double parmin, parmax;
          EffFunc->GetParLimits(i, parmin, parmax);
          EffFunc->SetParLimits(i, -1e4, 1e4);
          EffFunc->SetParError(i, 0.1);
        }
      EffFunc->SetParLimits(6, 1.0, 1e4);

      EffFunc->SetParLimits(7, 0, 1.0);
      EffFunc->SetParError(7, 0.01);
      
      EffFunc->FixParameter(2, 0.);
      EffFunc->FixParameter(6, 20.);

      fAbsScale = 1.0;
    }
    
    
    class EffFit::GlobalChiSquare {
    private:
      static EffFit *p;

    public:
      GlobalChiSquare(EffFit *parent) { p = parent; }

      double operator()(const double *par) {
        double chisq = 0;

        p->EffFunc->SetParameter(0, par[0]);
        p->EffFunc->SetParameter(1, par[1]);
        p->EffFunc->SetParameter(2, par[2]);
        p->EffFunc->SetParameter(3, par[3]);
        p->EffFunc->SetParameter(4, par[4]);
        p->EffFunc->SetParameter(5, par[5]);
        p->EffFunc->SetParameter(6, par[6]);
        p->EffFunc->SetParameter(7, par[7]);

        int nDataSets = p->fDataSets.size();
        for (int i=0; i<8+nDataSets; ++i) {
          std::cout << Form("%6.3f   ", par[i]);
        }

        for (int i=0; i<nDataSets; ++i) {
          p->fDataSets[i].SetAbsScale(par[7]);
          p->fDataSets[i].SetNorm(par[8+i]);
          if (p->fDataSets[i].GetNData() > 0) {
            TGraphErrors *graph;
            if (p->EqualWeights) {
              graph = p->fDataSets[i].GetGraph();
            }
            else {
              graph = p->fDataSets[i].GetGraphErrors();
            }
            if (p->fDataSets[i].GetAbsolute()) { //a bit of extra encouragement here, as for absolute normalizations we typically have a few data points with which we should achieve almost perfect agreement
              chisq += 100.0*graph->Chisquare(p->EffFunc);
            }
            else {
              chisq += graph->Chisquare(p->EffFunc);
            }

            delete graph;
          }
        }
        std::cout << Form("chisq=%5.1f",chisq);
        std::cout << std::endl;
        return chisq;
      }
      

      /*
      static void minuit(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
      {
        f = 0;
        
        p->EffFunc->SetParameter(0, par[0]);
        p->EffFunc->SetParameter(1, par[1]);
        p->EffFunc->SetParameter(2, par[2]);
        p->EffFunc->SetParameter(3, par[3]);
        p->EffFunc->SetParameter(4, par[4]);
        p->EffFunc->SetParameter(5, par[5]);
        p->EffFunc->SetParameter(6, par[6]);
        p->EffFunc->SetParameter(7, par[7]);

        int nDataSets = p->fDataSets.size();
        for (int i=0; i<nDataSets; ++i) {
          p->fDataSets[i].SetAbsScale(par[7]);
          p->fDataSets[i].SetNorm(par[8+i]);
          if (p->fDataSets[i].GetNData() > 0) {
            TGraphErrors *graph;
            if (p->EqualWeights) {
              graph = p->fDataSets[i].GetGraph();
            }
            else {
              graph = p->fDataSets[i].GetGraphErrors();
            }
            f += graph->Chisquare(p->EffFunc);

            delete graph;
          }
        }
      }
    */
    };


    EffFit *EffFit::GlobalChiSquare::p = nullptr;

    void EffFit::Fit(int quiet)
    {
      int nDataSets = fDataSets.size();
      if (nDataSets == 0) { return; }
      Int_t npars = 8 + nDataSets;

      ROOT::Math::Minimizer *min = NULL;
      min=ROOT::Math::Factory::CreateMinimizer("Minuit2", "Minimize");
  
      if (min==NULL) { std::cerr << "Minimizer failed to create!" << std::endl; exit(1); }

      GlobalChiSquare func(this);
      ROOT::Math::Functor f_init(func,npars);

      min->SetErrorDef(1.);
      min->SetMaxFunctionCalls(100000);
      min->SetMaxIterations(100000);
      min->SetTolerance(1e-6);
      min->SetPrecision(1e-8);
      min->SetFunction(f_init);

      Int_t parnum = 0;

      std::cout << "Starting fit with guesses: " << std::endl;
      std::vector< std::string > parnames = {"A", "B", "C", "D", "E", "F", "G", "AbsScale"};
      for ( int i=0; i<8; ++i ) {
        double parmin, parmax;
        EffFunc->GetParLimits(i, parmin, parmax);
        if (parmin==parmax) {
          parmin = EffFunc->GetParameter(i) - 1;  //because Minuit doesn't allow equal upper and lower bounds
          parmax = EffFunc->GetParameter(i) + 1;
        }
        std::cout << "   " << parnames[i] << "  " << EffFunc->GetParameter(i) << "  (" << parmin << "," << parmax << ")" << std::endl;
        min->SetLimitedVariable(parnum, parnames[i].c_str(), EffFunc->GetParameter(i), EffFunc->GetParError(i), parmin, parmax);
        min->SetVariableStepSize(parnum, 0.1);
        ++parnum;
      }

      for (int i=0; i<8; ++i) {
        double parmin, parmax;
        EffFunc->GetParLimits(i, parmin, parmax);
        if (parmin*parmax != 0 && parmin >= parmax) {
          min->FixVariable(i);
        }
      }
          
      for (int i=0; i<nDataSets; ++i) {
        std::cout << "Initial fNorm " << i << " = " << fDataSets[i].GetNorm() << std::endl;
        min->SetLimitedVariable(parnum, ("N"+std::to_string(i)).c_str(), fDataSets[i].GetNorm(), 0.02*fDataSets[i].GetNorm(), 0.8*fDataSets[i].GetNorm(), 1.2*fDataSets[i].GetNorm());
        if (fDataSets[i].GetNData() == 0 || fDataSets[i].GetAbsolute()) {
          min->FixVariable(parnum);
        }
        ++parnum;
      }
        
      min->FixVariable(7); //absolute scale
      min->FixVariable(8); //first data set
      
      // MINIMIZE 
      min->Minimize();
      min->PrintResults();
      
      //get parameters + errors and put into EffFunc
      for (int i=0; i<8; ++i) {
        double parVal, parErr;
        parVal = min->X()[i];
        parErr = min->Errors()[i];
        EffFunc->SetParameter(i, parVal);
        EffFunc->SetParError(i, parErr);
        if (i==7) {
          fAbsScale = parVal;
        }
      }
      //set final normalizations
      std::cout << "Setting final normalizations" << std::endl;
      for (int i=0; i<nDataSets; ++i) {
        double parVal, parErr;
        parVal = min->X()[8+i];
        fDataSets[i].SetNorm(parVal);
        std::cout << "Dataset " << i << ": " << parVal << std::endl;
      }

      delete min;

      if (quiet==0) {
        TCanvas *c1 = new TCanvas("cEff", "Efficiency Curve", 1280, 720);
        this->Draw(c1);
      }
      
    }
    
    /*
    void EffFit::Fit(int quiet)
    {
      int nDataSets = fDataSets.size();
      if (nDataSets == 0) { return; }
      Int_t npars = 8 + nDataSets;
      auto gMinuit = new TMinuit(npars);
      //gMinuit->Command("SET PRINT -1");

      GlobalChiSquare func(this);
      gMinuit->SetFCN(func.minuit);

      Double_t arglist[10];
      arglist[0] = 1;

      Int_t ierflg = 0; // some error flag ???

      gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
      arglist[0] = 2;
      gMinuit->mnexcm("SET STR", arglist, 1, ierflg);

      Int_t parnum = 0;

      std::vector< std::string > parnames = {"A", "B", "C", "D", "E", "F", "G", "AbsScale"};
      for ( int i=0; i<8; ++i ) {
        double parmin, parmax;
        EffFunc->GetParLimits(i, parmin, parmax);
        //std::cout << "Setting parameter " << parnum << " : " << parnames[i].c_str() << "   " << EffFunc->GetParameter(i) << "  " <<  EffFunc->GetParError(i) << "  " <<  parmin << "  " <<  parmax;
        if (parmin==parmax) {
          parmin = EffFunc->GetParameter(i) - 1;  //because Minuit doesn't allow equal upper and lower bounds
          parmax = EffFunc->GetParameter(i) + 1;
        }
        gMinuit->mnparm(parnum, parnames[i].c_str(), EffFunc->GetParameter(i), EffFunc->GetParError(i), parmin, parmax, ierflg);
        ++parnum;
      }

      for (int i=0; i<8; ++i) {
        double parmin, parmax;
        EffFunc->GetParLimits(i, parmin, parmax);
        if (parmin*parmax != 0 && parmin >= parmax) {
          gMinuit->FixParameter(i);
        }
      }
          
      for (int i=0; i<nDataSets; ++i) {
        std::cout << "Initial fNorm " << i << " = " << fDataSets[i].GetNorm() << std::endl;
        gMinuit->mnparm(parnum, ("N"+std::to_string(i)).c_str(), fDataSets[i].GetNorm(), 0.02*fDataSets[i].GetNorm(), 0.8*fDataSets[i].GetNorm(), 1.2*fDataSets[i].GetNorm(), ierflg);
        if (fDataSets[i].GetNData() == 0 || fDataSets[i].GetAbsolute()) {
          gMinuit->FixParameter(parnum);
        }
        ++parnum;
      }
        
      gMinuit->FixParameter(7); //absolute scale
      
      // MINIMIZE 
      arglist[0] = 100000; // Max Iterations
      arglist[1] = 1;      // Number of sigma max step
      gMinuit->mnexcm("MINIGRAD", arglist, 2, ierflg);
      gMinuit->mnimpr(); // Improve fit by searching for other minima
      gMinuit->mnexcm("HESSE", arglist, 2, ierflg);
      gMinuit->mnexcm("MINOS", arglist, 2, ierflg);

      //get parameters + errors and put into EffFunc
      for (int i=0; i<8; ++i) {
        double parVal, parErr;
        gMinuit->GetParameter(i, parVal, parErr);
        EffFunc->SetParameter(i, parVal);
        EffFunc->SetParError(i, parErr);
        if (i==7) {
          fAbsScale = parVal;
        }
      }
      //set final normalizations
      for (int i=0; i<nDataSets; ++i) {
        double parVal, parErr;
        gMinuit->GetParameter(8+i, parVal, parErr);
        fDataSets[i].SetNorm(parVal);
      }

      delete gMinuit;

      if (quiet==0) {
        TCanvas *c1 = new TCanvas("cEff", "Efficiency Curve", 1280, 720);
        this->Draw(c1);
      }
      
    }
    */

    void EffFit::SetParams(FitParams params) {
      for (int i=0; i<fDataSets.size(); ++i) {
        if (fDataSets[i].GetAbsolute()) {
          fDataSets[i].SetAbsScale(1.0);
        }
        else {
          fDataSets[i].SetAbsScale(fAbsScale);
        }
      }
      for (int i=0; i<params.params.size(); ++i) {
        double plow, phigh;
        EffFunc->GetParLimits(i, plow, phigh);
        double parmin = params.limlow[i].Eval(plow);
        double parmax = params.limhigh[i].Eval(phigh);
        //EffFunc->GetParLimits(i, parmin, parmax);

        if (params.fixed[i]==1) {
          EffFunc->SetParameter(i, params.params[i].Eval(EffFunc->GetParameter(i)));                   
          EffFunc->SetParLimits(i, parmin, parmax);
          EffFunc->FixParameter(i, params.params[i].Eval(EffFunc->GetParameter(i)));
        }
        else {          
          EffFunc->ReleaseParameter(i);
          EffFunc->SetParameter(i, params.params[i].Eval(EffFunc->GetParameter(i)));          
          EffFunc->SetParLimits(i, parmin, parmax);
          if (EffFunc->GetParError(i) == 0) {
            EffFunc->SetParError(i, 0.1);
          }
        }
      }
      EffFunc->SetParLimits(7, 0.1*fAbsScale, 10.0*fAbsScale);
      EffFunc->SetParameter(7, fAbsScale);
    }
    
    TMultiGraph* EffFit::Draw(TCanvas *canvas, int detID/*=0*/, double xlow/*=-1*/, double xhigh/*=-1*/, bool log/*=false*/)
    {
      std::cout << "Drawing Detector " << detID << std::endl;
      canvas->Clear();
      canvas->cd();
      int nDataSets = fDataSets.size();
      TMultiGraph *graph = new TMultiGraph();
      graph->SetTitle(("Efficiency "+std::to_string(detID)).c_str());
      std::vector<Color_t> colors = {kRed, kBlue, kGreen, kMagenta, kCyan, kBlack, kYellow};
      for (int i=0; i<nDataSets; ++i)
        {
          fDataSets[i].SetAbsScale(fAbsScale);
          TGraphErrors *dsetgraph = fDataSets[i].GetGraphErrors();
          std::cout << "    Data Set " << i << ", nPoints " << dsetgraph->GetN() << std::endl;
          dsetgraph->SetLineColor(colors[i]);
          dsetgraph->SetMarkerColor(colors[i]);
          graph->Add(dsetgraph);          
        }
      if (log) {
        graph->GetHistogram()->SetMinimum(0.001);
      }
      else {
        graph->GetHistogram()->SetMinimum(0.0);
      }
      graph->Draw("A*");
      if (xlow!=xhigh) {
        graph->GetXaxis()->SetLimits(xlow, xhigh);
      }
      graph->Draw("A*");
      EffFunc->SetParameter(7, fAbsScale);
      EffFunc->Draw("same");
      /*
      std::cout << "EXPLICIT PRINT OUT" << std::endl;
      for (int i=1; i<4096; ++i) {
        std::cout << i << "  " << EffFunc->Eval(i) << std::endl;
      }
      */
      if (log) {
        canvas->SetLogy();
        canvas->SetLogx();
      }
      return graph;
    }

    void EffFit::WriteGraph(std::string outDir)
    {      
      int nDataSets = fDataSets.size();
      
      for (int i=0; i<nDataSets; ++i)
        {
          std::string fname = outDir+"/dset_"+std::to_string(i)+".dat";
          std::ofstream dset_file(fname);            
          TGraphErrors *dsetgraph = fDataSets[i].GetGraphErrors();
          std::cout << "    Data Set " << i << ", nPoints " << dsetgraph->GetN() << std::endl;
          std::cout << fname << std::endl;
          for (int j=0; j<dsetgraph->GetN(); ++j) {
            double x, y, yerr;
            dsetgraph->GetPoint(j, x, y);
            yerr = dsetgraph->GetErrorY(j);
            dset_file << x << "    " << y << "    " << yerr << std::endl;            
          }
          dset_file.close();
        }

      std::string fname = outDir+"/efficiency.dat";
      std::ofstream eff_file(fname);            
      for (int i=1; i<=4096; ++i) {
        eff_file << i << "   " << EffFunc->Eval((double)i) << std::endl;
      }
      eff_file.close();
    }

    TMultiGraph* EffFit::DrawRes(TCanvas *canvas, int detID/*=0*/, double xlow/*=-1*/, double xhigh/*=-1*/)
    {
      std::cout << "Drawing Detector " << detID << std::endl;
      canvas->Clear();
      canvas->cd();
      int nDataSets = fDataSets.size();
      TMultiGraph *graph = new TMultiGraph();
      graph->SetTitle(("Efficiency "+std::to_string(detID)).c_str());
      std::vector<Color_t> colors = {kRed, kBlue, kGreen, kMagenta, kCyan, kBlack, kYellow};
      double std_dev = 0;
      int nPoints = 0;
      for (int i=0; i<nDataSets; ++i)
        {
          TGraphErrors *dsetgraph = fDataSets[i].GetGraphErrors();
          std::cout << "    Data Set " << i << ", nPoints " << dsetgraph->GetN() << std::endl;
          TGraphErrors *residuals = new TGraphErrors();
          for (int j=0; j<dsetgraph->GetN(); ++j) {
            ++nPoints;
            double x,y;
            dsetgraph->GetPoint(j, x, y);
            y = (y - EffFunc->Eval(x))/EffFunc->Eval(x)*100.0;
            std_dev += y*y;
            residuals->SetPoint(j, x, y);
            residuals->SetPointError(j, 0, dsetgraph->GetErrorY(j)/EffFunc->Eval(x)*100.0);
          }
          
          residuals->SetLineColor(colors[i]);
          residuals->SetMarkerColor(colors[i]);
          graph->Add(residuals);          
        }
      std_dev = std::sqrt(std_dev/(double)nPoints);
      std::cout << "Spread = " << std_dev << std::endl;
      canvas->SetLogy(0);
      graph->Draw("A*");
      if (xlow!=xhigh) {
        graph->GetXaxis()->SetLimits(xlow, xhigh);
      }
      graph->Draw("A*");
      TF1 *con = new TF1("con", "0", xlow, xhigh);
      con->Draw("same");
      return graph;
    }

    void EffFit::Draw(const char* outFile, double xlow, double xhigh, bool log) {
      TCanvas *c1 = new TCanvas();
      c1->Print(((std::string)outFile+"[").c_str());
      TMultiGraph *graph = Draw(c1, 0, xlow, xhigh, log);
      c1->Update();
      c1->Print(outFile);
      TMultiGraph *res = DrawRes(c1, 0, xlow, xhigh);
      c1->Update();
      c1->Print(outFile);
      c1->Print(((std::string)outFile+"]").c_str());
      delete graph;
      delete res;
    }

    MultiDataSet::MultiDataSet(const char *histFile, const char *histName, const char *gateFile, const char *mapName, const char *intensityFile)
    {
      TFile *hisFile = new TFile(histFile);      
      TH2D *fHist = (TH2D*)hisFile->Get(histName);
      
      TFile *gatFile = new TFile(gateFile);
      GamR::Nucleus::TransitionMap *fTransitionMap = (GamR::Nucleus::TransitionMap*)gatFile->Get(mapName);

      std::ifstream intFile(intensityFile);

      std::string key;
      double energy;
      double intensity;
      std::map<std::string, std::pair<double, double> > fIntensityMap;
      while(intFile >> key >> energy >> intensity) {
        fIntensityMap[key] = std::pair<double, double>(energy, intensity);
      }

      for (int i=1; i<fHist->GetYaxis()->GetNbins()+1; ++i) {
        TH1D *proj = (TH1D*)fHist->ProjectionX("proj", i, i);        
        std::cout << "ADDING DETECTOR " << i << ", " << proj->GetEntries() << std::endl;
        if (proj->GetEntries()>0) {
          fDataSets[i] = DataSet(proj, fTransitionMap, fIntensityMap);
        }
        delete proj;

      }

      hisFile->Close();
      gatFile->Close();

    }

    void FitParams::SetParams(std::vector<std::string> sParams, std::vector<std::string> sFixed, std::vector<std::string> sLimLow, std::vector<std::string> sLimHigh)
    {
      for (int i=0; i<sParams.size(); ++i) {
        TFormula fval("fval", sParams[i].c_str());
        TFormula flow("flow", sLimLow[i].c_str());
        TFormula fhigh("fhigh", sLimHigh[i].c_str());
        double parlow, parhigh;
        //func->GetParLimits(i, parlow, parhigh);
        params[i] = fval;//.Eval(func->GetParameter(i));
        limlow[i] = flow;//.Eval(parlow);
        limhigh[i] = fhigh;//.Eval(parhigh);
        if (atoi(sFixed[i].c_str())==1) {
          fixed[i] = 1;          
        }
        else {
          fixed[i] = 0;
        }
      }
    }  

    void MultiEffFit::AddData(const char *histFile, const char *histName, const char *gateFile, const char *mapName, const char *intensityFile)
    {
      MultiDataSet mdataset(histFile, histName, gateFile, mapName, intensityFile);
      for (auto &dset : *(mdataset.GetDataSets())) {
        int i = dset.first;
        AddData(dset.second, dset.first);   
      }      
    }

    void MultiEffFit::AddData(DataSet dataSet, int ID) {
      if (fEffFits.find(ID) == fEffFits.end()) {
        fEffFits[ID] = EffFit();
        fDetNorm[ID] = 1.0;
      }
      fEffFits[ID].AddData(dataSet);
      std::cout << "Added Det " << ID << " with " << dataSet.GetNData() << " efficiency calibration points" << std::endl;
      for (int j=0; j<dataSet.GetNData(); ++j) {
        std::cout << dataSet.GetEnergy(j) << "  " << dataSet.GetEfficiency(j) << std::endl;
      }    
    }

    void MultiEffFit::SetData(const char *effFile, int i, int ID)
    {
      fEffFits[ID].fDataSets[i].SetData(effFile);
    }
    
    void MultiEffFit::SetParams(FitParams params)
    {
      for (auto &efffit : fEffFits) {
        efffit.second.SetParams(params);
      }
    }

    void MultiEffFit::SetParams(int ID, FitParams params)
    {
      if (fEffFits.find(ID) == fEffFits.end()) { return; }
      fEffFits[ID].SetParams(params);
    }

    void MultiEffFit::SetDetNorms(int ID, int iDataSet, std::string key)
    {
      int index = fEffFits[ID].fDataSets[iDataSet].GetIndex(key);
      double normArea = fEffFits[ID].fDataSets[iDataSet].GetPeak(index);

      for (auto &efffit : fEffFits) {
        if (efffit.first != ID) {
          index = efffit.second.fDataSets[iDataSet].GetIndex(key);
          fDetNorm[efffit.first] = efffit.second.fDataSets[iDataSet].GetPeak(index)/normArea;
        }
      }      
    }
    
    void MultiEffFit::SetNorm(int iDataSet, double factor) {
      for (auto &efffit : fEffFits) {
        double curNorm = efffit.second.fDataSets[iDataSet].GetNorm();
        efffit.second.fDataSets[iDataSet].SetNorm(curNorm*factor);
      }
    }

    void MultiEffFit::SetNorm(int ID, int iDataSet, double factor) {
      double curNorm = fEffFits[ID].fDataSets[iDataSet].GetNorm();
      fEffFits[ID].fDataSets[iDataSet].SetNorm(curNorm*factor);
    }

    void MultiEffFit::EraseData(int iDataSet, std::string key) {
      for (auto &efffit : fEffFits) {
        efffit.second.fDataSets[iDataSet].EraseData(key);
      }
    }

    void MultiEffFit::SetEqualWeights(bool eq) {
      for (auto &efffit : fEffFits) {
        efffit.second.EqualWeights = true;
      }
    }
    
    void MultiEffFit::Fit()
    {
      for (auto &efffit : fEffFits) {
        std::cout << "=====================================================" << std::endl;
        std::cout << "FITTING DETECTOR " << efffit.first << std::endl;
        std::cout << "=====================================================" << std::endl;
        efffit.second.Fit(1);
      }
    }

    void MultiEffFit::Fit(int ID)
    {
      if (fEffFits.find(ID) == fEffFits.end()) { return; }
      fEffFits[ID].Fit(1);
    }
    
    void MultiEffFit::Draw(const char *outFile, double xlow/*=-1*/, double xhigh/*=-1*/, bool log/*=false*/)
    {
      std::vector<int> presentIDs;
      TCanvas *c1 = new TCanvas("c1", "c1", 1280, 720);
      c1->Print((outFile+std::string("[")).c_str());
      for (auto &efffit : fEffFits) {
        int detID = efffit.first;
        std::cout << "Drawing Det " << detID << std::endl;
        c1->Clear();
        TMultiGraph *graph = efffit.second.Draw(c1, detID, xlow, xhigh, log);
        c1->Update();
        c1->Print(outFile);
        presentIDs.push_back(detID);
        delete graph;
      }
      c1->Clear();
      c1->Print((outFile+std::string("]")).c_str());
    }

    void MultiEffFit::PrintDataSet(int i, int ID, const char *fileName)
    {
      fEffFits[ID].fDataSets[i].Print(fileName);
    }

    void MultiEffFit::PrintDataSet(int i, const char *fileNameBase)
    {           
      for (auto &efffit : fEffFits) {
        std::string fileName((std::string(fileNameBase)+"."+std::to_string(efffit.first)).c_str());
        efffit.second.fDataSets[i].Print(fileName.c_str());
      }
    }
    
    void MultiEffFit::PrintParams(const char *outFile)
    {
      FILE *file;
      file = fopen(outFile, "wa");
      fprintf(file, "  ID     AbsScale    RelNorm     A     Aerr    B     Berr    C     Cerr    D     Derr    E     Eerr    F     Ferr    G     Gerr\n");
      for (auto &efffit : fEffFits) {
        int detID = efffit.first;
        fprintf(file, "%4i", detID);
        fprintf(file, "  %8.7f   ", efffit.second.EffFunc->GetParameter(7));
        fprintf(file, "  %10.3f", fDetNorm[efffit.first]);
        for (int i=0; i<7; ++i) {
          fprintf(file, "  %5.4f  %5.4f ", efffit.second.EffFunc->GetParameter(i), efffit.second.EffFunc->GetParError(i));
        }
        fprintf(file,"\n");
      }
      fclose(file);
    }

    void MultiEffFit::WriteGraphs(std::string outDir)
    {
      for ( auto &det : fEffFits) {
        det.second.WriteGraph(outDir+"/det"+std::to_string(det.first));      
      }
    }        

    void EffFit::PrintParams(const char *outFile) {
      FILE *file;
      file = fopen(outFile, "wa");
      fprintf(file, "AbsScale     A     Aerr    B     Berr    C     Cerr    D     Derr    E     Eerr    F     Ferr    G     Gerr\n");
      fprintf(file, "  %8.7f   ", EffFunc->GetParameter(7));
      for (int i=0; i<7; ++i) {
        fprintf(file, "  %5.4f  %5.4f ", EffFunc->GetParameter(i), EffFunc->GetParError(i));
      }
      fprintf(file,"\n");
      fclose(file);
    }
  }    
}
