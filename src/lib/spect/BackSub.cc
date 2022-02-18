#include <TBox.h>
#include <TMarker.h>

#include <utils/Utilities.hh>

#include <spect/BackSub.hh>

namespace GamR {
  namespace Spect {
    int BackSub2D::SetPeak(TCanvas *canvas) {
      TMarker *marker = new TMarker();
      TObject *obj;

      int ex=-2;

      canvas->SetCrosshair();
      
      canvas->Update();

      double lowX = 0;
      double lowY = 0;
      double highX = 0;
      double highY = 0;

      std::string canvasname = canvas->GetName();

      std::string functioncall = "GamR::Utils::GetClick("+canvasname+")";
      
      canvas->AddExec("ex", functioncall.c_str());
      std::cout << "Click for corner 1, press any key to exit..." << std::endl;
      while (true){
        obj=canvas->WaitPrimitive();
        if (!obj) break;
        if (strncmp(obj->ClassName(),"TMarker",7)==0) {
          marker=(TMarker*)obj;
          if (ex==-2){
            lowX = marker->GetX();
            lowY = marker->GetY();
            // this->Low=marker->GetX();
            ex = ex + 1;
            std::cout << "Click for corner 2, press any key to exit..." << std::endl;
          } else {
            highX = marker->GetX();
            highY = marker->GetY();
            // this->High=marker->GetX();
            delete marker;
            ex = ex + 1;
            break;
          }
          delete marker;
        }
      }

      if (highX < lowX) {
        double temp = highX;
        highX = lowX;
        lowX = temp;
      }

      if (highY < lowY) {
        double temp = highY;
        highY = lowY;
        lowY = temp;
      }

      TBox *box = new TBox(lowX, lowY, highX, highY);
      box->SetLineColor(kRed);
      box->SetFillStyle(0);
      box->SetLineStyle(1);
      box->SetLineWidth(2);
      box->Draw("same");
      
      //make gates
      GamR::TK::Gate x(lowX, highX);
      GamR::TK::Gate y(lowY, highY);
      fPeakX = x;
      fPeakY = y;
      
      canvas->DeleteExec("ex");

      if (ex < 0) { // quit prematurely
        std::cout << "gating cancelled" << std::endl;
        canvas->SetCrosshair(0);
        return ex;
      } else {
        canvas->SetCrosshair(0);
        //std::cout << *this << std::endl;
        return ex;
      }

    }

    int BackSub2D::AddBackX(TCanvas *canvas) {
      TMarker *marker = new TMarker();
      TObject *obj;

      int ex=-2;

      canvas->SetCrosshair();
      
      canvas->Update();

      double lowX = 0;
      double lowY = 0;
      double highX = 0;
      double highY = 0;

      std::string canvasname = canvas->GetName();

      std::string functioncall = "GamR::Utils::GetClick("+canvasname+")";
      
      canvas->AddExec("ex", functioncall.c_str());
      std::cout << "Click for corner 1, press any key to exit..." << std::endl;
      while (true){
        obj=canvas->WaitPrimitive();
        if (!obj) break;
        if (strncmp(obj->ClassName(),"TMarker",7)==0) {
          marker=(TMarker*)obj;
          if (ex==-2){
            lowX = marker->GetX();
            lowY = marker->GetY();
            // this->Low=marker->GetX();
            ex = ex + 1;
            std::cout << "Click for corner 2, press any key to exit..." << std::endl;
          } else {
            highX = marker->GetX();
            highY = marker->GetY();
            // this->High=marker->GetX();
            delete marker;
            ex = ex + 1;
            break;
          }
          delete marker;
        }
      }

      if (highX < lowX) {
        double temp = highX;
        highX = lowX;
        lowX = temp;
      }

      if (highY < lowY) {
        double temp = highY;
        highY = lowY;
        lowY = temp;
      }
      
      canvas->DeleteExec("ex");

      if (ex < 0) { // quit prematurely
        std::cout << "gating cancelled" << std::endl;
        canvas->SetCrosshair(0);
        return ex;
      } else {
        canvas->SetCrosshair(0);
        //std::cout << *this << std::endl;
        //make gates
        GamR::TK::Gate x(lowX, highX);
        //GamR::TK::Gate y(lowY, highY);
        fBackX.push_back(x);
        //fPeakY = y;

        TBox *box = new TBox(lowX, fPeakY.GetLow(), highX, fPeakY.GetHigh());
        box->SetLineColor(kBlue);
        box->SetFillStyle(0);
        box->SetLineStyle(1);
        box->SetLineWidth(2);
        box->Draw("same");
        return ex;
      }

    }

