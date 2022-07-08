#include <TMatrixD.h>
#include <TGraphErrors.h>
#include <TMarker.h>
#include <HFitInterface.h>
#include <Math/WrappedMultiTF1.h>
#include <Fit/BinData.h>
#include <Fit/Fitter.h>

#include <spect/Cut.hh>
#include "Peak.hh"

namespace GamR {
  namespace TK {
    BPeak::BPeak() { linear = new TF1(); backlow = new TF1(); backhigh = new TF1(); };
    BPeak::~BPeak() { delete linear; delete backlow; delete backhigh; };
    
    void BPeak::Set(TH1 *hist, GamR::TK::Gate peak, TF1 *background) {
      int iStart = peak.GetBinLow(hist);
      int iStop = peak.GetBinHigh(hist);

      double sumX = 0;
      double sumXY = 0;
      double sumY2E2 = 0;
      double sumY = 0;
      double sumY2 = 0;
      double sumYerr = 0;
      int nData = 0;
      double max = 0;
      double sumBinErr = 0;
      double areaErr = 0;
      TH1D *h = new TH1D("h", "h", iStop-iStart+1, hist->GetBinLowEdge(iStart), hist->GetBinLowEdge(iStop)+hist->GetBinWidth(iStop));
      for (int i=iStart; i<=iStop; ++i) {
        double binWidth = hist->GetBinWidth(i);
        double binCent = hist->GetBinCenter(i);
        double binErr = hist->GetBinError(i);
        double backErr = 0;
        if (background->GetNpar() < 4) { //crude to suppress error message for now
          backErr = background->IntegralError(hist->GetBinLowEdge(i), hist->GetBinLowEdge(i)+binWidth)/binWidth;
        }
        binErr = std::sqrt(binErr*binErr + backErr*backErr);
        sumBinErr = std::sqrt(sumBinErr*sumBinErr + binErr*binErr);
        areaErr = std::sqrt(areaErr*areaErr + binErr*binErr*binWidth*binWidth);
        /*
        ++nData;
        double binCont = (hist->GetBinContent(i) - background->Eval(binCent))*binWidth;
*binWidth;
        double sigc = background->GetParError(0);
        double sigm = background->GetParError(1);

        std::cout << binErr << "     " << backErr << std::endl;
        binErr = std::sqrt(binErr*binErr + backErr*backErr);
        sumYerr = std::sqrt(sumYerr*sumYerr + binErr*binErr);
        sumX += binCent;
        sumY += binCont;
        sumY2 += binCont*binCont;
        sumXY += binCont*binCent;
        sumY2E2 += binCont*binCont*binErr*binErr;
        if (binCont/binWidth > max) { max = binCont/binWidth; }
        */
        h->SetBinContent(i-iStart+1, hist->GetBinContent(i)-background->Eval(binCent));
        h->SetBinError(i-iStart+1, binErr);
      }
      
      //double mean = sumXY/sumY;
      Cent = h->GetMean();
      //stddev/neff
      //double neff = sumY*sumY/sumY2;
      
      //CentError = std::sqrt(sumY2E2/(sumY*sumY));
      /*
      double sumYdiff2 = 0;
      double sumdiff2 = 0;
      for (int i=iStart; i<=iStop; ++i) {
        double binWidth = hist->GetBinWidth(i);
        double binCent = hist->GetBinCenter(i);
        double binCont = (hist->GetBinContent(i) - background->Eval(binCent))*binWidth;
        sumYdiff2 += binCont*std::pow(binCent - mean, 2);
        sumdiff2 += std::pow(binCent - mean, 2);
      }
      */

      //double stddev = std::sqrt(1.0/(iStop-iStart+1)*sumdiff2);
      CentError = h->GetMeanError();//stddev/neff;
      Width = 2.3548*h->GetStdDev();//2.3548*std::sqrt(sumY/(sumY*sumY - sumY2)*sumYdiff2);  //assuming something vaguely gaussian to get a FWHM here
      WidthError = 2.3548*h->GetStdDevError();
      Amp = h->GetMaximum();
      AmpError = h->GetBinError(h->GetMaximumBin());
      Area = h->Integral("width");
      AreaError = areaErr;
      Counts = h->Integral();
      CountsError = sumBinErr;

      h->Delete();
    }

    void BPeak::Set(TH1 *hist, double x1, double y1, double x2, double y2) {
      TGraph *graph = new TGraph();
      graph->SetPoint(0, x1, y1);
      graph->SetPoint(1, x2, y2);

      delete linear;
      linear = new TF1("linear", "[0]+[1]*x", x1, x2);
      double m = (y2-y1)/(x2-x1);
      double c = y2 - m*x2;

      linear->SetParameter(0, c);
      linear->SetParameter(1, m);
      graph->Fit(linear, "RQN");

      GamR::TK::Gate peak(x1, x2);
      mPeak = peak;
      
      Set(hist, peak, linear);

      linear->Draw("same");

      this->Draw("same");      
      
      graph->Delete();
    }
    
