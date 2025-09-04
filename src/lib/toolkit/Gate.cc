/**
   @file
   @author Tim Gray <timothy.gray.edu.au>
   @author Aqeel Akber
   @section DESCRIPTION

   Tools relating to a Gate object that contains upper and lower bounds

*/

/* STD */
#include <iostream>

/* ROOT */
#include <Buttons.h>
#include <TAttFill.h>
#include <TAttLine.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMarker.h>
#include <TNamed.h>
#include <TParameter.h>
#include <TROOT.h>
#include <TMath.h>
#include <TVirtualX.h>
#include <TQObject.h>

/* GAMMA */
#include <utils/Utilities.hh>
#include "Gate.hh"

/* apparently we have to do this explicitly for every type */
/// \cond CLASSIMP
// ClassImp(GamR::TK::Gate<Double_t>) ClassImp(GamR::TK::Gate<Float_t>)
// ClassImp(GamR::TK::Gate<Int_t>)

// ClassImp(GamR::TK::GateMap<Double_t>)
// ClassImp(GamR::TK::GateMap<Float_t>)
// ClassImp(GamR::TK::GateMap<Int_t>)
/// \endcond

// This was supposed to work according to the root documentation!
// AND ALSO THE CODE /usr/include/root/Rtypes.h
// templateClassImp(GamR::TK::Gate);

namespace GamR {
  namespace TK {
    Gate::Gate(const char *name) : TNamed(name, name)
    {
      SetLineColor(8); SetFillStyle(3003); SetFillColor(8); 
    }
    
    Gate::Gate(const char *name, const char *title) : TNamed(name, title)
    {
      SetLineColor(8); SetFillStyle(3003); SetFillColor(8);
    }

    Gate::Gate(const char *name, TVirtualPad *canvas, Option_t *opt) : TNamed(name, name)
    {
      SetLineColor(8); SetFillStyle(3003); SetFillColor(8);
      this->SetGate(canvas, opt);
    }

    Gate::Gate(const char *name, const char *title, TVirtualPad *canvas, Option_t *opt) : TNamed(name, title)
    {
      SetLineColor(8); SetFillStyle(3003); SetFillColor(8);
      this->SetGate(canvas, opt);
    }
    
    Gate::Gate(TVirtualPad *canvas, Option_t *opt)
    {
      SetLineColor(8); SetFillStyle(3003); SetFillColor(8);
      this->SetGate(canvas, opt);
    }

    int Gate::SetGate()
    {      
      return this->SetGate(gPad->GetCanvas());
    }
    /**
       Set gate bounds by mouse click.
       
       @param canvas Pointer to a canvas cointaining some coordinate system. Not tested for anything other than a single histogram.
       @return Return value < 0 means a failure of some kind, otherwise the gate values have been set successfully
    */
    int Gate::SetGate(TVirtualPad *canvas, Option_t *opt)
    {
      TString sOpt(opt);
      sOpt.ToLower();      
      
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

      //std::string functioncall = "GamR::Utils::GetClick("+canvasname+")";
      
      //canvas->AddExec("ex", functioncall.c_str());
      GamR::Utils::Clicker click;
      canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "GamR::Utils::Clicker", &click, "GetClick(Int_t,Int_t,Int_t,TObject*)");

      std::cout << "Click for lower bound of region, press any key to exit..." << std::endl;
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
            std::cout << "Click for upper bound of region, press any key to exit..." << std::endl;
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
      // set gate values
      if (sOpt.Contains("x")) {
        this->Low = lowX;
        this->High = highX;
      }
      else if (sOpt.Contains("y")) {
        this->Low = lowY;
        this->High = highY;
      }
      else {
        if ((highX - lowX) / (canvas->GetUxmax() - canvas->GetUxmin()) >=
            (highY - lowY) / (canvas->GetUymax() - canvas->GetUymin())) {
          this->Low = lowX;
          this->High = highX;
        } else {
          this->Low = lowY;
          this->High = highY;
        }
      }

      canvas->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", &click, "GetClick(Int_t,Int_t,Int_t,TObject*)");
      //canvas->DeleteExec("ex");