    int BackSub2D::AddBackY(TCanvas *canvas) {
      TMarker *marker = new TMarker();
      TObject *obj;

      int ex=-2;

      canvas->SetCrosshair();
      
      canvas->Update();

      double lowX = 0;
      double lowY = 0;
      double highX = 0;
      double highY = 0;

      std::string canvasname = canvas->GetName();

      std::string functioncall = "GamR::Utils::GetClick("+canvasname+")";
      
      canvas->AddExec("ex", functioncall.c_str());
      std::cout << "Click for corner 1, press any key to exit..." << std::endl;
      while (true){
        obj=canvas->WaitPrimitive();
        if (!obj) break;
        if (strncmp(obj->ClassName(),"TMarker",7)==0) {
          marker=(TMarker*)obj;
          if (ex==-2){
            lowX = marker->GetX();
            lowY = marker->GetY();
            // this->Low=marker->GetX();
            ex = ex + 1;
            std::cout << "Click for corner 2, press any key to exit..." << std::endl;
          } else {
            highX = marker->GetX();
            highY = marker->GetY();
            // this->High=marker->GetX();
            delete marker;
            ex = ex + 1;
            break;
          }
          delete marker;
        }
      }

      if (highX < lowX) {
        double temp = highX;
        highX = lowX;
        lowX = temp;
      }

      if (highY < lowY) {
        double temp = highY;
        highY = lowY;
        lowY = temp;
      }
      
      canvas->DeleteExec("ex");

      if (ex < 0) { // quit prematurely
        std::cout << "gating cancelled" << std::endl;
        canvas->SetCrosshair(0);
        return ex;
      } else {
        canvas->SetCrosshair(0);
        //std::cout << *this << std::endl;
        //make gates
        //GamR::TK::Gate x(lowX, highX);
        GamR::TK::Gate y(lowY, highY);
        fBackY.push_back(y);
        //fBackY.push_back(y);

        TBox *box = new TBox(fPeakX.GetLow(), lowY, fPeakX.GetHigh(), highY);
        box->SetLineColor(kGreen);
        box->SetFillStyle(0);
        box->SetLineStyle(1);
        box->SetLineWidth(2);
        box->Draw("same");
        
        return ex;
      }

    }

    int BackSub2D::AddBackDiag(TCanvas *canvas) {
      TMarker *marker = new TMarker();
      TObject *obj;

      int ex=-2;

      canvas->SetCrosshair();
      
      canvas->Update();

      double lowX = 0;
      double lowY = 0;
      double highX = 0;
      double highY = 0;

      std::string canvasname = canvas->GetName();

      std::string functioncall = "GamR::Utils::GetClick("+canvasname+")";
      
      canvas->AddExec("ex", functioncall.c_str());
      std::cout << "Click for corner 1, press any key to exit..." << std::endl;
      while (true){
        obj=canvas->WaitPrimitive();
        if (!obj) break;
        if (strncmp(obj->ClassName(),"TMarker",7)==0) {
          marker=(TMarker*)obj;
          if (ex==-2){
            lowX = marker->GetX();
            lowY = marker->GetY();
            // this->Low=marker->GetX();
            ex = ex + 1;
            std::cout << "Click for corner 2, press any key to exit..." << std::endl;
          } else {
            highX = marker->GetX();
            highY = marker->GetY();
            // this->High=marker->GetX();
            delete marker;
            ex = ex + 1;
            break;
          }
          delete marker;
        }
      }

      if (highX < lowX) {
        double temp = highX;
        highX = lowX;
        lowX = temp;
      }

      if (highY < lowY) {
        double temp = highY;
        highY = lowY;
        lowY = temp;
      }
      
      
      canvas->DeleteExec("ex");

      if (ex < 0) { // quit prematurely
        std::cout << "gating cancelled" << std::endl;
        canvas->SetCrosshair(0);
        return ex;
      } else {
        canvas->SetCrosshair(0);
        //std::cout << *this << std::endl;
        //make gates
        GamR::TK::Gate x(lowX, highX);
        GamR::TK::Gate y(lowY, highY);
        fBackDiagX.push_back(x);
        fBackDiagY.push_back(y);

        TBox *box = new TBox(lowX, lowY, highX, highY);
        box->SetLineColor(kMagenta);
        box->SetFillStyle(0);
        box->SetLineStyle(1);
        box->SetLineWidth(2);
        box->Draw("same");
        
        return ex;
      }
    }