    void BPeak::Set(TH1 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background, Option_t *foption, Option_t *option) {
      //make TGraphErrors;
      if (background.size()==0) { std::cout << "Must have at least one background region" << std::endl; return; }

      TString opts(option);
      opts.ToLower();

      if (opts.Contains("s")) {
        SetCont(hist, peak, background, foption, option);
        return;
      }
      if (opts.Contains("p")) {
        SetPoint(hist, peak, background, foption, option);
        return;
      }
      if (opts.Contains("x")) {
        SetStep(hist, peak, background, foption, option);
        return;
      }
      
      SetCont(hist, peak, background, foption, option);
      return;
    }

    void BPeak::SetCont(TH1 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background, Option_t *foption, Option_t *option) {  //where a single continuous background should be fitted

      TString opts(option);
      opts.ToLower();
      if (opts.Contains("v")) {
        std::cout << "Setting peak with regions:" << std::endl;
        std::cout << peak.GetLow() << "   " << peak.GetHigh() << "   ";
        for (auto &b : background) {
          std::cout << b.GetLow() << "   " << b.GetHigh() << "  ";
        }
        std::cout << std::endl;
      }

      mPeak = peak;
      mBackgrounds = background;
      
      TGraphErrors *back = new TGraphErrors();
      double lowest=1e9;
      double highest=-1e9;
      for (int b=0; b<background.size(); ++b) {
        int iStart = background[b].GetBinLow(hist);
        int iStop = background[b].GetBinHigh(hist);
        double last_err = -1.0;
        for (int i=iStart; i<=iStop; ++i) {
          int nPoint = back->GetN();
          double x = hist->GetBinCenter(i);
          double y = hist->GetBinContent(i);
          if (hist->GetBinError(i) > 0.0) {
            back->SetPoint(nPoint, x, y);
            back->SetPointError(nPoint, 0, hist->GetBinError(i));
            last_err = hist->GetBinError(i);
          }
          else {
            //hacky and possibly statistically dubious?
            //necessary for cases with low counts where bins with no counts should be
            //taken into account
            if (last_err > 0.0) {
              back->SetPoint(nPoint, x, y);
              back->SetPointError(nPoint, 0, last_err);
            }
          }
          if (x < lowest) { lowest = x; }
          if (x > highest) {highest = x; }
        }
      }

      delete linear;

      if (opts.Contains("c")) {
        linear = new TF1("linear", "[0]", lowest, highest);
        double y1 = hist->GetBinContent(hist->FindBin(lowest));
        double y2 = hist->GetBinContent(hist->FindBin(highest));
        linear->SetParameter(0, (y1+y2)/2.0); 
      }
      else { //default behaviour
        linear = new TF1("linear", "[0]+[1]*x", lowest, highest);
        double x1 = hist->GetBinCenter(hist->FindBin(lowest));
        double x2 = hist->GetBinCenter(hist->FindBin(highest));
        double y1 = hist->GetBinContent(hist->FindBin(lowest));
        double y2 = hist->GetBinContent(hist->FindBin(highest));

        double w = x2 - x1;
      
        double m = (y2-y1)/(x2-x1);
        double c = y2 - m*x2;

        linear->SetParameter(0, c);
        linear->SetParameter(1, m);
      }
      
      back->Fit(linear, ("RQN"+(std::string)foption).c_str());

      Set(hist, peak, linear);

      linear->Draw("same");

      this->Draw("same");      
      
      back->Delete();
    }

