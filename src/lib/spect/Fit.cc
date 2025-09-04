#include <iostream>
#include <string.h>

/* ROOT */
#include <TArrow.h>
#include <TH1.h>
#include <TMarker.h>
#include <TMath.h>
#include <TMatrixD.h>
#include <TString.h>
#include <TText.h>
#include <TPolyMarker.h>
#include <TRatioPlot.h>
#include <TFitResult.h>

#include "Fit.hh"
#include "FitGuesses.hh"
#include <utils/Utilities.hh>
#include <toolkit/Peak.hh>

namespace GamR {
  namespace Spect {
    //extern PeakFitGuesses *gFitGuesses;
    
    GamR::Spect::PeakFit::PeakFit() {
      fFitGuesses = gFitGuesses;
    }

    GamR::Spect::PeakFit::PeakFit(double Low, double High) : fLow(Low), fHigh(High) {
      parameters = {};
      fFitGuesses = gFitGuesses;
    }

    GamR::Spect::PeakFit::PeakFit(double Low, double High, PeakFitGuesses *FitGuesses) : fLow(Low), fHigh(High) {
      parameters = {};
      fFitGuesses = FitGuesses;
    }
    
    void GamR::Spect::PeakFit::SetOpts(Option_t *option) {
      TString opts(option);
      opts.ToLower();
      
      /* iWidthsEnergy sets the sigma according to an empirical energy formula */
      //int iWidthsEnergy = 0;
      
      if (opts.Contains("z")) {
        parameters.iQuiet = 1;
      }
      if (opts.Contains("f")) {
        parameters.iFixWidths = 1;
      }
      if (opts.Contains("ff")) {
        parameters.iFixWidthsFile = 1;
      }
      if (opts.Contains("q")) {
        parameters.iQuadBack = 1;
      }
      if (opts.Contains("c")) {
        parameters.iConstantBack = 1;
      }
      if (opts.Contains("t")) {
        parameters.iTails1 = 1;
      }
      if (opts.Contains("s")) {
        parameters.iStep = 1;
      }
      if (opts.Contains("g")) {
        parameters.iTails2 = 1;
      }
      if (opts.Contains("e")) {
        parameters.iFixEnergy = 1;
      }
      if (opts.Contains("n")) {
        parameters.iNoFit = 1;
      }

      if (!(parameters.iStep || parameters.iTails1 || parameters.iTails2)) {
        fPeakType = GamR::TK::Gaussian;
      }
      else if (parameters.iStep && !parameters.iTails1 && !parameters.iTails2) {
        fPeakType = GamR::TK::StepGaussian;
      }
      else if (!parameters.iStep && parameters.iTails1) {
        fPeakType = GamR::TK::OneTailGaussian;
      }
      else if (!parameters.iStep && parameters.iTails2) {
        fPeakType = GamR::TK::TwoTailGaussian;
      }
      else if (parameters.iStep && parameters.iTails1) {
        fPeakType = GamR::TK::OneTailStepGaussian;
      }
      else if (parameters.iStep && parameters.iTails2) {
        fPeakType = GamR::TK::TwoTailStepGaussian;
      }

    }
    
    void GamR::Spect::PeakFit::SetBackground() {
      iParamCount = 0;
      int iPeak = 0;
      TString sFuncString;
      if (parameters.iQuadBack) {
        sFuncString.Form("[0] + [1]*(x-%f) + [2]*pow(x-%f, 2)", (fHigh+fLow)/2, (fHigh+fLow)/2);
        iParamCount = iParamCount + 3;
      } else if (parameters.iConstantBack) {
        sFuncString.Form("[0]");
        iParamCount = iParamCount + 1;
      }
      else {
        sFuncString.Form("[0] + [1]*(x-%f)", (fHigh+fLow)/2);
        iParamCount = iParamCount + 2;
      }

      
      fBackground = new TF1("fBackground", sFuncString.Data(), fLow, fHigh);
    }

    void GamR::Spect::PeakFit::SetPeaks(std::vector<double> Peaks) {
      //make a map
      std::map<std::string,double> mPeaks;
      //loop over Peaks and generate names
      for (int iPeak; iPeak<Peaks.size(); ++iPeak) {
        std::string name = "Peak" + std::to_string(iPeak);
        mPeaks[name] = Peaks[iPeak];
      }
      GamR::Spect::PeakFit::SetPeaks(mPeaks);
    }
    
    void GamR::Spect::PeakFit::SetPeaks(std::map<std::string,double> Peaks) {
      for (auto &mPeak : Peaks) {
        auto peakKey = mPeak.first;
        auto peak = mPeak.second;
        AddPeak(peakKey, fPeakType);
      }
    }