      if (ex < 0) { // quit prematurely
        std::cout << "gating cancelled" << std::endl;
        canvas->SetCrosshair(0);
        return ex;
      } else {
        canvas->SetCrosshair(0);
        Valid();
        std::cout << *this << std::endl;        
        return ex;
      }
    }

    /**
     * @brief
     *
     * @param[in] Meas Templated argument, the measurement number of the TDetector
     * object passed.
     * @param[in] det The TDetector in question, template type should
     * be automatically deduced by this argument.
     * @param[in] calibrated Use detectors calibrated measurement.
     * @param[in] id If positive, match ID number.
     * @return Whether the detectors measurement sits within this gate.
     */
    template <size_t Meas, class TDetector>
    Bool_t PassDetector(TDetector det, Bool_t calibrated, Int_t id)
    {
      if (id >= 0 && id != det.ID) {
        return kFALSE;
      } else if (calibrated) {
        return Pass(det.template GetCal<Meas>());
      } else {
        return Pass(det.template Get<Meas>());
      }
    }

    /**
       Applies the gate to a TH2 histogram in the Y direction, projecting onto the
       X-axis.  Appends "_gx" to the input histogram name for the name of the
       output histogram.

       @param hist Input histogram
       @return X-Projection from between the gate bounds
    */
    TH1D *Gate::ApplyY(TH2 *hist) const
    {
      TH1D *hOut;
      TString name;
      name.Form("%s_gx", hist->GetName());
      double xmax = -1;
      double xmin = -1;
      if (gPad) {
        xmax = gPad->GetUxmax();
        xmin = gPad->GetUxmin();
      }
      hist->GetXaxis()->UnZoom();
      hOut = hist->ProjectionX(name.Data(), hist->GetYaxis()->FindBin(this->Low), hist->GetYaxis()->FindBin(this->High));
      if (gPad)
        hist->GetXaxis()->SetRangeUser(xmin, xmax);
      return hOut;
    }

    /**
       Applies the gate to a TH2 histogram in the Y direction, projecting onto the
       X-axis.

       @param hist Input histogram
       @param name Name of the returned histogram
       @return X-Projection from between the gate bounds
    */
    TH1D *Gate::ApplyY(TH2 *hist, const char *name) const
    {
      TH1D *hOut;
      double xmax = -1;
      double xmin = -1;
      if (gPad) {
        xmax = gPad->GetUxmax();
        xmin = gPad->GetUxmin();
      }
      hist->GetXaxis()->UnZoom();
      hOut = hist->ProjectionX(name, hist->GetYaxis()->FindBin(this->Low), hist->GetYaxis()->FindBin(this->High));
      if (gPad)
        hist->GetXaxis()->SetRangeUser(xmin, xmax);
      return hOut;
    }

    /**
       Applies the gate to a TH2 histogram in the X direction, projecting onto the
       Y-axis.  Appends "_gy" to the input histogram name for the name of the
       output histogram.

       @param hist Input histogram
       @return Y-Projection from between the gate bounds
    */
    TH1D *Gate::ApplyX(TH2 *hist) const
    {
      TH1D *hOut;
      TString name;
      name.Form("%s_gy", hist->GetName());
      double ymax = -1;
      double ymin = -1;
      if (gPad) {
        ymax = gPad->GetUymax();
        ymin = gPad->GetUymin();
      }
      hist->GetYaxis()->UnZoom();
      hOut = hist->ProjectionY(name.Data(), hist->GetXaxis()->FindBin(this->Low), hist->GetXaxis()->FindBin(this->High));
      if (gPad)
        hist->GetYaxis()->SetRangeUser(ymin, ymax);
      return hOut;
    }

    /**
       Applies the gate to a TH2 histogram in the X direction, projecting onto the
       Y-axis.

       @param hist Input histogram
       @param name Name of the returned histogram
       @return Y-Projection from between the gate bounds
    */
    TH1D *Gate::ApplyX(TH2 *hist, const char *name) const
    {
      TH1D *hOut;
      double ymin = -1;
      double ymax = -1;
      if (gPad) {
        ymax = gPad->GetUymax();
        ymin = gPad->GetUymin();
      }
      hist->GetYaxis()->UnZoom();
      hOut = hist->ProjectionY(name, hist->GetXaxis()->FindBin(this->Low), hist->GetXaxis()->FindBin(this->High));
      if (gPad)
        hist->GetYaxis()->SetRangeUser(ymin, ymax);
      return hOut;
    }