    void BPeak::SetPoint(TH1 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background, Option_t *foption, Option_t *option) { //where upper and lower background regions are fitted and extrpolated to the boundaries of the peak area

      TString opts(option);
      opts.ToLower();
      if (opts.Contains("v")) {
        std::cout << "Setting peak with regions:" << std::endl;
        std::cout << peak.GetLow() << "   " << peak.GetHigh() << "   ";
        for (auto &b : background) {
          std::cout << b.GetLow() << "   " << b.GetHigh() << "  ";
        }
        std::cout << std::endl;
      }

      mPeak = peak;
      mBackgrounds = background;
      
      TGraphErrors *back_low = new TGraphErrors();
      TGraphErrors *back_high = new TGraphErrors();
      TGraphErrors *backs[2] = {back_low, back_high};
      int back_ind = -1;
      double lowest[2]={1e9, 1e9};
      double highest[2]={-1e9, -1e9};
      for (int b=0; b<background.size(); ++b) {
        float av_pos = (background[b].GetLow() + background[b].GetHigh())/2.0;
        if (av_pos < peak.GetLow()) { back_ind = 0;}
        else if (av_pos > peak.GetHigh()) { back_ind = 1; }
        else { std::cout << "Invalid background region, ignoring" << std::endl; continue; }

        int iStart = background[b].GetBinLow(hist);
        int iStop = background[b].GetBinHigh(hist);
        double last_err = -1.0;
        for (int i=iStart; i<=iStop; ++i) {
          int nPoint = backs[back_ind]->GetN();
          double x = hist->GetBinCenter(i);
          double y = hist->GetBinContent(i);
          if (hist->GetBinError(i) > 0.0) {
            backs[back_ind]->SetPoint(nPoint, x, y);
            backs[back_ind]->SetPointError(nPoint, 0, hist->GetBinError(i));
            last_err = hist->GetBinError(i);
          }
          else {
            //hacky and possibly statistically dubious?
            //necessary for cases with low counts where bins with no counts should be
            //taken into account
            if (last_err > 0.0) {
              backs[back_ind]->SetPoint(nPoint, x, y);
              backs[back_ind]->SetPointError(nPoint, 0, last_err);
            }
          }
          if (x < lowest[back_ind]) { lowest[back_ind] = x; }
          if (x > highest[back_ind]) {highest[back_ind] = x; }
        }
      }

      Lowest = lowest[0];
      Highest = highest[1];

      delete linear;
      delete backlow;
      delete backhigh;

      if (opts.Contains("c")) {
        backlow = new TF1("backlow", "[0]", lowest[0], highest[0]);
        double y1 = hist->GetBinContent(hist->FindBin(lowest[0]));
        double y2 = hist->GetBinContent(hist->FindBin(highest[0]));
        backlow->SetParameter(0, (y1+y2)/2.0);
        backs[0]->Fit(backlow, ("RQN"+(std::string)foption).c_str());

        backhigh = new TF1("backlow", "[0]", lowest[1], highest[1]);
        y1 = hist->GetBinContent(hist->FindBin(lowest[1]));
        y2 = hist->GetBinContent(hist->FindBin(highest[1]));
        backhigh->SetParameter(0, (y1+y2)/2.0);
        backs[1]->Fit(backhigh, ("RQN"+(std::string)foption).c_str());
        
      }
      else { //default behaviour
        backlow = new TF1("backlow", "[0]+[1]*x", lowest[0], highest[0]);
        double x1 = hist->GetBinCenter(hist->FindBin(lowest[0]));
        double x2 = hist->GetBinCenter(hist->FindBin(highest[0]));
        double y1 = hist->GetBinContent(hist->FindBin(lowest[0]));
        double y2 = hist->GetBinContent(hist->FindBin(highest[0]));

        double w = x2 - x1;
      
        double m = (y2-y1)/(x2-x1);
        double c = y2 - m*x2;

        backlow->SetParameter(0, c);
        backlow->SetParameter(1, m);
        backs[0]->Fit(backlow, ("RQN"+(std::string)foption).c_str());

        backhigh = new TF1("backhigh", "[0]+[1]*x", lowest[1], highest[1]);
        x1 = hist->GetBinCenter(hist->FindBin(lowest[1]));
        x2 = hist->GetBinCenter(hist->FindBin(highest[1]));
        y1 = hist->GetBinContent(hist->FindBin(lowest[1]));
        y2 = hist->GetBinContent(hist->FindBin(highest[1]));

        w = x2 - x1;
      
        m = (y2-y1)/(x2-x1);
        c = y2 - m*x2;

        backhigh->SetParameter(0, c);
        backhigh->SetParameter(1, m);
        backs[1]->Fit(backhigh, ("RQN"+(std::string)foption).c_str());

      }

      linear = new TF1("linear", "[0] + [1]*x", peak.GetLow(), peak.GetHigh());
      double y1 = backlow->Eval(hist->GetBinCenter(hist->FindBin(peak.GetLow())));
      double y2 = backhigh->Eval(hist->GetBinCenter(hist->FindBin(peak.GetHigh())));
      double x1 = peak.GetLow();
      double x2 = peak.GetHigh();

      double m = (y2-y1)/(x2-x1);
      double c = y2 - m*x2;

      linear->SetParameter(0, c);
      linear->SetParameter(1, m);

      TGraphErrors *back_graph = new TGraphErrors();
      int i = hist->FindBin(x1);
      double binWidth = hist->GetBinWidth(i);
      double backErr = backlow->IntegralError(hist->GetBinLowEdge(i), hist->GetBinLowEdge(i)+binWidth)/binWidth;
      back_graph->SetPoint(0, x1, y1);
      back_graph->SetPointError(0, 0, backErr);

      i = hist->FindBin(x2);
      binWidth = hist->GetBinWidth(i);
      backErr = backhigh->IntegralError(hist->GetBinLowEdge(i), hist->GetBinLowEdge(i)+binWidth)/binWidth;
      back_graph->SetPoint(0, x2, y2);
      back_graph->SetPointError(0, 0, backErr);

      back_graph->Fit(linear, ("RQN"+(std::string)foption).c_str());
      
      Set(hist, peak, linear);

      linear->Draw("same");

      this->Draw("same");
      
      backs[0]->Delete();
      backs[1]->Delete();
    }

