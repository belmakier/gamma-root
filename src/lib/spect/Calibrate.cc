#include <iostream>

#include <utils/Utilities.hh>
#include <spect/Calibrate.hh>
#include <spect/Transform.hh>

#include <TSystem.h>
#include <TSpectrum.h>
#include <TMarker.h>
#include <TLine.h>

namespace GamR {
  namespace Spect {
    std::pair<double, double> TwoClickCalibrate(TVirtualPad *canvas) {
      if (!canvas) { if (gPad) { canvas = gPad->GetCanvas(); } else { return {-1,-1}; } }
      TMarker *marker = new TMarker();
      TObject *obj;
      TH1D *hist = GamR::Utils::GetHist1D(canvas);

      int ex=-2;

      canvas->SetCrosshair();
      
      canvas->Update();

      double lowx = -1;
      double highx = -1;

      std::string canvasname = canvas->GetName();

      GamR::Utils::Clicker click;
      canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "GamR::Utils::Clicker", &click, "GetClick(Int_t,Int_t,Int_t,TObject*)");

      double lowy = -1;                  
      double highy = -1;

      TGraph *line = new TGraph();
      line->SetLineColor(kRed);
      line->SetMarkerStyle(kFullCircle);
      line->SetMarkerColor(kRed);
      line->Draw("same LP");
      //canvas->AddExec("ex", functioncall.c_str());
      std::cout << "Click for first point" << std::endl;
      while (true){
        canvas->Modified();
        canvas->Update();
        obj=canvas->WaitPrimitive();
        if (!obj) break;
        if (strncmp(obj->ClassName(),"TMarker",7)==0) {
          marker=(TMarker*)obj;
          if (ex==-2){
            lowx = marker->GetX();
            lowy = marker->GetY();
            line->AddPoint(lowx,lowy);
            ex = ex + 1;
            canvas->Update();
            std::cout << "Click for second point" << std::endl;
          } else {
            highx = marker->GetX();
            highy = marker->GetY();
            line->AddPoint(highx,highy);
            canvas->Update();
            canvas->Modified();

            delete marker;
            ex = ex + 1;
            break;
          }
          delete marker;
        }
      }
      canvas->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", &click, "GetClick(Int_t,Int_t,Int_t,TObject*)");
      canvas->SetCrosshair(0);
      canvas->Modified();
      canvas->Update();
      gSystem->ProcessEvents();
      canvas->Modified();
      canvas->Update();
      
      if (ex < 0) { // quit prematurely
        std::cout << "calibration cancelled" << std::endl;
        canvas->SetCrosshair(0);
        line->Delete();
        return std::pair<double,double>(-1,-1);
      } else {
        canvas->SetCrosshair(0);
        double gradient = (highy-lowy)/(highx-lowx);
        double offset = lowy - lowx*gradient;

        return std::pair<double,double>(gradient,offset);
      }

    }

    std::pair<double, double> TwoPointCalibrate(TVirtualPad *canvas, double sigma) {
      if (!canvas) { if (gPad) { canvas = gPad->GetCanvas(); } else { return {-1,-1}; } }
      TMarker *marker = new TMarker();
      TObject *obj;
      TSpectrum *spect = new TSpectrum();
      TH1D *hist = GamR::Utils::GetHist1D(canvas);
      double startlow = canvas->GetUxmin();
      double starthigh = canvas->GetUxmax();;      
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

      GamR::Utils::Clicker click;
      canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "GamR::Utils::Clicker", &click, "GetClick(Int_t,Int_t,Int_t,TObject*)");

      double lowPos = -1;                  
      double highPos = -1;
      double lowEn;
      double highEn;