    /**
       Finds the total area within the gate bounds (inclusive)

       @param hist 1D histogram to act on
       @return The total histogram area falling between the bounds of the gate
    */
    double Gate::GetIntegral(TH1 *hist) const
    {
      int iLowBin = hist->FindBin(this->Low);
      int iHighBin = hist->FindBin(this->High);

      double integral = 0;

      for (int i = iLowBin; i <= iHighBin; i++) {
        integral = integral + hist->GetBinContent(i) * hist->GetBinWidth(i);
      }

      return integral;
    }

    double Gate::GetIntegral(TH1 *hist, std::vector<Gate> back) const
    {
      int nData    = 0;
      double sumX  = 0;
      double sumY  = 0;
      double sumX2 = 0;
      double sumXY = 0;
      double sumY2 = 0;

      int startGate = GetBinLow(hist);
      int stopGate = GetBinHigh(hist);

      for (auto &backgate : back) {
        int startback = backgate.GetBinLow(hist);
        int stopback = backgate.GetBinHigh(hist);
        for (int i=startback; i<=stopback; ++i) {
          nData++;
          sumX += hist->GetBinCenter(i);
          sumX2 += hist->GetBinCenter(i)*hist->GetBinCenter(i);
          sumXY += hist->GetBinCenter(i)*hist->GetBinContent(i);
          sumY += hist->GetBinContent(i);
          sumY2 += hist->GetBinContent(i)*hist->GetBinContent(i);
        }
      }
      
      double slope = (nData*sumXY - sumX*sumY)/(nData*sumX2-sumX*sumX);

      double constant = (sumY*sumX2 - sumX*sumXY)/(nData*sumX2 - sumX*sumX);

      double sumBackground = 0;
      sumX = 0;
      sumY = 0;
      sumX2 = 0;
      sumY2 = 0;
      sumXY = 0;
      for ( int i=startGate; i<= stopGate; ++i) {
        double background = constant + slope*hist->GetBinCenter(i);
        sumBackground += background;
        double Y = hist->GetBinContent(i) - background;
        sumY += Y;
        sumXY += hist->GetBinCenter(i)*Y;
      }

      double posX = sumXY/sumY;
      double area = (double)sumY;
      double dArea = std::sqrt(area + 2*sumBackground);

      return area;
    }

    /**
       Finds the difference between the areas contained by the gate bounds and the background gate bounds (scaled appropriately)

       @param hist 1D histogram to act on
       @param background background Gates
       @return The total peak area
    */
    double Gate::GetIntegral(TH1 *hist, Gate background) const
    {
      double peak = 0;
      double back = 0;
      peak = GetIntegral(hist);
      back = background.GetIntegral(hist);
      return peak - back*(double)GetBinWidth(hist)/(double)background.GetBinWidth(hist);
    }

    double Gate::GetIntegral(TH1 *hist, Gate backLow, Gate backHigh) const
    {
      int nData    = 0;
      double sumX  = 0;
      double sumY  = 0;
      double sumX2 = 0;
      double sumXY = 0;
      double sumY2 = 0;

      int startLow = backLow.GetBinLow(hist);
      int stopLow = backLow.GetBinHigh(hist);
      int startHigh = backHigh.GetBinLow(hist);
      int stopHigh = backHigh.GetBinHigh(hist);

      int startGate = GetBinLow(hist);
      int stopGate = GetBinHigh(hist);

      for (int i=startLow; i<=stopLow; ++i) {
        nData++;
        sumX += hist->GetBinCenter(i);
        sumX2 += hist->GetBinCenter(i)*hist->GetBinCenter(i);
        sumXY += hist->GetBinCenter(i)*hist->GetBinContent(i);
        sumY += hist->GetBinContent(i);
        sumY2 += hist->GetBinContent(i)*hist->GetBinContent(i);
      }
      for (int i=startHigh; i<=stopHigh; ++i) {
        nData++;
        sumX += hist->GetBinCenter(i);
        sumX2 += hist->GetBinCenter(i)*hist->GetBinCenter(i);
        sumXY += hist->GetBinCenter(i)*hist->GetBinContent(i);
        sumY += hist->GetBinContent(i);
        sumY2 += hist->GetBinContent(i)*hist->GetBinContent(i);
      }
      double slope = (nData*sumXY - sumX*sumY)/(nData*sumX2-sumX*sumX);
      double constant = (sumY*sumX2 - sumX*sumXY)/(nData*sumX2 - sumX*sumX);

      double sumBackground = 0;
      sumX = 0;
      sumY = 0;
      sumX2 = 0;
      sumY2 = 0;
      sumXY = 0;
      for ( int i=startGate; i<= stopGate; ++i) {
        double background = constant + slope*hist->GetBinCenter(i);
        sumBackground += background;
        double Y = hist->GetBinContent(i) - background;
        sumY += Y;
        sumXY += hist->GetBinCenter(i)*Y;
      }

      double posX = sumXY/sumY;
      double area = (double)sumY;
      double dArea = std::sqrt(area + 2*sumBackground);

      //std::cout << "centroid: " << posX << std::endl;
      return area;
    }
    