    void BPeak::SetStep(TH1 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background, Option_t *foption, Option_t *option) { //where upper and lower background regions are fitted and extrpolated to the boundaries of the peak area, a step is created between them with width and centroid of the peak
      SetPoint(hist, peak, background, foption, option);

      TString opts(option);
      opts.ToLower();
      
      //now get centroid and width
      double cent = GetCent();
      double cent_err = GetCentError();
      double sigma = GetWidth()/2.3548;
      double sigma_err = GetWidthError()/2.3548;
      
      delete linear;

      if (opts.Contains("c")) {
        linear = new TF1("linear", "0.5 * ROOT::Math::erfc((x-[0])/(sqrt(2)*[1])) * ([2]) + (1.0 - 0.5 * ROOT::Math::erfc((x-[0])/(sqrt(2)*[1]))) * ([3])", Lowest, Highest);

        linear->SetParameter(0, cent);
        linear->SetParameter(1, sigma);
        linear->SetParameter(2, backlow->GetParameter(0));
        linear->SetParameter(3, backhigh->GetParameter(0));

        linear->SetParError(0, cent_err);
        linear->SetParError(1, sigma_err);
        linear->SetParError(2, backlow->GetParError(0));
        linear->SetParError(3, backhigh->GetParError(0));
      }
      else {
        linear = new TF1("linear", "0.5 * ROOT::Math::erfc((x-[0])/(sqrt(2)*[1])) * ([2] + [3]*x) + (1.0 - 0.5 * ROOT::Math::erfc((x-[0])/(sqrt(2)*[1]))) * ([4] + [5]*x)", Lowest, Highest);

        linear->SetParameter(0, cent);
        linear->SetParameter(1, sigma);
        linear->SetParameter(2, backlow->GetParameter(0));
        linear->SetParameter(3, backlow->GetParameter(1));
        linear->SetParameter(4, backhigh->GetParameter(0));
        linear->SetParameter(5, backhigh->GetParameter(1));      

        linear->SetParError(0, cent_err);
        linear->SetParError(1, sigma_err);
        linear->SetParError(2, backlow->GetParError(0));
        linear->SetParError(3, backlow->GetParError(1));
        linear->SetParError(4, backhigh->GetParError(0));
        linear->SetParError(5, backhigh->GetParError(1));
      }
      Set(hist, peak, linear);

      //do this again
      for (int i=0; i<3; ++i) {
        cent = GetCent();                  
        cent_err = GetCentError();         
        sigma = GetWidth()/2.3548;         
        sigma_err = GetWidthError()/2.3548;

        if (opts.Contains("c")) {
          linear->SetParameter(0, cent);
          linear->SetParameter(1, sigma);
          linear->SetParameter(2, backlow->GetParameter(0));
          linear->SetParameter(3, backhigh->GetParameter(0));
         
          linear->SetParError(0, cent_err);
          linear->SetParError(1, sigma_err);
          linear->SetParError(2, backlow->GetParError(0));
          linear->SetParError(3, backhigh->GetParError(0));
        }
        else {
          linear->SetParameter(0, cent);
          linear->SetParameter(1, sigma);
          linear->SetParameter(2, backlow->GetParameter(0));
          linear->SetParameter(3, backlow->GetParameter(1));
          linear->SetParameter(4, backhigh->GetParameter(0));
          linear->SetParameter(5, backhigh->GetParameter(1));      

          linear->SetParError(0, cent_err);
          linear->SetParError(1, sigma_err);
          linear->SetParError(2, backlow->GetParError(0));
          linear->SetParError(3, backlow->GetParError(1));
          linear->SetParError(4, backhigh->GetParError(0));
          linear->SetParError(5, backhigh->GetParError(1));
        }
        
        Set(hist, peak, linear);
      }

      linear->Draw("same");
      
      this->Draw("same");            
    }
    