    int BackSub2D::AddBackBack(TCanvas *canvas) {
      TMarker *marker = new TMarker();
      TObject *obj;

      int ex=-2;

      canvas->SetCrosshair();
      
      canvas->Update();

      double lowX = 0;
      double lowY = 0;
      double highX = 0;
      double highY = 0;

      std::string canvasname = canvas->GetName();

      std::string functioncall = "GamR::Utils::GetClick("+canvasname+")";
      
      canvas->AddExec("ex", functioncall.c_str());
      std::cout << "Click for corner 1, press any key to exit..." << std::endl;
      while (true){
        obj=canvas->WaitPrimitive();
        if (!obj) break;
        if (strncmp(obj->ClassName(),"TMarker",7)==0) {
          marker=(TMarker*)obj;
          if (ex==-2){
            lowX = marker->GetX();
            lowY = marker->GetY();
            // this->Low=marker->GetX();
            ex = ex + 1;
            std::cout << "Click for corner 2, press any key to exit..." << std::endl;
          } else {
            highX = marker->GetX();
            highY = marker->GetY();
            // this->High=marker->GetX();
            delete marker;
            ex = ex + 1;
            break;
          }
          delete marker;
        }
      }

      if (highX < lowX) {
        double temp = highX;
        highX = lowX;
        lowX = temp;
      }

      if (highY < lowY) {
        double temp = highY;
        highY = lowY;
        lowY = temp;
      }
      
      canvas->DeleteExec("ex");

      if (ex < 0) { // quit prematurely
        std::cout << "gating cancelled" << std::endl;
        canvas->SetCrosshair(0);
        return ex;
      } else {
        canvas->SetCrosshair(0);
        //std::cout << *this << std::endl;
        //make gates
        GamR::TK::Gate x(lowX, highX);
        GamR::TK::Gate y(lowY, highY);
        fBackBackX.push_back(x);
        fBackBackY.push_back(y);

        TBox *box = new TBox(lowX, lowY, highX, highY);
        box->SetLineColor(kOrange);
        box->SetFillStyle(0);
        box->SetLineStyle(1);
        box->SetLineWidth(2);
        box->Draw("same");
        return ex;
      }
    }

