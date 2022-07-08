#include <iostream>
#include <string.h>

/* ROOT */
#include <TMarker.h>
#include <TH1.h>
#include <TMath.h>
#include <TArrow.h>
#include <TText.h>
#include <TString.h>

#include <utils/Utilities.hh>
#include <nucleus/Transition.hh>
#include "Integral.hh"

namespace GamR{
  namespace Spect{
    std::pair<double, double> Integral(TH1 *hist, GamR::TK::Gate peak) {
      double peakArea = peak.GetIntegral((TH1D*)hist);
      double peakAreaError = peak.GetIntegralError((TH1D*)hist);
      std::cout << "             Peak Area          Error" << std::endl;
      printf("%21.4f %15.4f\n", peakArea, peakAreaError);
      std::pair<double, double> area = std::pair<double, double>(peakArea, peakAreaError);
      return area;
    }
      
    std::pair<double, double> Integral(TH1 *hist, double peakLow, double peakHigh) {
      GamR::TK::Gate gate(peakLow, peakHigh);
      return Integral(hist, gate);
    }

    std::pair<double, double> Integral(TCanvas *canvas /*= gPad->GetCanvas()*/) {
      TH1D *hist = GamR::Utils::GetHist1D(canvas);
      if (!hist) { return std::pair<int, int>(-1, -1); }
      GamR::TK::Gate gate;
      gate.SetGate(canvas);
      return Integral(hist, gate);
    }

    std::pair<double, double> IntegralBS(TH1 *hist, GamR::Nucleus::Transition transition) {
      double peakArea = transition.Apply((TH1D*)hist);
      double peakAreaError = transition.ApplyError((TH1D*)hist);
      std::cout << "             Peak Area          Error" << std::endl;
      printf("%21.4f %15.4f\n", peakArea, peakAreaError);
      std::pair<double, double> area = std::pair<double, double>(peakArea, peakAreaError);
      return area;
    }

    std::pair<double, double> IntegralBS(TH1 *hist, GamR::TK::Gate peak, GamR::TK::Gate background) {
      GamR::Nucleus::Transition transition(0, peak.GetLow(), peak.GetHigh(), background.GetLow(), background.GetHigh());
      return IntegralBS(hist, transition);
    }
    
    std::pair<double, double> IntegralBS(TH1 *hist, double peakLow, double peakHigh, double backLow, double backHigh) {
      GamR::Nucleus::Transition transition(0, peakLow, peakHigh, backLow, backHigh);
      return IntegralBS(hist, transition);
    }   
    
    std::pair<double, double> IntegralBS(TCanvas *canvas/*=gPad->GetCanvas()*/)
    {
      TH1D *hist = GamR::Utils::GetHist1D(canvas);
      if (!hist) { return std::pair<int, int>(-1, -1); }
      GamR::Nucleus::Transition transition;
      transition.SetTransition();
      return IntegralBS(hist, transition);      
    }


    std::pair<double, double> Counts(TH1 *hist, GamR::TK::Gate peak) {
      double peakArea = peak.GetCounts((TH1D*)hist);
      double peakAreaError = peak.GetCountsError((TH1D*)hist);
      std::cout << "             Peak Area          Error" << std::endl;
      printf("%21.4f %15.4f\n", peakArea, peakAreaError);
      std::pair<double, double> area = std::pair<double, double>(peakArea, peakAreaError);
      return area;
    }
      
    std::pair<double, double> Counts(TH1 *hist, double peakLow, double peakHigh) {
      GamR::TK::Gate gate(peakLow, peakHigh);
      return Counts(hist, gate);
    }

    std::pair<double, double> Counts(TCanvas *canvas /*= gPad->GetCanvas()*/) {
      TH1D *hist = GamR::Utils::GetHist1D(canvas);
      if (!hist) { return std::pair<int, int>(-1, -1); }
      GamR::TK::Gate gate;
      gate.SetGate(canvas);
      return Counts(hist, gate);
    }

    std::pair<double, double> CountsBS(TH1 *hist, GamR::Nucleus::Transition transition) {
      double peakArea = transition.ApplyCounts((TH1D*)hist);
      double peakAreaError = transition.ApplyCountsError((TH1D*)hist);
      std::cout << "             Peak Counts        Error" << std::endl;
      printf("%21.4f %15.4f\n", peakArea, peakAreaError);
      std::pair<double, double> peak = std::pair<double, double>(peakArea, peakAreaError);
      return peak;
    }

    std::pair<double, double> CountsBS(TH1 *hist, GamR::TK::Gate peak, GamR::TK::Gate background) {
      GamR::Nucleus::Transition transition(0, peak.GetLow(), peak.GetHigh(), background.GetLow(), background.GetHigh());
      return CountsBS(hist, transition);
    }

    std::pair<double, double> CountsBS(TH1 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate> backgrounds) {
      GamR::Nucleus::Transition transition(0, peak.GetLow(), peak.GetHigh(), backgrounds[0].GetLow(), backgrounds[0].GetHigh());
      for (int i=1; i<backgrounds.size(); ++i) {
        transition.AddBackground(backgrounds[i].GetLow(), backgrounds[i].GetHigh());
      }
      return CountsBS(hist, transition);
    }
    
    std::pair<double, double> CountsBS(TH1 *hist, double peakLow, double peakHigh, double backLow, double backHigh) {
      GamR::Nucleus::Transition transition(0, peakLow, peakHigh, backLow, backHigh);
      return CountsBS(hist, transition);
    }   
    
    std::pair<double, double> CountsBS(TCanvas *canvas/*=gPad->GetCanvas()*/)
    {
      TH1D *hist = GamR::Utils::GetHist1D(canvas);
      if (!hist) { return std::pair<int, int>(-1, -1); }
      GamR::Nucleus::Transition transition;
      transition.SetTransition();
      return CountsBS(hist, transition);      
    }
  }
}

      