    void BPeak::Paint(Option_t *option /*="same"*/) {      
      mPeak.SetLineColor(kBlue);
      mPeak.SetFillStyle(3003);
      mPeak.SetFillColor(kBlue);
      mPeak.Paint("");

      for (int i=0; i<mBackgrounds.size(); ++i) {
        mBackgrounds[i].SetLineColor(kRed);
        mBackgrounds[i].SetFillStyle(3003);
        mBackgrounds[i].SetFillColor(kRed);
        mBackgrounds[i].Paint("");
      }
      // TAttLine::SetLineColor(kRed);
      // TAttLine::Modify();
      
      // double x1[2];
      // double y1[2];
      // double x2[2];
      // double y2[2];

      // // std::vector<double[2]> bx1;
      // // std::vector<double[2]> bx2;
      
      // x1[0] = mPeak.GetLow();
      // x1[1] = mPeak.GetLow();

      // y1[0] = gPad->GetUymin();
      // y1[1] = gPad->GetUymax();

      // x2[0] = mPeak.GetHigh();
      // x2[1] = mPeak.GetHigh();

      // y2[0] = gPad->GetUymin();
      // y2[1] = gPad->GetUymax();

      // gPad->PaintPolyLine(2, &x1[0], &y1[0], option);
      // gPad->PaintPolyLine(2, &x2[0], &y2[0], option);

      // for (int i=0; i<mBackgrounds.size(); ++i) {
      //   TAttLine::SetLineColor(kBlue);
      //   TAttLine::Modify();
      //   x1[0] = mBackgrounds[i].GetLow();
      //   x1[1] = mBackgrounds[i].GetLow();

      //   x2[0] = mBackgrounds[i].GetHigh();
      //   x2[1] = mBackgrounds[i].GetHigh();

      //   gPad->PaintPolyLine(2, &x1[0], &y1[0], option);
      //   gPad->PaintPolyLine(2, &x2[0], &y2[0], option);
      // }        
    }

    Int_t BPeak::DistancetoPrimitive(Int_t px, Int_t py) {
      (void)py;
      double lowDist = std::abs(gPad->XtoPixel(mPeak.GetLow()) - px);
      double highDist = std::abs(gPad->XtoPixel(mPeak.GetHigh()) - px);

      for (int i=0; i<mBackgrounds.size(); ++i) {
        double low = mBackgrounds[i].GetLow();
        double high = mBackgrounds[i].GetHigh();

        low = std::abs(gPad->XtoPixel(low) - px);
        high = std::abs(gPad->XtoPixel(high) - px);

        if (low < lowDist) { lowDist = low; }
        if (high < highDist) { highDist = high; }
      }

      return fmin(lowDist, highDist);
    }

    void BPeak::ExecuteEvent(Int_t event, Int_t px, Int_t py) {
      (void)py;
      if (!gPad) { return; }
      int kMaxDiff = 20;

      if (!gPad->IsEditable()) { return; }

      switch(event) {
      case kMouseMotion:
        if (DistancetoPrimitive(px,py) < kMaxDiff) {
          gPad->SetCursor(kPointer);
          return;
        }
        break;
      }
    }
      
    void BPeak::Set(TH1 *hist, GamR::TK::Gate peak, GamR::TK::Gate background, Option_t *foption, Option_t *option) {
      std::vector<GamR::TK::Gate > bg;
      bg.push_back(background);
      Set(hist, peak, bg, foption, option);
    }

    void BPeak::Set(TH1 *hist, Option_t *foption, Option_t *option) {
      GamR::TK::Gate peak;
      std::cout << "Select peak region: " << std::endl;
      peak.SetGate();
      std::cout << "Select background regions:" << std::endl;
      std::vector<GamR::TK::Gate > background;
      while(true) {
        GamR::TK::Gate bg;
        int retval = bg.SetGate();
        if (retval<0) { break; }
        background.push_back(bg);
      }
      Set(hist, peak, background, foption, option);
    }