    /**
       Finds the error in the area within the gate bounds
       (inclusive).  Sums the errors of the histogram channels in quadrature.

       @param hist 1D histogram to act on
       @return The total error in the area falling between the bounds of the gate
    */
    double Gate::GetIntegralError(TH1 *hist) const
    {
      int iLowBin = hist->FindBin(this->Low);
      int iHighBin = hist->FindBin(this->High);

      double integralerror = 0;

      for (int i = iLowBin; i <= iHighBin; i++) {
        integralerror = integralerror + pow(hist->GetBinError(i) * hist->GetBinWidth(i), 2);
      }

      return sqrt(integralerror);
    }

    double Gate::GetIntegralError(TH1 *hist, Gate background) const
    {
      double peak = 0;
      double back = 0;
      peak = GetIntegralError(hist);
      back = background.GetIntegralError(hist);
      return sqrt(pow(peak,2) + pow(back*(double)GetBinWidth(hist)/(double)background.GetBinWidth(hist), 2));
    }

    double Gate::GetIntegralError(TH1 *hist, std::vector<Gate> back) const
    {
      int nData    = 0;
      double sumX  = 0;
      double sumY  = 0;
      double sumX2 = 0;
      double sumXY = 0;
      double sumY2 = 0;

      int startGate = GetBinLow(hist);
      int stopGate = GetBinHigh(hist);

      double backwidth = 0;

      for (auto &backgate : back) {
	backwidth += (backgate.GetHigh()-backgate.GetLow());
	int startback = backgate.GetBinLow(hist);
	int stopback = backgate.GetBinHigh(hist);
	for (int i=startback; i<=stopback; ++i) {
	  nData++;
	  sumX += hist->GetBinCenter(i);
	  sumX2 += hist->GetBinCenter(i)*hist->GetBinCenter(i);
	  sumXY += hist->GetBinCenter(i)*hist->GetBinContent(i);
	  sumY += hist->GetBinContent(i);
	  sumY2 += hist->GetBinContent(i)*hist->GetBinContent(i);
	}
      }
      
      double slope = (nData*sumXY - sumX*sumY)/(nData*sumX2-sumX*sumX);
      double constant = (sumY*sumX2 - sumX*sumXY)/(nData*sumX2 - sumX*sumX);

      double sumBackground = 0;
      sumX = 0;
      sumY = 0;
      sumX2 = 0;
      sumY2 = 0;
      sumXY = 0;
      double peakwidth = (this->GetHigh() - this->GetLow());
      for ( int i=startGate; i<= stopGate; ++i) {
        double background = constant + slope*hist->GetBinCenter(i);
        sumBackground += background;
        double Y = hist->GetBinContent(i) - background;
        sumY += Y;
        sumXY += hist->GetBinCenter(i)*Y;
      }

      double posX = sumXY/sumY;
      double area = (double)sumY;
      double dArea = std::sqrt(area + std::pow(peakwidth/backwidth,2)*sumBackground);

      //std::cout << "centroid: " << posX << std::endl;
      return dArea;
    }


    /**
       Finds the total counts within the gate bounds (inclusive)

       @param hist 1D histogram to act on
       @return The total counts falling between the bounds of the gate
    */
    double Gate::GetCounts(TH1 *hist) const
    {
      int iLowBin = hist->FindBin(this->Low);
      int iHighBin = hist->FindBin(this->High);

      double integral = 0;

      for (int i = iLowBin; i <= iHighBin; i++) {
        integral = integral + hist->GetBinContent(i);
      }
      
      return integral;
    }