    void GamR::Spect::PeakFit::SetIndices(std::map<std::string,GamR::TK::FPeak*> Peaks) {
      std::string firstKey;
      int i = 0;
      for (auto &mPeak : Peaks) {
        auto peakKey = mPeak.first;
        auto peak = mPeak.second;  

        fPeakParamInds[peakKey]={};
        
        int iAmpParam = iParamCount;
        iParamCount++;
        fPeakParamInds[peakKey].iAmplitude = iAmpParam;
        int iCentParam = iParamCount;
        iParamCount++;
        fPeakParamInds[peakKey].iCentroid = iCentParam;
        int iWidthParam;
        int iSkewAmpParam;
        int iSkewWidthParam;
        int iStepAmpParam;
        int iSkewAmpParam2;
        int iSkewWidthParam2;
        if (parameters.iFixWidthsFile) {
          iWidthParam = -1;
        }
        else if (parameters.iFixWidths) {
          if (i == 0) {
            iWidthParam = iParamCount;
            iParamCount++;
            firstKey = peakKey;
          } else {
            iWidthParam = fPeakParamInds[firstKey].iWidth;
          }
        } else {
          iWidthParam = iParamCount;
          iParamCount++;
        }
        fPeakParamInds[peakKey].iWidth = iWidthParam;
        if (fPeakType == GamR::TK::StepGaussian ||
            fPeakType == GamR::TK::OneTailStepGaussian ||
            fPeakType == GamR::TK::TwoTailStepGaussian) {
          if (parameters.iFixWidthsFile) {
            iStepAmpParam = -1;
          }
          else if (parameters.iFixWidths) {
            if (i == 0) {
              iStepAmpParam = iParamCount;
              iParamCount++;
              firstKey = peakKey;
            } else {
              iStepAmpParam = fPeakParamInds[firstKey].iStepAmplitude;
            }
          } else {
            iStepAmpParam = iParamCount;
            iParamCount++;            
          }
          fPeakParamInds[peakKey].iStepAmplitude = iStepAmpParam;
        }

        if (fPeakType == GamR::TK::OneTailGaussian ||
            fPeakType == GamR::TK::OneTailStepGaussian ||
            fPeakType == GamR::TK::TwoTailGaussian ||
            fPeakType == GamR::TK::TwoTailStepGaussian) {

          if (parameters.iFixWidthsFile) {
            iSkewAmpParam = -1;
            iSkewWidthParam = -1;
          }
          else if (parameters.iFixWidths ) {
            if (i == 0) {
              iSkewAmpParam = iParamCount;
              iParamCount++;
              iSkewWidthParam = iParamCount;
              iParamCount++;
            } else {
              iSkewAmpParam = fPeakParamInds[firstKey].iSkewAmplitude;
              iSkewWidthParam = fPeakParamInds[firstKey].iSkewWidth;
            }
          } else {
            iSkewAmpParam = iParamCount;
            iParamCount++;
            iSkewWidthParam = iParamCount;
            iParamCount++;       
          }
          fPeakParamInds[peakKey].iSkewAmplitude = iSkewAmpParam;
          fPeakParamInds[peakKey].iSkewWidth = iSkewWidthParam;

          if (fPeakType == GamR::TK::TwoTailGaussian ||
              fPeakType == GamR::TK::TwoTailStepGaussian) {

            if (parameters.iFixWidthsFile) {
              iSkewAmpParam2 = -1;
              iSkewWidthParam2 = -1;
            }
            else if (parameters.iFixWidths) {
              if (i == 0) {
                iSkewAmpParam2 = iParamCount;
                iParamCount++;
                iSkewWidthParam2 = iParamCount;
                iParamCount++;
              } else {
                iSkewAmpParam2 = fPeakParamInds[firstKey].iSkewAmplitude2;
                iSkewWidthParam2 = fPeakParamInds[firstKey].iSkewWidth2;
              }
            } else {
              iSkewAmpParam2 = iParamCount;
              iParamCount++;
              iSkewWidthParam2 = iParamCount;
              iParamCount++;
            }
            fPeakParamInds[peakKey].iSkewAmplitude2 = iSkewAmpParam2;
            fPeakParamInds[peakKey].iSkewWidth2 = iSkewWidthParam2;
          } 
        }
	
        ++i;
      }
      /* this creates the total function from all the peaks + background */
      SetFunction();
      fTotal->SetNpx(500);
      
      /* set parameter names */
      fTotal->SetParName(0, "c");
      if (!parameters.iConstantBack) {
        fTotal->SetParName(1, "b");
      }
      if (parameters.iQuadBack) {
        fTotal->SetParName(2, "a");
      }
      
      i=0;
      for (auto &mpp : fPeakParamInds) {
        auto peakKey = mpp.first;
        auto pp = mpp.second;
        fTotal->SetParName(pp.iAmplitude, ("Amp" + std::to_string(i)).c_str());
        fTotal->SetParName(pp.iCentroid, ("Cent" + std::to_string(i)).c_str());
        if (parameters.iFixWidths && !parameters.iFixWidthsFile) {
          fTotal->SetParName(pp.iWidth, "Sigma");
        } else {
          fTotal->SetParName(pp.iWidth, ("Sigma" + std::to_string(i)).c_str());
        }        
        if (fPeakType == GamR::TK::StepGaussian ||
            fPeakType == GamR::TK::OneTailStepGaussian ||
            fPeakType == GamR::TK::TwoTailStepGaussian) {
          if (parameters.iFixWidths && !parameters.iFixWidthsFile) {
            fTotal->SetParName(pp.iStepAmplitude, "H");
          }
          else {
            fTotal->SetParName(pp.iStepAmplitude, ("H" + std::to_string(i)).c_str());
          }
        }

        if (fPeakType == GamR::TK::OneTailGaussian ||
            fPeakType == GamR::TK::OneTailStepGaussian ||
            fPeakType == GamR::TK::TwoTailGaussian ||
            fPeakType == GamR::TK::TwoTailStepGaussian) {

          if (parameters.iFixWidths && !parameters.iFixWidthsFile) {
            fTotal->SetParName(pp.iSkewAmplitude, "R");
            fTotal->SetParName(pp.iSkewWidth, "Beta");
          } else {
            fTotal->SetParName(pp.iSkewAmplitude, ("R" + std::to_string(i)).c_str());
            fTotal->SetParName(pp.iSkewWidth, ("Beta" + std::to_string(i)).c_str());
          }

          if (fPeakType == GamR::TK::TwoTailGaussian ||
              fPeakType == GamR::TK::TwoTailStepGaussian) {
            if (parameters.iFixWidths && !parameters.iFixWidthsFile) {
              fTotal->SetParName(pp.iSkewAmplitude2, "R2");
              fTotal->SetParName(pp.iSkewWidth2, "Beta2");
            } else {
              fTotal->SetParName(pp.iSkewAmplitude2, ("R2_" + std::to_string(i)).c_str());
              fTotal->SetParName(pp.iSkewWidth2, ("Beta2_" + std::to_string(i)).c_str());
            }
          }
        }
        ++i;
      }
    }

    void GamR::Spect::PeakFit::SetGuesses(TH1 *hist, std::map<std::string,GamR::TK::FPeak*> mPeaks, std::vector<std::string> FixPeaks /*= {}*/) {
      std::map<std::string,double> mcentroids;
      for (auto &mpeak : mPeaks) {
        auto peakKey = mpeak.first;
        auto peak = mpeak.second;
        mcentroids[peakKey]=peak->GetCent();
      }
      GamR::Spect::PeakFit::SetGuesses(hist,mcentroids,FixPeaks);
    }

    void GamR::Spect::PeakFit::SetGuesses(TH1 *hist, std::map<std::string, double> Peaks, std::vector<std::string> FixPeaks /*= {}*/) {
      for (auto &peakKey : FixPeaks) {
        FixPeakEnergy(peakKey);
      }
	
      /* set initial guesses */
      fNData = hist->FindBin(fHigh) - hist->FindBin(fLow) + 1;
      double slope = (hist->GetBinContent(hist->FindBin(fHigh)) - hist->GetBinContent(hist->FindBin(fLow))) / (fHigh - fLow);
      if (!parameters.iConstantBack) {
        fTotal->SetParameter(1, slope);
      }
      double offset = (hist->GetBinContent(hist->FindBin(fLow)) +
                       hist->GetBinContent(hist->FindBin(fHigh)))/2.0;
      fTotal->SetParameter(0, offset);
      if (parameters.iQuadBack) {
        fTotal->SetParameter(2, 0.01);
      }
      //for (int i = 0; i < (int)Peaks.size(); i++) {
      double histMax = hist->GetMaximum();
      for (auto &peak : Peaks) {
        auto peakKey = peak.first;
        auto cent = peak.second;

        //std::cout << peakKey << "   " << cent << std::endl;
        //int nBin = hist->FindBin(peaks[i]);
        int nBin = hist->FindBin(cent);
        //auto pp = fPeakParamInds[i];
        auto pp = fPeakParamInds[peakKey];
        fTotal->SetParameter(pp.iAmplitude, hist->GetBinContent(nBin) - (offset + slope*(cent - (fHigh + fLow)/2.0)));
        //make sure peaks are not negative
        fTotal->SetParLimits(pp.iAmplitude, 0, histMax*2.0);
        //fTotal->SetParameter(pp.iCentroid, Peaks[i]);
        fTotal->SetParameter(pp.iCentroid, cent);
        //std::cout << pp.iCentroid << "   " << cent << std::endl;
        if (fPeakEnFix.find(peakKey) != fPeakEnFix.end()) {
          if ( fPeakEnFix[peakKey] == 1 ) {
            fTotal->FixParameter(pp.iCentroid, cent);
          }
        }


        //sigma = 5*bin width (?)        
        //fTotal->SetParameter(pp.iWidth, 5.0*hist->GetBinWidth(i));
        if (!parameters.iFixWidthsFile) {
        fTotal->SetParameter(pp.iWidth, fFitGuesses->fWidth.val);
        fTotal->SetParLimits(pp.iWidth, fFitGuesses->fWidth.low, fFitGuesses->fWidth.high);
        }

        if (fPeakType == GamR::TK::StepGaussian ||
            fPeakType == GamR::TK::OneTailStepGaussian ||
            fPeakType == GamR::TK::TwoTailStepGaussian) {
          /*
          double low;
          double high;
          fTotal->GetParLimits(pp.iStepAmplitude,low,high);
          if (low==high) {
            fTotal->FixParameter(pp.iStepAmplitude, 0.);
          } else {
            fTotal->SetParameter(pp.iStepAmplitude, (high-low)/2.);
          }
          */
          if (!parameters.iFixWidthsFile) {
          fTotal->FixParameter(pp.iStepAmplitude, 0.);
          }
        }

        if (fPeakType == GamR::TK::OneTailGaussian ||
            fPeakType == GamR::TK::OneTailStepGaussian ||
            fPeakType == GamR::TK::TwoTailGaussian ||
            fPeakType == GamR::TK::TwoTailStepGaussian) {

          /*
            fTotal->SetParameter(skewWidthParameters[i], 1.);
            fTotal->SetParLimits(skewWidthParameters[i], 0, 10);
            fTotal->SetParameter(skewAmplitudeParameters[i], 10.);
            fTotal->SetParLimits(skewAmplitudeParameters[i], 0, 50);
            fTotal->SetParameter(stepAmplitudeParameters[i], 1.);
            fTotal->SetParLimits(stepAmplitudeParameters[i], 0, 20);
          */
          if (!parameters.iFixWidthsFile) {
          fTotal->FixParameter(pp.iSkewWidth, 2.5);
          fTotal->FixParameter(pp.iSkewAmplitude, 0.0);
          }
          if (fPeakType == GamR::TK::TwoTailGaussian ||
              fPeakType == GamR::TK::TwoTailStepGaussian) {

            if (!parameters.iFixWidthsFile) {
            fTotal->FixParameter(pp.iSkewWidth2, 5);
            fTotal->FixParameter(pp.iSkewAmplitude2, 0.0);
            }
          }
        }
      }
    }