    void BPeak::Set(TH2 *hist, Option_t *foption, Option_t *option) {
      GamR::TK::Gate prompt;
      std::cout << "Select prompt region: " << std::endl;
      TH1D *projx = hist->ProjectionX();
      projx->Draw();
      prompt.SetGate();
      std::cout << "Select non-prompt regions: " << std::endl;
      std::vector<GamR::TK::Gate > nonprompt;
      while(true) {
        GamR::TK::Gate np;
        int retval = np.SetGate();
        if (retval<0) { break; }
        nonprompt.push_back(np);
      }
      if (nonprompt.size() == 0) { std::cout << "Must have at least one non-prompt region!" << std::endl; return; }
      //make prompt and non-prompt histograms
      TH1D *hPrompt = prompt.ApplyX(hist, "hPrompt");
      double p_width = prompt.GetBinWidth(projx);
      TH1D *hNonPrompt = nonprompt[0].ApplyX(hist, "hNonPrompt0");
      double np_width = nonprompt[0].GetBinWidth(projx);
      for (int i=1; i<nonprompt.size(); ++i) {
        hNonPrompt->Add(nonprompt[i].ApplyX(hist, ("hNonPrompt"+std::to_string(i)).c_str()));
        np_width += nonprompt[i].GetBinWidth(projx);
      }
      hNonPrompt->Scale(p_width/np_width);

      //now plot them both (?)
      hPrompt->Draw("hist");
      hNonPrompt->SetLineColor(kRed);
      hNonPrompt->Draw("hist same");
      //make LFit
      BPeak::LFit lfit(hNonPrompt);
      
      //select peak and background regions
      GamR::TK::Gate peak;
      std::cout << "Select peak region: " << std::endl;
      peak.SetGate();
      std::cout << "Select background regions:" << std::endl;
      std::vector<GamR::TK::Gate > background;
      double lowest = 1e9;
      double highest = -1e9;
      while(true) {
        GamR::TK::Gate bg;
        int retval = bg.SetGate();
        if (retval<0) { break; }
        background.push_back(bg);
        if (bg.GetLow() < lowest) {
          lowest = bg.GetLow();
        }
        if (bg.GetHigh() > highest) {
          highest = bg.GetHigh();
        }
      }
      if (background.size() == 0) { std::cout << "Must have at least one background region!" << std::endl; return; }

      ROOT::Fit::DataRange range(background[0].GetLow(), background[0].GetHigh());
      for (int i=1; i<background.size(); ++i) {
        range.AddRange(0, background[i].GetLow(), background[i].GetHigh());
      }

      delete linear;
      linear = new TF1("linear", lfit, lowest, highest, 2);
      //set initial guesses in linear here

      double x1 = hPrompt->GetBinCenter(hPrompt->FindBin(lowest));
      double x2 = hPrompt->GetBinCenter(hPrompt->FindBin(highest));
      double y1 = hPrompt->GetBinContent(hPrompt->FindBin(lowest)) - hNonPrompt->GetBinContent(hNonPrompt->FindBin(lowest));
      double y2 = hPrompt->GetBinContent(hPrompt->FindBin(highest)) - hNonPrompt->GetBinContent(hNonPrompt->FindBin(highest));

      double w = x2 - x1;
      
      double m = (y2-y1)/(x2-x1);
      double c = y2 - m*x2;

      linear->SetParameter(0, c);
      linear->SetParameter(1, m);

      ROOT::Fit::DataOptions opt;
      opt.fUseEmpty = true;
      ROOT::Fit::BinData data(opt, range);
      ROOT::Fit::FillData(data, hPrompt);
      ROOT::Math::WrappedMultiTF1 fitFunc(*linear, linear->GetNdim());
      ROOT::Fit::Fitter fitter;
      fitter.SetFunction(fitFunc, false);
      fitter.LikelihoodFit(data);

      fitter.Result().Print(std::cout);
      //linear->Draw("same");

      Set(hPrompt, peak, linear);

      TH2D* hBackSub = (TH2D*)hPrompt->Clone("hBackSub");
      hBackSub->Add(hNonPrompt, -1.0);
      hBackSub->Draw("hist");

      TF1 *lindraw = new TF1("lindraw", "[0] + [1]*x", lowest, highest);
      lindraw->SetParameter(0, linear->GetParameter(0));
      lindraw->SetParameter(1, linear->GetParameter(1));
      lindraw->Draw("same");

      
    }

    void BPeak::Print() {
      TString sPrintString;
      sPrintString.Form("Centroid       Height         FWHM           Area          Counts   ");
      std::printf("%s\n", sPrintString.Data());
      
      char line[120];
      *line = '\0';
      GamR::Utils::wrresult(line, GetCent(),
                            GetCentError(), 15);
      GamR::Utils::wrresult(line, GetAmp(),
                            GetAmpError(), 30);
      GamR::Utils::wrresult(line, GetWidth(),
                            GetWidthError(), 45);
      GamR::Utils::wrresult(line, GetArea(),
                            GetAreaError(), 60);
      GamR::Utils::wrresult(line, GetCounts(),
                            GetCountsError(), 75);
      std::printf("%s\n", line);    
    }
    
    GaussianPeak::GaussianPeak(double Low, double High) : FPeak(Low, High, Gaussian) {
      fPeakFunc = new TF1("GaussianPeak", "[0]*exp(-pow(x-[1], 2)/(2*pow([2],2)))",
                          Low, High);
      fPeakFunc->SetParName(0, "Amp");
      fPeakFunc->SetParName(1, "Cent");
      fPeakFunc->SetParName(2, "Sigma");
    }

