#include <iostream>

#include <utils/Utilities.hh>
#include <spect/Calibrate.hh>
#include <spect/Transform.hh>

#include <TSpectrum.h>
#include <TMarker.h>

namespace GamR {
  namespace Spect {
    std::pair<double, double> TwoPointCalibrate(TVirtualPad *canvas, double sigma) {
      if (!canvas) { if (gPad) { canvas = gPad->GetCanvas(); } else { return {-1,-1}; } }
      TMarker *marker = new TMarker();
      TObject *obj;
      TSpectrum *spect = new TSpectrum();
      TH1D *hist = GamR::Utils::GetHist1D(canvas);
      double range = 10*sigma*hist->GetBinWidth(1);
      if (range < 100*hist->GetBinWidth(1)) {
        range = 100*hist->GetBinWidth(1);
      }

      int ex=-2;

      canvas->SetCrosshair();
      
      canvas->Update();

      double low = -1;
      double high = -1;

      std::string canvasname = canvas->GetName();

      std::string functioncall = "GamR::Utils::GetClick("+canvasname+")";

      double lowPos = -1;                  
      double highPos = -1;
      double lowEn;
      double highEn;
      
      canvas->AddExec("ex", functioncall.c_str());
      std::cout << "Click for lower peak" << std::endl;
      while (true){
        obj=canvas->WaitPrimitive();
        if (!obj) break;
        if (strncmp(obj->ClassName(),"TMarker",7)==0) {
          marker=(TMarker*)obj;
          if (ex==-2){
            low = marker->GetX();
            ex = ex + 1;

            hist->GetXaxis()->SetRangeUser(low-range,low+range);
            int nPeaks = spect->Search(hist,sigma);
            double closest = 1e9;
            for (int i=0; i<nPeaks; ++i) {
              double posX = spect->GetPositionX()[i];
              double dist = std::abs(posX-low);
              if (dist < closest) {
                closest = dist;
                lowPos = posX;
              }
            }            
            canvas->Update();

            std::cout << "Peak estimate: " << lowPos << std::endl;
            std::cout << "Peak energy: ";
            std::cin >> lowEn;

            std::cout << "Click for upper peak..." << std::endl;
          } else {
            high = marker->GetX();

            hist->GetXaxis()->SetRangeUser(high-range,high+range);
            int nPeaks = spect->Search(hist, sigma);
            double closest = 1e9;

            for (int i=0; i<nPeaks; ++i) {
              double posX = spect->GetPositionX()[i];
              double dist = std::abs(posX-high);
              if (dist < closest) {
                closest = dist;
                highPos = posX;
              }
            }           
            canvas->Update();

            std::cout << "Peak estimate: " << highPos << std::endl;
            std::cout << "Peak energy: ";
            std::cin >> highEn;
            
            delete marker;
            ex = ex + 1;
            break;
          }
          delete marker;
        }
      }
      
      canvas->DeleteExec("ex");
      
      if (ex < 0) { // quit prematurely
        std::cout << "calibration cancelled" << std::endl;
        canvas->SetCrosshair(0);
        return std::pair<double,double>(-1,-1);
      } else {
        canvas->SetCrosshair(0);
        double gradient = (highEn-lowEn)/(highPos-lowPos);
        double offset = lowEn - lowPos*gradient;

        std::string answer;
        while (true) {
          std::cout << "Gain = " << gradient << "     Offset = " << offset << std::endl;
          std::cout << "Apply calibration? [y/n]:";
                       std::cin >> answer;
          if (answer == "y") {
            GamR::Spect::ScaleLabelsLinear(hist, gradient, offset);
            break;
          }
          else if (answer == "n") {
            break;
          }
        }
        return std::pair<double,double>(gradient,offset);
      }

    }

    std::pair<double, double> TwoPointCalibrate(TH1 *hist, double lowEst, double highEst, double lowEn, double highEn, double sigma) {
      TSpectrum *spect = new TSpectrum();
      double range = 10*sigma;
    
      hist->GetXaxis()->SetRangeUser(lowEst-range,lowEst+range);
      int nPeaks = spect->Search(hist,sigma,"",0.1);
      double closest = 1e9;
      double lowPos = 0;
      for (int i=0; i<nPeaks; ++i) {
        double posX = spect->GetPositionX()[i];
        double dist = std::abs(posX-lowEst);
        if (dist < closest) {
          closest = dist;
          lowPos = posX;
        }
      }

      hist->GetXaxis()->SetRangeUser(highEst-range,highEst+range);
      nPeaks = spect->Search(hist,sigma,"",0.1);
      double highPos = 0;
      closest = 1e9;
      for (int i=0; i<nPeaks; ++i) {
        double posX = spect->GetPositionX()[i];
        double dist = std::abs(posX-highEst);
        if (dist < closest) {
          closest = dist;
          highPos = posX;
        }
      }
      double gradient = (highEn-lowEn)/(highPos-lowPos);
      double offset = lowEn - lowPos*gradient;

      return std::pair<double,double>(gradient,offset);    
    }
  }
}
  