    void GamR::Spect::PeakFit::SetLimit(std::string peakKey, std::string parameterKey, double lowerLimit, double upperLimit) {
      auto pp = fPeakParamInds[peakKey];
      auto peak = fPeaks[peakKey];
      if (!peak) std::cout << "Error: Peak '" << peakKey << "' not found." << std::endl;
      auto func = peak->GetFunc();
      func->SetParLimits(func->GetParNumber((TString)parameterKey),lowerLimit,upperLimit);
      
    }

    void GamR::Spect::PeakFit::Fit(TH1 *hist, Option_t *foption) {
      //if (!parameters.iQuiet) {
      //  fFitGuesses->Print();
      //}
      std::string fopts(foption);
      fopts = fopts + " R";

      fFitGuesses->fScale.val = 1./(hist->GetBinCenter(2)-hist->GetBinCenter(1));

      //
      if (parameters.iFixWidthsFile) {
        FILE *file = fopen("FitWidths.dat", "ra");
        if (!file) { std::cerr << "Error! file FitWidths.dat not opened" << std::endl; return;}    
        std::stringstream ss;
        char cline[2048];

        gWidth = new TGraph();
        gStep = new TGraph();
        gSkew = new TGraph();
        gSkewAmp = new TGraph();
        gSkew2 = new TGraph();
        gSkewAmp2 = new TGraph();
        
        while(std::fgets(cline, sizeof cline, file)!=NULL) {
          std::string line(cline);
          if (line.size() == 0) { continue; }
          if (line[0] == '#') { continue; }
          if (line[0] == ';') { continue; }
          if (line[0] == '!') { continue; }

          ss.clear();
          ss.str(line);

          double energy, width, step, skew, skewamp, skew2, skewamp2;
          ss >> energy >> width >> step >> skew >> skewamp >> skew2 >> skewamp2;

          gWidth->AddPoint(energy, width);
          gStep->AddPoint(energy,step);
          gSkew->AddPoint(energy,skew);
          gSkewAmp->AddPoint(energy,skewamp);
          gSkew2->AddPoint(energy,skew2);          
          gSkewAmp2->AddPoint(energy,skewamp2);
        }
      }
      
      // first fit, only gaussian
      // this seems to be broken (sometimes?) with tails when tail amplitude fixed at zero
      if (fPeakType == GamR::TK::Gaussian) {
        if (!parameters.iNoFit) {
          hist->Fit(fTotal, fopts.c_str());
        }
      }
      
      // with step now
      if (fPeakType == GamR::TK::StepGaussian ||
          fPeakType == GamR::TK::OneTailStepGaussian ||
          fPeakType == GamR::TK::TwoTailStepGaussian) {
        for (auto &mpp : fPeakParamInds) {
          auto peakKey = mpp.first;
          auto pp = mpp.second;
          if (!parameters.iFixWidthsFile) {
          fTotal->SetParameter(pp.iStepAmplitude, fFitGuesses->fStepAmp.val);
          fTotal->SetParLimits(pp.iStepAmplitude, fFitGuesses->fStepAmp.low, fFitGuesses->fStepAmp.high);
          }
          /*
          double low;
          double high;
          fTotal->GetParLimits(pp.iStepAmplitude,low,high);
          fTotal->SetParameter(pp.iStepAmplitude, 1.);
          if (low==high) {
            fTotal->SetParLimits(pp.iStepAmplitude, 0, 20.);
          }
          */
        }
        if (!parameters.iNoFit) {
          hist->Fit(fTotal, fopts.c_str());
        }
      }
      
      // 2 more fits for tails, iterative
      if (fPeakType == GamR::TK::OneTailGaussian ||
          fPeakType == GamR::TK::OneTailStepGaussian ||
          fPeakType == GamR::TK::TwoTailGaussian ||
          fPeakType == GamR::TK::TwoTailStepGaussian) {
        for (auto &mpp : fPeakParamInds) {
          auto peakKey = mpp.first;
          auto pp = mpp.second;
          if (!parameters.iFixWidthsFile) {
          fTotal->SetParameter(pp.iSkewWidth, fFitGuesses->fSkewWidth.val);
          fTotal->SetParLimits(pp.iSkewWidth, fFitGuesses->fSkewWidth.low, fFitGuesses->fSkewWidth.high);
          fTotal->SetParameter(pp.iSkewAmplitude, fFitGuesses->fSkewAmp.val);
          fTotal->SetParLimits(pp.iSkewAmplitude, fFitGuesses->fSkewAmp.low, fFitGuesses->fSkewAmp.high);
          }
        }
        if (!parameters.iNoFit) {
          hist->Fit(fTotal, fopts.c_str());
        }
      }
      
      if (fPeakType == GamR::TK::TwoTailGaussian ||
          fPeakType == GamR::TK::TwoTailStepGaussian) {
        for (auto &mpp : fPeakParamInds) {
          auto peakKey = mpp.first;
          auto pp = mpp.second;
          if (!parameters.iFixWidthsFile) {
          fTotal->SetParameter(pp.iSkewWidth2, fFitGuesses->fSkewWidth2.val);
          fTotal->SetParLimits(pp.iSkewWidth2, fFitGuesses->fSkewWidth2.low, fFitGuesses->fSkewWidth2.high);
          fTotal->SetParameter(pp.iSkewAmplitude2, fFitGuesses->fSkewAmp2.val);
          fTotal->SetParLimits(pp.iSkewAmplitude2, fFitGuesses->fSkewAmp2.low, fFitGuesses->fSkewAmp2.high);
          }
        }
        if (!parameters.iNoFit) {
          hist->Fit(fTotal, fopts.c_str());
        }
      }
      
    }