    StepGaussianPeak::StepGaussianPeak(double Low, double High) : FPeak(Low, High, StepGaussian) {
      fPeakFunc = new TF1("StepGaussianPeak", "[0]*exp(-pow(x-[1], 2)/(2*pow([2],2))) + [0]*([3]/100)*std::erfc((x-[1])/(sqrt(2)*[2]))",
                          Low, High);
      fPeakFunc->SetParName(0, "Amp");
      fPeakFunc->SetParName(1, "Cent");
      fPeakFunc->SetParName(2, "Sigma");
      fPeakFunc->SetParName(3, "H");

    }

    OneTailGaussianPeak::OneTailGaussianPeak(double Low, double High) : FPeak(Low, High, OneTailGaussian) {
      fPeakFunc = new TF1("OneTailGaussianPeak", "[0]*(1 - [3]/100)*exp(-pow(x-[1],2)/(2*pow([2],2))) + "
                           "[0]*([3]/100)*exp((x-[1])/[4])*std::erfc((x-[1])/"
                          "(sqrt(2)*[2]) + [2]/(sqrt(2)*[4]))",
                          Low, High);
      fPeakFunc->SetParName(0, "Amp");
      fPeakFunc->SetParName(1, "Cent");
      fPeakFunc->SetParName(2, "Sigma");
      fPeakFunc->SetParName(3, "R");
      fPeakFunc->SetParName(4, "Beta");

    }

    double OneTailGaussianPeak::GetAreaError() {
      TMatrixD covMatrix(5,5);
      for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
          covMatrix[i][j] = 0;
        }
      }

      for(int i=0; i<5; i++) {
        covMatrix[i][i] = fPeakFunc->GetParError(i) * fPeakFunc->GetParError(i);
      }