    TH2D * BackSub2D::Subtract(TH2D *hist) {
      int startBinX = hist->GetXaxis()->FindBin(fPeakX.GetLow());
      int startBinY = hist->GetYaxis()->FindBin(fPeakY.GetLow());

      int stopBinX = hist->GetXaxis()->FindBin(fPeakX.GetHigh());
      int stopBinY = hist->GetYaxis()->FindBin(fPeakY.GetHigh());

      subtracted = new TH2D("sub_hist", "subtracted histogram",
                                  stopBinX - startBinX + 1,
                                  hist->GetXaxis()->GetBinLowEdge(startBinX),
                                  hist->GetXaxis()->GetBinLowEdge(stopBinX+1),
                                  stopBinY - startBinY + 1,
                                  hist->GetYaxis()->GetBinLowEdge(startBinY),
                                  hist->GetYaxis()->GetBinLowEdge(stopBinY+1));

      unsubtracted = new TH2D("unsub_hist", "unsubtracted histogram",
                              stopBinX - startBinX + 1,
                              hist->GetXaxis()->GetBinLowEdge(startBinX),
                              hist->GetXaxis()->GetBinLowEdge(stopBinX+1),
                              stopBinY - startBinY + 1,
                              hist->GetYaxis()->GetBinLowEdge(startBinY),
                              hist->GetYaxis()->GetBinLowEdge(stopBinY+1));
                                  
      for (int i=startBinX; i<=stopBinX; ++i) {
        for (int j=startBinY; j<=stopBinY; ++j) {
          subtracted->SetBinContent(i-startBinX+1, j-startBinY+1, hist->GetBinContent(i, j));
          subtracted->SetBinError(i-startBinX+1, j-startBinY+1, hist->GetBinError(i, j));

          unsubtracted->SetBinContent(i-startBinX+1, j-startBinY+1, hist->GetBinContent(i, j));
          unsubtracted->SetBinError(i-startBinX+1, j-startBinY+1, hist->GetBinError(i, j));
        }
      }
      
      int nBinsY = 0;
      y_sub = new TH1D("y_sub", "Y subtraction",
                       stopBinX - startBinX + 1,
                       hist->GetXaxis()->GetBinLowEdge(startBinX),
                       hist->GetXaxis()->GetBinLowEdge(stopBinX+1));

      for (auto &gate : fBackY) {
        int start = hist->GetYaxis()->FindBin(gate.GetLow());
        int stop = hist->GetYaxis()->FindBin(gate.GetHigh());

        for (int j=start; j<=stop; ++j) {
          nBinsY += 1;
          for (int i=startBinX; i<=stopBinX; ++i) {
            y_sub->SetBinContent(i-startBinX+1,
                                 y_sub->GetBinContent(i-startBinX+1) + hist->GetBinContent(i, j));
            y_sub->SetBinError(i-startBinX+1,
                               std::sqrt(std::pow(y_sub->GetBinError(i-startBinX+1), 2) +
                                         std::pow(hist->GetBinError(i,j), 2)));
          }
        }
      }

      int nBinsX = 0;
      x_sub = new TH1D("x_sub", "X subtraction",
                       stopBinY - startBinY + 1,
                       hist->GetYaxis()->GetBinLowEdge(startBinY),
                       hist->GetYaxis()->GetBinLowEdge(stopBinY+1));

      for (auto &gate : fBackX) {
        int start = hist->GetXaxis()->FindBin(gate.GetLow());
        int stop = hist->GetXaxis()->FindBin(gate.GetHigh());

        for (int i=start; i<=stop; ++i) {
          nBinsX += 1;
          for (int j=startBinY; j<=stopBinY; ++j) {
            x_sub->SetBinContent(j-startBinY+1,
                                 x_sub->GetBinContent(j-startBinY+1) + hist->GetBinContent(i, j));
            x_sub->SetBinError(j-startBinY+1,
                               std::sqrt(std::pow(x_sub->GetBinError(j-startBinY+1), 2) +
                                         std::pow(hist->GetBinError(i,j), 2)));
          }
        }
      }

      //background-background
      int nBinsBackground = 0;

      double backback = 0;
      double backback_err = 0;
      
      for (int k=0; k<fBackBackX.size(); ++k) {
        auto gateX = fBackBackX[k];
        auto gateY = fBackBackY[k];

        int startX = hist->GetXaxis()->FindBin(gateX.GetLow());
        int stopX = hist->GetXaxis()->FindBin(gateX.GetHigh());
        int startY = hist->GetYaxis()->FindBin(gateY.GetLow());
        int stopY = hist->GetYaxis()->FindBin(gateY.GetHigh());

        for (int i=startX; i<=stopX; ++i) {
          for (int j=startY; j<=stopY; ++j) {
            nBinsBackground += 1;
            backback += hist->GetBinContent(i, j);
            backback_err = std::sqrt(std::pow(backback_err, 2) +
                                     std::pow(hist->GetBinError(i, j), 2));
          }
        }
      }

      if (nBinsBackground > 0) {
        backback = backback/(double)nBinsBackground;
        backback_err = backback_err/(double)nBinsBackground;
      }

      std::vector<int> nBinsSlice(stopBinX + stopBinY - startBinX - startBinY + 1);
      std::vector<double> sumSlice(stopBinX + stopBinY - startBinX - startBinY + 1);
      std::vector<double> sumErrSlice(stopBinX + stopBinY - startBinX - startBinY + 1);

      int startSum = startBinX + startBinY;
      int stopSum = stopBinX + stopBinY;
      
      //diagonal bits
      for (int k=0; k<fBackDiagX.size(); ++k) {
        auto gateX = fBackDiagX[k];
        auto gateY = fBackDiagY[k];

        int startX = hist->GetXaxis()->FindBin(gateX.GetLow());
        int stopX = hist->GetXaxis()->FindBin(gateX.GetHigh());
        int startY = hist->GetYaxis()->FindBin(gateY.GetLow());
        int stopY = hist->GetYaxis()->FindBin(gateY.GetHigh());
        
        //go through each diagonal (constant sum) slice
        for (int s=startSum; s<=stopSum; ++s) {
          for (int i=startX; i<=stopX; ++i) {
            int j = s - i; //so that i+j = sum
            if (j >= startY && j <= stopY) {
              nBinsSlice[s-startSum] += 1;
              sumSlice[s-startSum] += hist->GetBinContent(i, j);
              sumErrSlice[s-startSum] = std::sqrt(std::pow(sumErrSlice[s-startSum], 2) +
                                                  std::pow(hist->GetBinError(i, j), 2));
            }
          }         
        }
      }

      for (int k = 0; k<nBinsSlice.size(); ++k) {
        if (nBinsSlice[k] > 0) {
          sumSlice[k] = sumSlice[k]/(double)nBinsSlice[k];
          sumErrSlice[k] = sumErrSlice[k]/(double)nBinsSlice[k];
        }
      }

      int peakWidthY = stopBinY - startBinY + 1;
      int peakWidthX = stopBinX - startBinX + 1;

      if (nBinsX > 0) {
        x_sub->Scale((double)1.0/(double)nBinsX);
      }
      if (nBinsY > 0) {
        y_sub->Scale((double)1.0/(double)nBinsY);
      }

      for (int i=1; i<=peakWidthX; ++i) {
        for (int j=1; j<=peakWidthY; ++j) {
          double counts = subtracted->GetBinContent(i, j);
          double error = subtracted->GetBinError(i, j);

          if (nBinsSlice[i+j-2]>0) {
            subtracted->SetBinContent(i, j, counts - x_sub->GetBinContent(j) - y_sub->GetBinContent(i) - sumSlice[i+j-2] + 2.0*backback);
            subtracted->SetBinError(i, j, std::sqrt(std::pow(error, 2) +
                                                    std::pow(x_sub->GetBinError(j), 2) +
                                                    std::pow(y_sub->GetBinError(i), 2) +
                                                    std::pow(sumErrSlice[i+j-2], 2) + 
                                                    std::pow(2.0*backback_err, 2)));
          }
          else {
            subtracted->SetBinContent(i, j, counts - x_sub->GetBinContent(j) - y_sub->GetBinContent(i) + backback);
            subtracted->SetBinError(i, j, std::sqrt(std::pow(error, 2) +
                                                    std::pow(x_sub->GetBinError(j), 2) +
                                                    std::pow(y_sub->GetBinError(i), 2) +
                                                    std::pow(backback_err, 2)));
          }
        }
      }      
      return subtracted;      
    }