    /**
       Finds the difference between the counts contained by the gate bounds and the background gate bounds (scaled appropriately)

       @param hist 1D histogram to act on
       @param background background Gate
       @return The total peak counts
    */
    double Gate::GetCounts(TH1 *hist, Gate background) const
    {
      double peak = 0;
      double back = 0;
      peak = GetCounts(hist);
      back = background.GetCounts(hist);
      return peak - back*(double)GetBinWidth(hist)/(double)background.GetBinWidth(hist);
    }

    double Gate::GetCounts(TH1 *hist, std::vector<Gate> background) const
    {
      double peak = 0;
      double back = 0;
      peak = GetCounts(hist);
      double back_width = 0;
      for (auto &backgate : background) {
        back += backgate.GetCounts(hist);
        back_width += backgate.GetBinWidth(hist);
      }
      //std::cout << "peak: " << peak << "    back: " << back << "    scale: " << (double)GetBinWidth(hist)/back_width << std::endl;
      return peak - back*(double)GetBinWidth(hist)/back_width;

      /*
      int nData    = 0;
      double sumX  = 0;
      double sumY  = 0;
      double sumX2 = 0;
      double sumXY = 0;
      double sumY2 = 0;

      int startGate = GetBinLow(hist);
      int stopGate = GetBinHigh(hist);

      for (auto &backgate : background) {
        int startback = backgate.GetBinLow(hist);
        int stopback = backgate.GetBinHigh(hist);
        for (int i=startback; i<=stopback; ++i) {
          nData++;
          sumX += double(i);
          sumX2 += double(i)*double(i);
          sumXY += double(i)*hist->GetBinContent(i);
          sumY += hist->GetBinContent(i);
          sumY2 += hist->GetBinContent(i)*hist->GetBinContent(i);
        }
      }

      
      double slope = (nData*sumXY - sumX*sumY)/(nData*sumX2-sumX*sumX);
      double constant = (sumY*sumX2 - sumX*sumXY)/(nData*sumX2 - sumX*sumX);

      double sumBackground = 0;
      sumX = 0;
      sumY = 0;
      sumX2 = 0;
      sumY2 = 0;
      sumXY = 0;
      for ( int i=startGate; i<= stopGate; ++i) {
        double background = constant + slope*double(i);
        sumBackground += background;
        double Y = hist->GetBinContent(i) - background;
        sumY += Y;
        sumXY += double(i)*Y;
      }

      double posX = sumXY/sumY;
      double counts = (double)sumY;
      double dCounts = std::sqrt(counts + 2*sumBackground);

      //std::cout << "centroid: " << posX << std::endl;
      return counts;
      */
    }
    
    /**
       Finds the error in the counts within the gate bounds
       (inclusive).  Sums the errors of the histogram channels in quadrature.

       @param hist 1D histogram to act on
       @return The total error in the counts falling between the bounds of the gate
    */
    double Gate::GetCountsError(TH1 *hist) const
    {
      int iLowBin = hist->FindBin(this->Low);
      int iHighBin = hist->FindBin(this->High);

      double integralerror = 0;

      for (int i = iLowBin; i <= iHighBin; i++) {
        integralerror = integralerror + pow(hist->GetBinError(i), 2);
      }

      return sqrt(integralerror);
    }

    double Gate::GetCountsError(TH1 *hist, Gate background) const
    {
      double peak = 0;
      double back = 0;
      peak = GetCountsError(hist);
      back = background.GetCountsError(hist);
      return sqrt(pow(peak,2) + pow(back*(double)GetBinWidth(hist)/(double)background.GetBinWidth(hist), 2));
    }