      TLine *line_low;
      TLine *line_high;
      //canvas->AddExec("ex", functioncall.c_str());
      std::cout << "Click for lower peak" << std::endl;
      while (true){
        canvas->Modified();
        canvas->Update();
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
                line_low = new TLine(lowPos, canvas->GetUymin(), lowPos, canvas->GetUymax());
                line_low->SetLineColor(kRed);
                line_low->SetLineWidth(2);
                line_low->Draw();
              }
            }            
            hist->GetXaxis()->SetRangeUser(startlow, starthigh);            
            canvas->Update();

            std::cout << "Peak estimate: " << lowPos << std::endl;

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
                line_high = new TLine(highPos, canvas->GetUymin(), highPos, canvas->GetUymax());
                line_high->SetLineColor(kRed);
                line_high->SetLineWidth(2);
                line_high->Draw();
              }
            }
            hist->GetXaxis()->SetRangeUser(startlow, starthigh);
            canvas->Update();
            canvas->Modified();

            std::cout << "Peak estimate: " << highPos << std::endl;
            
            delete marker;
            ex = ex + 1;
            break;
          }
          delete marker;
        }
      }
      canvas->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", &click, "GetClick(Int_t,Int_t,Int_t,TObject*)");
      canvas->SetCrosshair(0);
      line_low->Draw();
      line_high->Draw();
      canvas->Modified();
      canvas->Update();
      gSystem->ProcessEvents();
      canvas->Modified();
      canvas->Update();

      std::cout << "Low peak energy: ";
      std::cin >> lowEn;
      std::cout << "High peak energy: ";
      std::cin >> highEn;
      
      if (ex < 0) { // quit prematurely
        std::cout << "calibration cancelled" << std::endl;
        canvas->SetCrosshair(0);
        line_low->Delete();
        line_high->Delete();
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
        line_low->Delete();
        line_high->Delete();
        return std::pair<double,double>(gradient,offset);
      }

    }
    
    std::pair<double, double> TwoPointCalibrate(TVirtualPad *canvas, double lowEn, double highEn, double sigma) {
      if (!canvas) { if (gPad) { canvas = gPad->GetCanvas(); } else { return {-1,-1}; } }
      TMarker *marker = new TMarker();
      TObject *obj;
      TSpectrum *spect = new TSpectrum();
      TH1D *hist = GamR::Utils::GetHist1D(canvas);
      canvas->Update();
      double startlow = canvas->GetUxmin();
      double starthigh = canvas->GetUxmax();
      std::cout << startlow << "   " << starthigh << std::endl;
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

      //std::string functioncall = "GamR::Utils::GetClick("+canvasname+")";
      GamR::Utils::Clicker click;
      canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "GamR::Utils::Clicker", &click, "GetClick(Int_t,Int_t,Int_t,TObject*)");

      double lowPos = -1;                  
      double highPos = -1;

      TLine *line_low;
      TLine *line_high;
      //canvas->AddExec("ex", functioncall.c_str());
      std::cout << "Click for lower peak" << std::endl;
      while (true){
        canvas->Modified();
        canvas->Update();
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
                line_low = new TLine(lowPos, canvas->GetUymin(), lowPos, canvas->GetUymax());
                line_low->SetLineColor(kRed);
                line_low->SetLineWidth(2);
                line_low->Draw();
              }
            }            
            hist->GetXaxis()->SetRangeUser(startlow, starthigh);            
            canvas->Update();

            std::cout << "Peak estimate: " << lowPos << std::endl;

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
                line_high = new TLine(highPos, canvas->GetUymin(), highPos, canvas->GetUymax());
                line_high->SetLineColor(kRed);
                line_high->SetLineWidth(2);
                line_high->Draw();
              }
            }
            hist->GetXaxis()->SetRangeUser(startlow, starthigh);
            canvas->Update();
            canvas->Modified();

            std::cout << "Peak estimate: " << highPos << std::endl;
            
            delete marker;
            ex = ex + 1;
            break;
          }
          delete marker;
        }
      }
      canvas->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", &click, "GetClick(Int_t,Int_t,Int_t,TObject*)");
      canvas->SetCrosshair(0);
      line_low->Draw();
      line_high->Draw();
      canvas->Modified();
      canvas->Update();
      gSystem->ProcessEvents();
      canvas->Modified();
      canvas->Update();
      
      if (ex < 0) { // quit prematurely
        std::cout << "calibration cancelled" << std::endl;
        canvas->SetCrosshair(0);
        line_low->Delete();
        line_high->Delete();
        return std::pair<double,double>(-1,-1);
      } else {
        canvas->SetCrosshair(0);
        double gradient = (highEn-lowEn)/(highPos-lowPos);
        double offset = lowEn - lowPos*gradient;

        line_low->Delete();
        line_high->Delete();
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
  