    double BackSub2D::GetPeakCounts() {
      double sum = 0;
      for (int i=1; i<=subtracted->GetNbinsX(); ++i) {
        for (int j=1; j<=subtracted->GetNbinsY(); ++j) {
          sum += subtracted->GetBinContent(i,j);
        }
      }
      return sum;
    }

    double BackSub2D::GetPeakCountsError() {
      double err = 0;
      for (int i=1; i<=subtracted->GetNbinsX(); ++i) {
        for (int j=1; j<=subtracted->GetNbinsY(); ++j) {
          err += std::pow(subtracted->GetBinError(i,j), 2);
        }
      }
      return std::sqrt(err);
    }

    BackSub2D::BackSub2D(TH2D *hist) {
      TCanvas *c1 = new TCanvas();

      hist->Draw("colz2");

      SetPeak(c1);

      while (true) {
        std::cout << "Select area(s) for X subtraction" << std::endl;
        int retval = AddBackX(c1);
        if (retval < 0) { break; }
      }
      while (true) {
        std::cout << "Select area(s) for Y subtraction" << std::endl;
        int retval = AddBackY(c1);
        if (retval < 0) { break; }
      }
      while (true) {
        std::cout << "Select area(s) for background-background region" << std::endl;
        int retval = AddBackBack(c1);
        if (retval < 0) { break; }
      }
      while (true) {
        std::cout << "Select area(s) for diagonal subtraction" << std::endl;
        int retval = AddBackDiag(c1);
        if (retval < 0) { break; }
      }
      Subtract(hist);

      std::cout << std::endl;
      std::cout << "Peak Area: " << GetPeakCounts() << "   +/-   " << GetPeakCountsError() << std::endl;
      return;
    }
      
      
  }
}