    double Gate::GetCountsError(TH1 *hist, std::vector<Gate> background) const
    {
      double peak = 0;
      double back = 0;
      peak = GetCountsError(hist);
      double back_width = 0;
      for (auto &backgate : background) {
        back += backgate.GetCountsError(hist);
        back_width += backgate.GetBinWidth(hist);
      }
      //std::cout << "peak err: " << peak << "    back err: " << back << "    scale: " << (double)GetBinWidth(hist)/back_width << std::endl;
      return sqrt(pow(peak, 2) + pow(back*(double)GetBinWidth(hist)/back_width, 2));

      /*
      int nData    = 0;
      double sumX  = 0;
      double sumY  = 0;
      double sumX2 = 0;
      double sumXY = 0;
      double sumY2 = 0;

      int startGate = GetBinLow(hist);
      int stopGate = GetBinHigh(hist);

      int peakWidth = 0;
      peakWidth = stopGate-startGate+1;
      int backWidth = 0;
      for (auto &backgate : background) {
        int startback = backgate.GetBinLow(hist);
        int stopback = backgate.GetBinHigh(hist);
        backWidth += stopback - startback + 1;
        for (int i=startback; i<=stopback; ++i) {
          nData++;
          sumX += double(i);
          sumX2 += double(i)*double(i);
          sumXY += double(i)*hist->GetBinContent(i);
          sumY += hist->GetBinContent(i);
          sumY2 += hist->GetBinContent(i)*hist->GetBinContent(i);
        }
      }

      
      double slope = (nData*sumXY - sumX*sumY)/(nData*sumX2-sumX*sumX);
      double constant = (sumY*sumX2 - sumX*sumXY)/(nData*sumX2 - sumX*sumX);

      double sumBackground = 0;
      sumX = 0;
      sumY = 0;
      sumX2 = 0;
      sumY2 = 0;
      sumXY = 0;
      for ( int i=startGate; i<= stopGate; ++i) {
        double background = constant + slope*double(i);
        sumBackground += background;
        double Y = hist->GetBinContent(i) - background;
        sumY += Y;
        sumXY += double(i)*Y;
      }

      double posX = sumXY/sumY;
      double counts = (double)sumY;
      double dCounts = std::sqrt(counts + std::pow(double(peakWidth)/double(backWidth),2)*sumBackground);

      return dCounts;
      */
    }

    void Gate::Norm(TH1 *hist, TH1 *ref) {
      double scale = GetIntegral(ref)/GetIntegral(hist);
      hist->Scale(scale);
    }

    void Gate::NormBackSub(TH1 *hist, TH1 *ref, Gate background) {
      /*
      //this is very dumb: subtracts constant background from all histograms and then rescales
      double back_level = background.GetIntegral(hist)/(double)background.GetBinWidth(hist);
      std::cout << "hist = " << hist->GetName() << std::endl;
      std::cout << back_level << std::endl;
      for (int i=0; i<hist->GetNbinsX(); ++i) {
        hist->SetBinContent(i, hist->GetBinContent(i) - back_level);
      }
      double back_ref = background.GetIntegral(ref)/(double)background.GetBinWidth(hist);
      std::cout << back_ref << std::endl;
      for (int i=0; i<ref->GetNbinsX(); ++i) {
        ref->SetBinContent(i, ref->GetBinContent(i) - back_ref);
      }
      std::cout << GetIntegral(hist) << "   " << GetIntegral(ref) << std::endl;
      double scale = GetIntegral(ref)/GetIntegral(hist);
      hist->Scale(scale);
      */

      double scale = GetIntegral(ref, background)/GetIntegral(hist, background);
      hist->Scale(scale);
    }
    
    void Gate::Browse(TBrowser *b)
    {
      (void)b;
      Draw();
      ls();
    }