      double areaError = fPeakFunc->IntegralError(fLow, fHigh, fPeakFunc->GetParameters(), covMatrix.GetMatrixArray());
      return areaError;
    }

    OneTailStepGaussianPeak::OneTailStepGaussianPeak(double Low, double High) : FPeak(Low, High, OneTailStepGaussian) {
      fPeakFunc = new TF1("OneTailStepGaussianPeak", "[0]*(1 - [3]/100)*exp(-pow(x-[1],2)/(2*pow([2],2))) + "
                          "[0]*([3]/100)*exp((x-[1])/[4])*std::erfc((x-[1])/"
                          "(sqrt(2)*[2]) + [2]/(sqrt(2)*[4])) + "
                          "[0]*([5]/100)*std::erfc((x-[1])/(sqrt(2)*[2]))",
                          Low, High);
      fPeakFunc->SetParName(0, "Amp");
      fPeakFunc->SetParName(1, "Cent");
      fPeakFunc->SetParName(2, "Sigma");
      fPeakFunc->SetParName(3, "R");
      fPeakFunc->SetParName(4, "Beta");
      fPeakFunc->SetParName(5, "H");
    }
    
    double OneTailStepGaussianPeak::GetArea() {
      //construct OneTailGaussianPeak and use that to get area
      GamR::TK::OneTailGaussianPeak purePeak(fLow, fHigh);

      for (int i=0; i<5; ++i) {
        purePeak.GetFunc()->SetParameter(i, GetFunc()->GetParameter(i));
        purePeak.GetFunc()->SetParError(i, GetFunc()->GetParError(i));
      }

      double area = purePeak.GetArea();      
      return area;
    }

    double OneTailStepGaussianPeak::GetAreaError() {
      //construct OneTailGaussianPeak and use that to get area
      GamR::TK::OneTailGaussianPeak purePeak(fLow, fHigh);

      for (int i=0; i<5; ++i) {
        purePeak.GetFunc()->SetParameter(i, GetFunc()->GetParameter(i));
        purePeak.GetFunc()->SetParError(i, GetFunc()->GetParError(i));
      }

      double area = purePeak.GetAreaError();      
      return area;
    }

    TwoTailGaussianPeak::TwoTailGaussianPeak(double Low, double High) : FPeak(Low, High, TwoTailGaussian) {
      fPeakFunc = new TF1("TwoTailGaussianPeak",
                          "[0]*(1 -([3]/100 + "
                          "[5]/100))*exp(-pow(x-[1],2)/(2*pow([2],2))) + "
                          "[0]*([3]/100)*exp((x-[1])/[4])*std::erfc((x-[1])/"
                          "(sqrt(2)*[2]) + [2]/(sqrt(2)*[4])) + "
                          "[0]*([5]/100)*exp((x-[1])/[6])*std::erfc((x-[1])/"
                          "(sqrt(2)*[2]) + [2]/(sqrt(2)*[6]))",
                          Low, High);
      fPeakFunc->SetParName(0, "Amp");
      fPeakFunc->SetParName(1, "Cent");
      fPeakFunc->SetParName(2, "Sigma");
      fPeakFunc->SetParName(3, "R1");
      fPeakFunc->SetParName(4, "Beta1");
      fPeakFunc->SetParName(5, "R2");
      fPeakFunc->SetParName(6, "Beta2");
    }

    double TwoTailGaussianPeak::GetAreaError() {
      TMatrixD covMatrix(7,7);
      for (int i=0; i<7; i++) {
        for (int j=0; j<7; j++) {
          covMatrix[i][j] = 0;
        }
      }

      for(int i=0; i<7; i++) {
        covMatrix[i][i] = fPeakFunc->GetParError(i) * fPeakFunc->GetParError(i);
      }

      double areaError = fPeakFunc->IntegralError(fLow, fHigh, fPeakFunc->GetParameters(), covMatrix.GetMatrixArray());
      return areaError;
    }
    
    TwoTailStepGaussianPeak::TwoTailStepGaussianPeak(double Low, double High) : FPeak(Low, High, TwoTailStepGaussian) {
      fPeakFunc = new TF1("TwoTailStepGaussianPeak",
                          "[0]*(1 -([3]/100 + "
                          "[5]/100))*exp(-pow(x-[1],2)/(2*pow([2],2))) + "
                          "[0]*([3]/100)*exp((x-[1])/[4])*std::erfc((x-[1])/"
                          "(sqrt(2)*[2]) + [2]/(sqrt(2)*[4])) + "
                          "[0]*([5]/100)*exp((x-[1])/[6])*std::erfc((x-[1])/"
                          "(sqrt(2)*[2]) + [2]/(sqrt(2)*[6]))  + "
                          "[0]*([7]/100)*std::erfc((x-[1])/(sqrt(2)*[2]))",
                          Low, High);
      fPeakFunc->SetParName(0, "Amp");
      fPeakFunc->SetParName(1, "Cent");
      fPeakFunc->SetParName(2, "Sigma");
      fPeakFunc->SetParName(3, "R1");
      fPeakFunc->SetParName(4, "Beta1");
      fPeakFunc->SetParName(5, "R2");
      fPeakFunc->SetParName(6, "Beta2");
      fPeakFunc->SetParName(7, "H");
    }

    double TwoTailStepGaussianPeak::GetArea() {
      //construct TwoTailGaussianPeak and use that to get area
      GamR::TK::TwoTailGaussianPeak purePeak(fLow, fHigh);

      for (int i=0; i<7; ++i) {
        purePeak.GetFunc()->SetParameter(i, GetFunc()->GetParameter(i));
        purePeak.GetFunc()->SetParError(i, GetFunc()->GetParError(i));
      }

      double area = purePeak.GetArea();      
      return area;
    }

    double TwoTailStepGaussianPeak::GetAreaError() {
      //construct TwoTailGaussianPeak and use that to get area
      GamR::TK::TwoTailGaussianPeak purePeak(fLow, fHigh);

      for (int i=0; i<7; ++i) {
        purePeak.GetFunc()->SetParameter(i, GetFunc()->GetParameter(i));
        purePeak.GetFunc()->SetParError(i, GetFunc()->GetParError(i));
      }

      double area = purePeak.GetAreaError();      
      return area;
    }
    
    BPeak *FitBPeak(TCanvas *canvas, Option_t *foption, Option_t *option) {
      TH1D *hist = GamR::Utils::GetHist1D(canvas);
      if (!hist) { return NULL; }

      BPeak *peak = new BPeak();
      peak->Set(hist, foption, option);

      peak->Print();
      return peak;
    }

    BPeak *ClickBPeak(TCanvas *canvas) {
      TH1D *hist = GamR::Utils::GetHist1D(canvas);
      if (!hist) { return NULL; }

      BPeak *peak = new BPeak();
      //get two (x,y) coordinates
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
      std::cout << "Click for lower point, press any key to exit..." << std::endl;
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
            std::cout << "Click for upper point, press any key to exit..." << std::endl;
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
      canvas->DeleteExec("ex");
      canvas->SetCrosshair(0);

      peak->Set(hist, lowX, lowY, highX, highY);
      
      peak->Print();
      return peak;           
    }
      

    OneTailGaussianPeak::OneTailGaussianPeak() {}
    OneTailGaussianPeak::~OneTailGaussianPeak() {}
    
  }
}