    void GamR::Spect::PeakFit::SetResults(TH1* hist) {
      /* set results in all the components of the results object from fTotal*/
      
      GetBackground()->SetParameter(0, fTotal->GetParameter(0));
      if (!parameters.iConstantBack) {
        GetBackground()->SetParameter(1, fTotal->GetParameter(1));
      }
      if (parameters.iQuadBack) {
        GetBackground()->SetParameter(2, fTotal->GetParameter(2));
      }
      SetChi2(hist->Chisquare(fTotal, "R"));
      for (auto &mpeak : fPeaks) {
        auto peakKey = mpeak.first;
        auto peak = mpeak.second;
        auto pp = fPeakParamInds[peakKey];
        switch(fPeakType) {
        case GamR::TK::Gaussian : {
          if (parameters.iFixWidthsFile) {
            peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                gWidth->Eval(fTotal->GetParameter(pp.iCentroid))/2.3548});
            peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                0});
          }
          else {
            peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                fTotal->GetParameter(pp.iWidth)});
            peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                0.0});
          }
          break;
        }
        case GamR::TK::StepGaussian : {
          if (parameters.iFixWidthsFile) {
            peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                gWidth->Eval(fTotal->GetParameter(pp.iCentroid))/2.3548,
                gStep->Eval(fTotal->GetParameter(pp.iCentroid))});
            peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                0.0,
                0.0});
          }
          else {
            peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                fTotal->GetParameter(pp.iWidth),
                fTotal->GetParameter(pp.iStepAmplitude)});
            peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                fTotal->GetParError(pp.iWidth),
                fTotal->GetParError(pp.iStepAmplitude)});
          }
          break;
        }
        case GamR::TK::OneTailGaussian : {
          if (parameters.iFixWidthsFile) {
            peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                gWidth->Eval(fTotal->GetParameter(pp.iCentroid))/2.3548,
                gSkewAmp->Eval(fTotal->GetParameter(pp.iCentroid)),
                gSkew->Eval(fTotal->GetParameter(pp.iCentroid))});
            peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                0.0,
                0.0,
                0.0});
          }
          else {
            peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                fTotal->GetParameter(pp.iWidth),
                fTotal->GetParameter(pp.iSkewAmplitude),
                fTotal->GetParameter(pp.iSkewWidth)});
            peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                fTotal->GetParError(pp.iWidth),
                fTotal->GetParError(pp.iSkewAmplitude),
                fTotal->GetParError(pp.iSkewWidth)});
          }
          break;
        }
        case GamR::TK::TwoTailGaussian : {
          if (parameters.iFixWidthsFile) {
            peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                gWidth->Eval(fTotal->GetParameter(pp.iCentroid))/2.3548,
                gSkewAmp->Eval(fTotal->GetParameter(pp.iCentroid)),
                gSkew->Eval(fTotal->GetParameter(pp.iCentroid)),
                gSkewAmp2->Eval(fTotal->GetParameter(pp.iCentroid)),
                gSkew2->Eval(fTotal->GetParameter(pp.iCentroid))});
            peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                0.0,
                0.0,
                0.0,
                0.0,
                0.0});
          }
          else {          
            peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                fTotal->GetParameter(pp.iWidth),
                fTotal->GetParameter(pp.iSkewAmplitude),
                fTotal->GetParameter(pp.iSkewWidth),
                fTotal->GetParameter(pp.iSkewAmplitude2),
                fTotal->GetParameter(pp.iSkewWidth2)});
            peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                fTotal->GetParError(pp.iWidth),
                fTotal->GetParError(pp.iSkewAmplitude),
                fTotal->GetParError(pp.iSkewWidth),
                fTotal->GetParError(pp.iSkewAmplitude2),
                fTotal->GetParError(pp.iSkewWidth2)});
          }
          break;
        }
        case GamR::TK::OneTailStepGaussian : {
          if (parameters.iFixWidthsFile) {
            peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                gWidth->Eval(fTotal->GetParameter(pp.iCentroid))/2.3548,
                gSkewAmp->Eval(fTotal->GetParameter(pp.iCentroid)),
                gSkew->Eval(fTotal->GetParameter(pp.iCentroid)),
                gStep->Eval(fTotal->GetParameter(pp.iCentroid))});
            peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                0.0,
                0.0,
                0.0,
                0.0});

          }
          else {
          peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                fTotal->GetParameter(pp.iWidth),
                fTotal->GetParameter(pp.iSkewAmplitude),
                fTotal->GetParameter(pp.iSkewWidth),
                fTotal->GetParameter(pp.iStepAmplitude)});
          peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                fTotal->GetParError(pp.iWidth),
                fTotal->GetParError(pp.iSkewAmplitude),
                fTotal->GetParError(pp.iSkewWidth),
                fTotal->GetParError(pp.iStepAmplitude)});
          }
          break;
        }
        case GamR::TK::TwoTailStepGaussian : {
          if (parameters.iFixWidthsFile) {
            peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                gWidth->Eval(fTotal->GetParameter(pp.iCentroid))/2.3548,
                gSkewAmp->Eval(fTotal->GetParameter(pp.iCentroid)),
                gSkew->Eval(fTotal->GetParameter(pp.iCentroid)),
                gSkewAmp2->Eval(fTotal->GetParameter(pp.iCentroid)),
                gSkew2->Eval(fTotal->GetParameter(pp.iCentroid)),
                gStep->Eval(fTotal->GetParameter(pp.iCentroid))});
            peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                0.0,
                0.0,
                0.0,
                0.0,
                0.0,
                0.0});
          }
          else {
            peak->SetParameters({fTotal->GetParameter(pp.iAmplitude),
                fTotal->GetParameter(pp.iCentroid),
                fTotal->GetParameter(pp.iWidth),
                fTotal->GetParameter(pp.iSkewAmplitude),
                fTotal->GetParameter(pp.iSkewWidth),
                fTotal->GetParameter(pp.iSkewAmplitude2),
                fTotal->GetParameter(pp.iSkewWidth2),
                fTotal->GetParameter(pp.iStepAmplitude)});
            peak->SetParErrors({fTotal->GetParError(pp.iAmplitude),
                fTotal->GetParError(pp.iCentroid),
                fTotal->GetParError(pp.iWidth),
                fTotal->GetParError(pp.iSkewAmplitude),
                fTotal->GetParError(pp.iSkewWidth),
                fTotal->GetParError(pp.iSkewAmplitude2),
                fTotal->GetParError(pp.iSkewWidth2),
                fTotal->GetParError(pp.iStepAmplitude)});
          }
          break;
        }
        }
      }
    }

    void GamR::Spect::PeakFit::PrintResults() {
      std::cout << "Chi2 = " << fChi2 << ", ndata = " << fNData << ",  NDF = " << fNData - fNPars << ", Chi2/NDF = " << fChi2/(double)(fNData - fNPars) << std::endl;
      TString sPrintString;      
      if (!parameters.iQuiet) {
        sPrintString.Form("Peak   Centroid       Height         FWHM           Area           Counts  ");
        std::printf("%s\n", sPrintString.Data());
      }
      
      int i=0;
      for (auto &mPeak : fPeaks) {
        auto peakKey = mPeak.first;
        auto peak = mPeak.second;
        char line[120];
        *line = '\0';
        GamR::Utils::wrresult(line, peak->GetCent(),
                              peak->GetCentError(), 15);
        GamR::Utils::wrresult(line, peak->GetAmp(),
                              peak->GetAmpError(), 30);
        GamR::Utils::wrresult(line, peak->GetWidth(),
                              peak->GetWidthError(), 45);
        GamR::Utils::wrresult(line, peak->GetArea(),
                              peak->GetAreaError(), 60);
        GamR::Utils::wrresult(line, peak->GetArea()*fFitGuesses->fScale.val,
                              peak->GetAreaError()*fFitGuesses->fScale.val, 60);
        if (!parameters.iQuiet) {
          std::printf("%-5d %s\n", i, line);
        }
        ++i;
      }
    }
    
    /**
       Fits an arbitrary number of Gaussian peaks over a quadratic background.

       @param hist Histogram to be fitted to
       @param Low Lower bound of fit
       @param High Upper bound of fit
       @param Peaks std::vector of doubles containing approximate locations of peak
       centroids (starting guesses)
       @return A TF1* which is the fitted function
    */
    GamR::Spect::PeakFit *FitPeaks(TH1 *hist, double Low, double High, std::vector<double> Peaks, Option_t *foption /*=""*/,
                                   Option_t *option /*=""*/, std::vector<std::string> FixPeaks) {
      std::map<std::string, double> mPeaks;
      for (int iPeak=0; iPeak<Peaks.size(); ++iPeak) {
        std::string peakKey;
        peakKey = "Peak" + std::to_string(iPeak);
        mPeaks[peakKey] = Peaks[iPeak];
      }
      return GamR::Spect::FitPeaks(hist, Low, High, mPeaks, foption, option, FixPeaks);
    }
    
    GamR::Spect::PeakFit *FitPeaks(TH1 *hist, double Low, double High, std::map<std::string,double> Peaks, Option_t *foption /*=""*/,
                                   Option_t *option /*=""*/, std::vector<std::string> FixPeaks) {

      GamR::Spect::PeakFit *retval = new GamR::Spect::PeakFit(Low, High);

      std::cout << retval->GetLow() << "   " << retval->GetHigh() << std::endl;
      //setup the fit: make the relevant GamR::TK::FPeak objects, set the background, make the function
      //to fit, and set initial guesses in a sensible way

      retval->SetUp(hist, Peaks, option, FixPeaks);
      //execute the fit to the histogram

      retval->Fit(hist, foption);

      //draw total function after fitting
      retval->GetTotal()->Draw("same");

      //set the results of the fitted total function to all the sub-functions:
      //background, each peak's individual parameters
      retval->SetResults(hist);

      //print results
      retval->PrintResults();

      return retval;
    }

    /**
       Fits an arbitrary number of peaks over a quadratic background, using mouse
       input.

       Click left and right for fitting area, then once for every peak centroid. Any
       key will start fitting.

       @param canvas A pointer to a TCanvas object containing a single histogram.
       Note that this function has not been tested for canvases containing multiple
       histograms.
    */
    GamR::Spect::PeakFit *FitPeaks(TCanvas *canvas /*=gPad->GetCanvas()*/, Option_t *foption /*=""*/, Option_t *option /*=""*/)
    {
      TH1D *hist = GamR::Utils::GetHist1D(canvas);
      if (!hist) { return NULL; }

      TString opts(option);
      opts.ToLower();

      int iQuiet = 0;

      if (opts.Contains("z")) {
        iQuiet = 1;
      }
      
      /* get clicks for background and peaks */

      TMarker *marker;
      TObject *obj;

      int peaks = -2;

      double low = 0;
      double high = 0;
      std::vector<double> centroids;
      std::vector<TArrow *> arrows;
      std::vector<TText *> labels;
      std::vector<TLine *> bounds;

      canvas->SetCrosshair();

      canvas->Update();

      std::string canvasname = canvas->GetName();

      //std::string functioncall = "GamR::Utils::GetClick(" + canvasname + ")";

      GamR::Utils::Clicker click;
      canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "GamR::Utils::Clicker", &click, "GetClick(Int_t,Int_t,Int_t,TObject*)");
      //canvas->AddExec("ex", functioncall.c_str());

      while (true) {
        if (peaks == -2) {
          if (!iQuiet){
            std::cout << "Click for lower bound of region..." << std::endl;
          }
        } else if (peaks == -1) {
          if (!iQuiet){
            std::cout << "Click for upper bound of region..." << std::endl;
          }
        } else {
          if (!iQuiet){
            std::cout << "Click for peak centroid, press any key to fit..." << std::endl;
          }
        }
        obj = canvas->WaitPrimitive();
        if (!obj)
          break;
        if (strncmp(obj->ClassName(), "TMarker", 7) == 0) {
          marker = (TMarker *)obj;
          if (peaks == -2) {
            low = marker->GetX();
            if (!iQuiet){
              std::cout << "Lower bound: " << low << std::endl;
            }
            TLine *line = new TLine(marker->GetX(), hist->GetBinContent(hist->FindBin(marker->GetX())), marker->GetX(),
                                    canvas->GetUymin());
            line->Draw();
            bounds.push_back(line);
          } else if (peaks == -1) {
            high = marker->GetX();
            if (!iQuiet){
              std::cout << "Upper bound: " << high << std::endl;
            }
            TLine *line = new TLine(marker->GetX(), hist->GetBinContent(hist->FindBin(marker->GetX())), marker->GetX(),
                                    canvas->GetUymin());
            line->Draw();
            bounds.push_back(line);
          } else {
            centroids.push_back(marker->GetX());
            if (!iQuiet){
              std::cout << "Centroid: " << marker->GetX() << std::endl;
            }
            TArrow *arrow = new TArrow(marker->GetX(), 0.8 * hist->GetBinContent(hist->FindBin(marker->GetX())),
                                       marker->GetX(), 0.95 * hist->GetBinContent(hist->FindBin(marker->GetX())), 0.01);
            TString s;
            s.Form("%d", peaks);
            TText *text =
              new TText(marker->GetX(), 0.75 * hist->GetBinContent(hist->FindBin(marker->GetX())), s.Data());
            text->SetTextSize(0.03);
            text->SetTextAlign(21);

            arrow->Draw();
            text->Draw();

            arrows.push_back(arrow);
            labels.push_back(text);
          }
          peaks = peaks + 1;
          delete marker;
        }
      }

      //canvas->DeleteExec("ex");
      canvas->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", &click, "GetClick(Int_t,Int_t,Int_t,TObject*)");

      if (peaks < 1) {
        if (!iQuiet){
          std::cout << "defined no peaks!" << std::endl;
        }
        canvas->SetCrosshair(0);
        hist->Draw("hist");
        return NULL;
      }

      std::vector<std::string> FixEnergies;
      if (opts.Contains("e")) {
	std::cout << "Fixing peak energies: " << std::endl;
	double energy;
	int index = 0;
	for (auto &cent : centroids) {
	  energy = 0;
	  std::cout << "Peak " << index << " [ " << cent << " ] : ";
	  std::string line;
	  std::getline(std::cin, line);

	  if (line.empty()) { index += 1; continue; }
	  std::stringstream ss;
	  ss << line;
	  ss >> energy;

	  if (energy != 0) {
	    centroids[index] = energy;
	    FixEnergies.push_back("Peak"+std::to_string(index));
	  }
	  index += 1;
	}
      }

      GamR::Spect::PeakFit *retval = FitPeaks(hist, low, high, centroids, foption, option, FixEnergies);

      TF1 *func = retval->GetTotal();      

      // draw background, individual peaks, and arrows       
      TF1 *background = retval->GetBackground();

      background->Draw("same");
      
      if ((int)centroids.size() >= 1) {
        int i=0;
        //for (int i = 0; i < (int)centroids.size(); i++) {
        for (auto &mpeak : retval->GetPeaks()) {
          auto peakKey = mpeak.first;
          auto peak = mpeak.second;
          //GamR::TK::FPeak *peak = retval->Get(i);
          //TF1 *single = retval->GetPeakBG(i);
          TF1 *single = retval->GetPeakBG(peakKey);
          single->SetNpx(500);
          single->SetLineColor(kBlue+1);
          single->SetLineWidth(2);
          single->Draw("same");

          TF1 *step = retval->GetPeakStepBG(peakKey);
          if (step != NULL) {
            step->SetNpx(500);
            step->SetLineColor(kBlack);
            step->SetLineWidth(1);
            step->Draw("same");
          }

          if ((retval->GetPeakType() != GamR::TK::Gaussian) &&
              (retval->GetPeakType() != GamR::TK::StepGaussian)) {
            TF1 *gauss = retval->GetPeakGaussBG(peakKey);
            if (gauss != NULL) {
              gauss->SetNpx(500);
              gauss->SetLineWidth(1);
              gauss->SetLineColor(kGreen+2);
              gauss->Draw("same");
            }
          }
          
          TArrow *arrow = arrows[i];
          canvas->GetListOfPrimitives()->Remove(arrow);
          arrow->SetX1(peak->GetCent());
          arrow->SetY1(0.8 *
                       single->Eval(peak->GetCent()));
          arrow->SetX2(peak->GetCent());
          arrow->SetY2(0.95 *
                       single->Eval(peak->GetCent()));

          TString s;
          s.Form("%d", i);
          TText *text = labels[i];
          canvas->GetListOfPrimitives()->Remove(text);
          text->SetX(peak->GetCent());
          text->SetY(0.75 *
                     single->Eval(peak->GetCent()));
          text->SetTextSize(0.03);
          text->SetTextAlign(21);

          canvas->Modified();
          canvas->Update();
          arrow->Draw();
          text->Draw();
          canvas->Update();
          ++i;
        }
      }

      func->Draw("same");
      
      //TRatioPlot *rp = new TRatioPlot(hist);
      //rp->Draw();
      // draw residuals 
      // calculate y offset 
      
      int iLowBin = hist->FindBin(low);
      int iHighBin = hist->FindBin(high);
      double min = canvas->GetUymin();
      double offset = min + (std::min(hist->GetBinContent(iLowBin), hist->GetBinContent(iHighBin)) - min) / 2.0;

      TH1D *residuals = new TH1D("residuals", "residuals", iHighBin - iLowBin + 1,
                                 hist->GetBinCenter(iLowBin) - hist->GetBinWidth(iLowBin) / 2.0,
                                 hist->GetBinCenter(iHighBin) + hist->GetBinWidth(iHighBin) / 2.0);
      for (int i = 1; i <= iHighBin - iLowBin + 1; i++) {
        residuals->SetBinContent(i, hist->GetBinContent(i + iLowBin - 1) -
                                 func->Eval(hist->GetBinCenter(i + iLowBin - 1)) + offset);
        residuals->SetBinError(i, hist->GetBinError(i + iLowBin - 1));
      }

      TF1 *zeroFunc = new TF1("zero", "[0]", low, high);
      zeroFunc->SetParameter(0, offset);
      residuals->SetMarkerSize(0.5);
      residuals->Draw("hist E1 same");
      zeroFunc->Draw("same");      
      
      
      // update and wait for key press       
      canvas->Update();
      if (!iQuiet){
        std::cout << "Press any key to exit" << std::endl;
      }
      canvas->WaitPrimitive();

      
      // clean up      
      residuals->Delete();
      hist->Draw("hist");
      
      canvas->SetCrosshair(0);

      return retval;
    } /* function FitPeaks */

    void PeakFit::AddPeak(std::string peakKey, GamR::TK::FPeak* peak) {
      fPeakKeys[(int)fPeaks.size()] = peakKey;
      fPeaks[peakKey] = peak;
    }

    void PeakFit::AddPeak(std::string peakKey, GamR::TK::PeakType peaktype) {
      if (GetNPeaks()==0){
        fPeakType = peaktype;
      } else {
        if (fPeakType!=peaktype) {
          std::cout << "Error: peak types must be the same.";
          return;
        }
      }
      switch(fPeakType) {      
      case GamR::TK::Gaussian: {
        GamR::TK::GaussianPeak *gpeak = new GamR::TK::GaussianPeak(fLow, fHigh);          
        AddPeak(peakKey, gpeak);
        break;
      }
      case GamR::TK::StepGaussian: {
        GamR::TK::StepGaussianPeak *sgpeak = new GamR::TK::StepGaussianPeak(fLow, fHigh);          
        AddPeak(peakKey, sgpeak);
        break;
      }
      case GamR::TK::OneTailGaussian: {
        GamR::TK::OneTailGaussianPeak *otgpeak = new GamR::TK::OneTailGaussianPeak(fLow, fHigh);          
        AddPeak(peakKey, otgpeak);
        break;
      }
      case GamR::TK::TwoTailGaussian: {
        GamR::TK::TwoTailGaussianPeak *ttgpeak = new GamR::TK::TwoTailGaussianPeak(fLow, fHigh);          
        AddPeak(peakKey, ttgpeak);
        break;
      }
      case GamR::TK::OneTailStepGaussian: {
        GamR::TK::OneTailStepGaussianPeak *otsgpeak = new GamR::TK::OneTailStepGaussianPeak(fLow, fHigh);
        AddPeak(peakKey, otsgpeak);
        break;
      }
      case GamR::TK::TwoTailStepGaussian: {
        GamR::TK::TwoTailStepGaussianPeak *ttsgpeak = new GamR::TK::TwoTailStepGaussianPeak(fLow, fHigh);  
        AddPeak(peakKey, ttsgpeak);
        break;
      }
      }
    }

    void PeakFit::AddPeak(std::string peakKey, GamR::TK::PeakType peaktype, double centroid) {
      //make correct type of peak and add, this will break if a new type of peak is added.
      AddPeak(peakKey, peaktype);
      SetCent(peakKey,centroid);
    }

    double PeakFit::GetAmp(std::string peakKey) {
      return fPeaks[peakKey]->GetAmp();
    }

    double PeakFit::GetAmpError(std::string peakKey) {
      return fPeaks[peakKey]->GetAmpError();
    }

    double PeakFit::GetCent(std::string peakKey) {
      return fPeaks[peakKey]->GetCent();
    }

    double PeakFit::GetCentError(std::string peakKey) {
      return fPeaks[peakKey]->GetCentError();
    }

    double PeakFit::GetWidth(std::string peakKey) {
      return fPeaks[peakKey]->GetWidth();
    }

    double PeakFit::GetWidthError(std::string peakKey) {
      return fPeaks[peakKey]->GetWidthError();
    }

    
    void PeakFit::SetAmp(std::string peakKey, double amp) {
      fPeaks[peakKey]->SetAmp(amp);
    }

    void PeakFit::SetAmpError(std::string peakKey, double error) {
      fPeaks[peakKey]->SetAmpError(error);
    }

    void PeakFit::SetCent(std::string peakKey, double centroid) {
      fPeaks[peakKey]->SetCent(centroid);
    }

    void PeakFit::SetCentError(std::string peakKey, double error) {
      fPeaks[peakKey]->SetCentError(error);
    }

    void PeakFit::SetWidth(std::string peakKey, double width) {
      fPeaks[peakKey]->SetWidth(width);
    }

    void PeakFit::SetWidthError(std::string peakKey, double error) {
      fPeaks[peakKey]->SetWidthError(error);
    }
    
    void PeakFit::SetFunction() {
      fTotal = new TF1("func",
                       [&](double *x, double *p){
                         double ret = 0;
                         fBackground->SetParameter(0, p[0]);
                         if (!parameters.iConstantBack) {
                           fBackground->SetParameter(1, p[1]);
                         }
                         if (parameters.iQuadBack) {
                           fBackground->SetParameter(2, p[2]);
                         }
                         ret += fBackground->Eval(x[0]);

                         for (auto &mpp : fPeakParamInds) {
                           auto peakKey = mpp.first;
                           auto pp = mpp.second;
                           switch(fPeakType) {      
                           case GamR::TK::Gaussian: {
                             if (parameters.iFixWidthsFile) {
                               fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],                                   
                                   gWidth->Eval(p[pp.iCentroid])/2.3548});
                             }
                             else {
                               fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],
                                   p[pp.iWidth]});
                             }
                             break;
                           }
                           case GamR::TK::StepGaussian: {
                             if (parameters.iFixWidthsFile) {
                             fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],
                                   gWidth->Eval(p[pp.iCentroid])/2.3548,
                                   gStep->Eval(p[pp.iCentroid])});
                             }
                             else {
                               fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],
                                   p[pp.iWidth],
                                   p[pp.iStepAmplitude]});
                             }
                             break;
                           }
                           case GamR::TK::OneTailGaussian: {
                             if (parameters.iFixWidthsFile) {
                               fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],
                                   gWidth->Eval(p[pp.iCentroid])/2.3548,
                                   gSkewAmp->Eval(p[pp.iCentroid]),
                                   gSkew->Eval(p[pp.iCentroid])});
                             }
                             else {
                               fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],
                                   p[pp.iWidth],
                                   p[pp.iSkewAmplitude],
                                   p[pp.iSkewWidth]});
                             }
                             break;
                           }
                           case GamR::TK::TwoTailGaussian: {
                             if (parameters.iFixWidthsFile) {
                               fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],
                                   gWidth->Eval(p[pp.iCentroid])/2.3548,
                                   gSkewAmp->Eval(p[pp.iCentroid]),
                                   gSkew->Eval(p[pp.iCentroid]),
                                   gSkewAmp2->Eval(p[pp.iCentroid]),
                                   gSkew2->Eval(p[pp.iCentroid])});
                             }
                             else {
                               fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],
                                   p[pp.iWidth],
                                   p[pp.iSkewAmplitude],
                                   p[pp.iSkewWidth],
                                   p[pp.iSkewAmplitude2],
                                   p[pp.iSkewWidth2]});
                             }
                             break;
                           }
                           case GamR::TK::OneTailStepGaussian: {
                             if (parameters.iFixWidthsFile) {
                               fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],
                                   gWidth->Eval(p[pp.iCentroid])/2.3548,
                                   gSkewAmp->Eval(p[pp.iCentroid]),
                                   gSkew->Eval(p[pp.iCentroid]),
                                   gStep->Eval(p[pp.iCentroid])});
                             }
                             else {
                               fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],
                                   p[pp.iWidth],
                                   p[pp.iSkewAmplitude],
                                   p[pp.iSkewWidth],
                                   p[pp.iStepAmplitude]});
                             }
                             break;
                           }
                           case GamR::TK::TwoTailStepGaussian: {
                             if (parameters.iFixWidthsFile) {
                               fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],
                                   gWidth->Eval(p[pp.iCentroid])/2.3548,
                                   gSkewAmp->Eval(p[pp.iCentroid]),
                                   gSkew->Eval(p[pp.iCentroid]),
                                   gSkewAmp2->Eval(p[pp.iCentroid]),
                                   gSkew2->Eval(p[pp.iCentroid]),
                                   gStep->Eval(p[pp.iCentroid])});
                             }
                             else {
                               fPeaks[peakKey]->SetParameters({p[pp.iAmplitude],
                                   p[pp.iCentroid],
                                   p[pp.iWidth],
                                   p[pp.iSkewAmplitude],
                                   p[pp.iSkewWidth],
                                   p[pp.iSkewAmplitude2],
                                   p[pp.iSkewWidth2],
                                   p[pp.iStepAmplitude]});
                             }
                             break;
                           }
                           }
          
                           ret += fPeaks[peakKey]->GetFunc()->Eval(x[0]);
                         }
                         return ret;        
                       }, fLow, fHigh, iParamCount);

      for (auto & mPeak : fPeaks) {
        auto peakKey = mPeak.first;
        auto peak = mPeak.second;
        auto func = peak->GetFunc();
        auto pp = fPeakParamInds[peakKey];
        switch(fPeakType) {      
        case GamR::TK::Gaussian: {
          double low;
          double high;
          func->GetParLimits(0,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iAmplitude, low, high);
          }
          func->GetParLimits(1,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iCentroid, low, high);
          }
          func->GetParLimits(2,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iWidth, low, high);
          }
          break;
        }
        case GamR::TK::StepGaussian: {
          double low;
          double high;
          func->GetParLimits(0,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iAmplitude, low, high);
          }
          func->GetParLimits(1,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iCentroid, low, high);
          }
          if (!parameters.iFixWidthsFile) {
            func->GetParLimits(2,low,high);
            if (low!=high) {
              fTotal->SetParLimits(pp.iWidth, low, high);
            }
            func->GetParLimits(3,low,high);
            if (low!=high) {
              fTotal->SetParLimits(pp.iStepAmplitude, low, high);
            }
          }
          break;
        }
        case GamR::TK::OneTailGaussian: {
          double low;
          double high;
          func->GetParLimits(0,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iAmplitude, low, high);
          }
          func->GetParLimits(1,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iCentroid, low, high);
          }
          if (!parameters.iFixWidthsFile) {
          func->GetParLimits(2,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iWidth, low, high);
          }
          func->GetParLimits(3,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewAmplitude, low, high);
          }
          func->GetParLimits(4,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewWidth, low, high);
          }
          }
          break;
        }
        case GamR::TK::TwoTailGaussian: {
          double low;
          double high;
          func->GetParLimits(0,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iAmplitude, low, high);
          }
          func->GetParLimits(1,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iCentroid, low, high);
          }
          if (!parameters.iFixWidthsFile) {
          func->GetParLimits(2,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iWidth, low, high);
          }
          func->GetParLimits(3,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewAmplitude, low, high);
          }
          func->GetParLimits(4,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewWidth, low, high);
          }
          func->GetParLimits(5,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewAmplitude2, low, high);
          }
          func->GetParLimits(6,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewWidth2, low, high);
          }
          }
          break;
        }
        case GamR::TK::OneTailStepGaussian: {
          double low;
          double high;
          func->GetParLimits(0,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iAmplitude, low, high);
          }
          func->GetParLimits(1,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iCentroid, low, high);
          }
          if (!parameters.iFixWidthsFile) {
          func->GetParLimits(2,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iWidth, low, high);
          }
          func->GetParLimits(3,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewAmplitude, low, high);
          }
          func->GetParLimits(4,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewWidth, low, high);
          }
          func->GetParLimits(5,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iStepAmplitude, low, high);
          }
          }
          break;
        }
        case GamR::TK::TwoTailStepGaussian: {
          double low;
          double high;
          func->GetParLimits(0,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iAmplitude, low, high);
          }
          func->GetParLimits(1,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iCentroid, low, high);
          }
          if (!parameters.iFixWidthsFile) {
          func->GetParLimits(2,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iWidth, low, high);
          }
          func->GetParLimits(3,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewAmplitude, low, high);
          }
          func->GetParLimits(4,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewWidth, low, high);
          }
          func->GetParLimits(5,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewAmplitude2, low, high);
          }
          func->GetParLimits(6,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iSkewWidth2, low, high);
          }
          func->GetParLimits(7,low,high);
          if (low!=high) {
            fTotal->SetParLimits(pp.iStepAmplitude, low, high);
          }
          }
          break;
        }
        }
      }

      fNPars = fTotal->GetNpar();
    }

    TF1 *PeakFit::GetPeakBG(std::string peakKey) {
      TF1 *PeakBG = new TF1("PeakBG", [&](double *x, double *p){ return (FindPeak((int)p[0]))->GetFunc()->Eval(x[0]) + fBackground->Eval(x[0]);}, fLow, fHigh, 1);
      int i=0;
      for (auto &peak : fPeaks) {
        auto key = peak.first;
        if (key==peakKey) {
          PeakBG->SetParameter(0, i);
          break;
        }
        ++i;
      }
      return PeakBG;
    }

    TF1 *PeakFit::GetPeakGaussBG(std::string peakKey) {
      if (FindPeak(0)->GetGaussFunc() == NULL) { return NULL; }
      TF1 *GaussPeakBG = new TF1("GaussPeakBG", [&](double *x, double *p){ return (FindPeak((int)p[0]))->GetGaussFunc()->Eval(x[0]) + fBackground->Eval(x[0]);}, fLow, fHigh, 1);
      int i=0;
      for (auto &peak : fPeaks) {
        auto key = peak.first;
        if (key==peakKey) {
          GaussPeakBG->SetParameter(0, i);
          break;
        }
        ++i;
      }
      return GaussPeakBG;
    }
    
    TF1 *PeakFit::GetPeakStepBG(std::string peakKey) {
      if (FindPeak(0)->GetStepFunc() == NULL) { return NULL; }
      TF1 *PeakStepBG = new TF1("PeakStepBG", [&](double *x, double *p){ return (FindPeak((int)p[0]))->GetStepFunc()->Eval(x[0]) + fBackground->Eval(x[0]);}, fLow, fHigh, 1);
      int i=0;
      for (auto &peak : fPeaks) {
        auto key = peak.first;
        if (key==peakKey) {
          PeakStepBG->SetParameter(0, i);
          break;
        }
        ++i;
      }
      return PeakStepBG;
    }

    void PeakFit::ToText(std::string filename, std::string delimiter, int nPoints) {
      std::ofstream outfile(filename);

      std::vector<TF1*> peaks;

      for (int i=0; i<GetNPeaks(); ++i) {
        peaks.push_back(GetPeakBG(i));
      }
      
      for (int i=0; i<nPoints; ++i) {
        double x = fLow + (fHigh-fLow)*(double)(i)/(double)(nPoints-1);
        outfile << x << delimiter << fTotal->Eval(x) << delimiter;
        outfile << fBackground->Eval(x) << delimiter;
        for (int j=0; j<GetNPeaks(); ++j) {
          outfile << peaks[j]->Eval(x) << delimiter;
        }
        outfile << std::endl;
      }

      outfile.close();      
    }

    TF1 *FitGaussians(TH1 *hist, double Low, double High, std::vector<double> Peaks, Option_t *foption /*=""*/,
                      Option_t *option /*=""*/) {
      auto retval = FitPeaks(hist, Low, High, Peaks, foption, option);
      TF1 *out = retval->GetTotal();
      return out;
    }

    TF1 *FitGaussians(TCanvas *canvas /*= gPad->GetCanvas()*/, Option_t *foption /*= ""*/, Option_t *option /*= ""*/) {
      auto retval = FitPeaks(canvas, foption, option);
      TF1 *out = retval->GetTotal();
      return out;
    }

    TSpectrum *FindPeaks(TCanvas *canvas /* = gPad->GetCanvas()*/,
                         double sigma /* = 2*/,
                         Option_t *option /*=""*/,
                         double threshold /* = 0.05*/) {
      TH1* hist = GamR::Utils::GetHist1D(canvas);

      TSpectrum *spectrum = new TSpectrum();
      spectrum->Search(hist, sigma, option, threshold);

      //eliminate old labels
      while (true) {
        TText *text = (TText*)hist->GetListOfFunctions()->FindObject("PeakLabel");
        if (text) {
          hist->GetListOfFunctions()->Remove(text);
          delete text;
        }
        else {
          break;
        }
      }

      for (int i=0; i<spectrum->GetNPeaks(); ++i) {
        double x = spectrum->GetPositionX()[i];
        double y = spectrum->GetPositionY()[i];
        char t[100];
        sprintf(t,"%.1f", x);
        TText *text = new TText(x, y, t);
        text->SetName("PeakLabel");
        text->SetTextAngle(90);
        text->SetTextSize(0.025);
        hist->GetListOfFunctions()->Add(text);
      }
      spectrum->Print();
      hist->Draw(option);
      return spectrum;
    }

    // TSpectrum *FindPeaks(TCanvas *canvas /* = gPad->GetCanvas()*/,
    //                      double sigma /* = 2*/,
    //                      Option_t *option /*=""*/,
    //                      double threshold /* = 0.05*/) {
    //   TH1 *hist = GamR::Utils::GetHist1D(canvas);
      
    //   const int nBins = hist->GetNbinsX();

    //   double in_hist[nBins];
    //   double out_hist[nBins];

    //   for (int i=0; i<nBins; ++i) {
    //     in_hist[i] = hist->GetBinContent(i+1);
    //   }

    //   TSpectrum *spectrum = new TSpectrum();
    //   spectrum->SearchHighRes(&in_hist[0], &out_hist[0], nBins, sigma, threshold*100, true, 3, true, 3);

    //   while (true) {
    //     TText *text = (TText*)hist->GetListOfFunctions()->FindObject("PeakLabel");
    //     if (text) {
    //       hist->GetListOfFunctions()->Remove(text);
    //       delete text;
    //     }
    //     else {
    //       break;
    //     }
    //   }
    //   TPolyMarker *marks = new TPolyMarker();
    //   for (int i=0; i<spectrum->GetNPeaks(); ++i) {
    //     double x = spectrum->GetPositionX()[i];
    //     int bin = 1 + Int_t(x + 0.5);
    //     double le = hist->GetBinLowEdge(bin);
    //     double he = hist->GetBinLowEdge(bin+1);
    //     double frac = x - floor(x);
    //     x = le + frac*(he-le);
        
    //     double y = hist->GetBinContent(bin);
    //     marks->SetNextPoint(x, y);
    //     char t[100];
    //     sprintf(t,"%.1f", x);
    //     TText *text = new TText(x, y, t);
    //     text->SetName("PeakLabel");
    //     text->SetTextAngle(90);
    //     text->SetTextSize(0.025);
    //     hist->GetListOfFunctions()->Add(text);
    //   }

    //   hist->GetListOfFunctions()->Add(marks);
    //   marks->SetMarkerStyle(23);
    //   marks->SetMarkerColor(kRed);
    //   marks->SetMarkerSize(1.3);
    //   hist->Draw(option);
    //   return spectrum;
    // }
      
  } /* namespace Spect */
} /* namespace GamR */