    void Gate::Paint(Option_t *option /*="same"*/)
    {
      TAttLine::Modify();
      TAttFill::Modify();

      //check if there's a histogram
      TH1D *hist = GamR::Utils::GetHist1D(gPad->GetCanvas());
      double x1[2];
      double y1[2];
      double x2[2];
      double y2[2];

      x1[0] = this->Low;
      x1[1] = this->Low;

      int logy = gPad->GetLogy();

      y1[0] = gPad->GetUymin();
      if (!hist) {        
        y1[1] = gPad->GetUymax();
      }
      else {
        y1[1] = hist->GetBinContent(hist->FindBin(this->Low));
        if (logy) {
          if (y1[1] > 0) y1[1] = TMath::Log10(y1[1]);
        }
        y1[1] = std::min(gPad->GetUymax(), y1[1]);
      }

      x2[0] = this->High;
      x2[1] = this->High;


      y2[0] = gPad->GetUymin();
      if (!hist) {
        y2[1] = gPad->GetUymax();
      }
      else {
        y2[1] = hist->GetBinContent(hist->FindBin(this->High));
        if (logy) {
          if (y2[1] > 0) y2[1] = TMath::Log10(y2[1]);
        }
        y2[1] = std::min(gPad->GetUymax(), y2[1]);
      }
      
      if (gPad->GetUxmin() <= x1[0] && x1[0] <= gPad->GetUxmax()) {
        if (y1[1] > y1[0]) { 
          gPad->PaintPolyLine(2, &x1[0], &y1[0], option);
        }
      }
      if (gPad->GetUxmin() <= x2[0] && x2[0] <= gPad->GetUxmax()) {
        if (y2[1] > y2[0]) { 
          gPad->PaintPolyLine(2, &x2[0], &y2[0], option);
        }
      }

      if (!hist) {
        gPad->PaintBox(x1[0], y1[0], x2[1], y2[1], option);
      }
      else {
        for (int i=hist->FindBin(this->Low); i<=hist->FindBin(this->High); ++i) {
          if (hist->GetBinCenter(i) < gPad->GetUxmin() || hist->GetBinCenter(i) > gPad->GetUxmax()) { continue; }
          x1[0] = std::max(this->Low, hist->GetBinLowEdge(i));
          x1[1] = x1[0];

          x2[0] = std::min(this->High, hist->GetBinLowEdge(i+1));
          x2[1] = x2[0];
          
          y1[1] = hist->GetBinContent(i);
          y2[1] = hist->GetBinContent(i);

          if (logy) {
            if (y1[1] > 0) y1[1] = TMath::Log10(y1[1]);
            if (y2[1] > 0) y2[1] = TMath::Log10(y2[1]);
          }

          y1[1] = std::min(gPad->GetUymax(), y1[1]);
          y2[1] = std::min(gPad->GetUymax(), y2[1]);

          if (y1[1] <= y1[0] || y2[1] <= y2[0]) { continue; }

          gPad->PaintBox(x1[0], y1[0], x2[1], y2[1], option);
        }
      }

    }

    Int_t Gate::DistancetoPrimitive(Int_t px, Int_t py)
    {
      (void)py;
      double lowDist = std::abs(gPad->XtoPixel(this->Low) - px);
      double highDist = std::abs(gPad->XtoPixel(this->High) - px);
      return fmin(lowDist, highDist);
    }

    void Gate::ExecuteEvent(Int_t event, Int_t px, Int_t py)
    {
      (void)py;
      if (!gPad)
        return;
      int kMaxDiff = 20;

      if (!gPad->IsEditable())
        return;

      switch (event) {
      case kMouseMotion:
        if (fmin(std::abs(px - gPad->XtoPixel(this->Low)), std::abs(px - gPad->XtoPixel(this->High))) < kMaxDiff) {
          gPad->SetCursor(kPointer);
          return;
        }
        break;
      }
    }

    void Gate::ls(Option_t *option /*=""*/) const
    {
      (void)option;
      printf("Name                Low         High\n");
      printf("%-20s%-12.2f%-12.2f\n", GetName(), (double)GetLow(), (double)GetHigh());
    }

    void GateMap::Browse(TBrowser *b)
    {
      TObject *obj;

      ls();

      if (b) {
        for (auto i = fMap.begin(); i != fMap.end(); ++i) {
          (i->second).SetName((i->first).c_str());
          obj = (TObject *)(&(i->second));
          b->Add(obj);
        }
      } else {
        TObject::Browse(b);
      }
    }

    void GateMap::ls(Option_t *option /*=""*/) const
    {
      (void)option;
      printf("Key                 Low         High\n");
      for (auto i = fMap.begin(); i != fMap.end(); ++i) {
        printf("%-20s%-12.2f%-12.2f\n", (i->first).c_str(), (double)(i->second).GetLow(), (double)(i->second).GetHigh());
      }
    }

    std::ostream &operator<<(std::ostream &os, Gate const &g)
    {
      os << "Low: " << g.GetLow() << " High: " << g.GetHigh();
      return os;
    }

  } /* namespace TK */
} /* namespace GamR */
