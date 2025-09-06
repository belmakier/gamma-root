#include <chrono>

#include <TMarker.h>

#include "Cut.hh"



namespace GamR {
  namespace Spect {
    TH1D *ProjX(TH2 *hist, const char *name) {
      return hist->ProjectionX(name);
    }

    TH1D *ProjX(TH2 *hist) {
      return hist->ProjectionX(((std::string)hist->GetName()+"_px").c_str());
    }

    TH1D *ProjX(TVirtualPad *canvas, const char *name) {
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      TH1D *ret = ProjX(hist, name);
      ret->Draw("hist");
      return ret;
    }

    TH1D *ProjX(TVirtualPad *canvas) {
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      TH1D *ret = ProjX(hist);
      ret->Draw("hist");
      return ret;
    }

    TH1D *ProjY(TH2 *hist, const char *name) {
      return hist->ProjectionY(name);
    }

    TH1D *ProjY(TH2 *hist) {
      return hist->ProjectionY(((std::string)hist->GetName()+"_py").c_str());
    }

    TH1D *ProjY(TVirtualPad *canvas, const char *name) {
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      TH1D *ret = ProjY(hist, name);
      ret->Draw("hist");
      return ret;
    }

    TH1D *ProjY(TVirtualPad *canvas) {
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      TH1D *ret = ProjY(hist);
      ret->Draw("hist");
      return ret;
    }
    
    
    /**
       Carries out a gate and projection

       Gates are applied on the X-axis.

       @param hist 2D histogram to act on
       @param peak Gate object for the peak bounds
       @param name Name of the output histogram
       @return 1D histogram containing the gated projection
    */
    TH1D *GateX(TH2 *hist, GamR::TK::Gate peak, const char *name)
    {
      /* applying gates in X direction */
      TH1D *hOut = peak.ApplyX(hist, name);
      return hOut;
    }

    TH1D *GateX(TH2 *hist, GamR::TK::Gate peak)
    {
      /* applying gates in X direction */
      TH1D *hOut = peak.ApplyX(hist, ((std::string)hist->GetName()+"_gx").c_str());
      return hOut;
    }
    
    TH1D *GateX(TCanvas *canvas, const char *name)
    {
      /* get histogram */
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      hist->ProjectionX()->Draw("hist");
      std::cout << "Select peak region:" << std::endl;
      GamR::TK::Gate peak(canvas, "x");
      //std::cout << peak << std::endl;

      TH1D *hOut = GateX(hist, peak, name);
      hOut->Draw("hist");
      return hOut;
    }

    TH1D *GateX(TCanvas *canvas)
    {
      /* get histogram */
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      hist->ProjectionX()->Draw("hist");
      std::cout << "Select peak region:" << std::endl;
      GamR::TK::Gate peak(canvas, "x");
      //std::cout << peak << std::endl;

      TH1D *hOut = GateX(hist, peak);
      hOut->Draw("hist");
      return hOut;
    }


    /**
       Carries out a gate and projection

       Gates are applied on the Y-axis.

       @param hist 2D histogram to act on
       @param peak Gate object for the peak bounds
       @param name Name of the output histogram
       @return 1D histogram containing the gated projection
    */
    TH1D *GateY(TH2 *hist, GamR::TK::Gate peak, const char *name)
    {
      /* applying gates in Y direction */
      TH1D *hOut = peak.ApplyY(hist, name);
      return hOut;
    }

    TH1D *GateY(TH2 *hist, GamR::TK::Gate peak)
    {
      /* applying gates in Y direction */
      TH1D *hOut = peak.ApplyY(hist, ((std::string)hist->GetName()+"_gy").c_str());
      return hOut;
    }

    TH1D *GateY(TCanvas *canvas, const char *name)
    {
      /* get histogram */
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      hist->ProjectionY()->Draw("hist");
      std::cout << "Select peak region:" << std::endl;
      GamR::TK::Gate peak(canvas, "x");
      //std::cout << peak << std::endl;

      TH1D *hOut = GateY(hist, peak, name);
      hOut->Draw("hist");
      return hOut;
    }

    TH1D *GateY(TCanvas *canvas)
    {
      /* get histogram */
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      hist->ProjectionY()->Draw("hist");
      std::cout << "Select peak region:" << std::endl;
      GamR::TK::Gate peak(canvas, "x");
      //std::cout << peak << std::endl;

      TH1D *hOut = GateY(hist, peak);
      hOut->Draw("hist");
      return hOut;
    }

    
    /**
       Carries out a rudimentary background subtraction

       Subtracts a projection of the background region from a
       projection of the peak region, with a scaling factor equal to
       the ratio of the regions' widths.

       Gates are applied on the X-axis.

       @param hist 2D histogram to act on
       @param peak Gate object for the peak bounds
       @param background Gate object for the background bounds
       @param name Name of the output histogram
       @return 1D histogram containing the background-subtracted projection
    */    
    TH1D *BackgroundSubtractX(TH2 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background, const char *name)
    {
      if (background.size()==0) { std::cout << "Must select at least one background region" << std::endl; return NULL; }
      /* applying gates in X direction */
      TH1D *hTotal = peak.ApplyX(hist, "hTotal");
      TH1D *hProjX = (TH1D*)hist->ProjectionX();
      TH1D *hBackground = background[0].ApplyX(hist, "hBackground");
      int backgroundWidth = background[0].GetBinWidth(hProjX);
      for (int i=1; i<background.size(); ++i) {
        TH1D *hBack = background[i].ApplyX(hist, "hBack");
        hBackground->Add(hBack);
        backgroundWidth += background[i].GetBinWidth(hProjX);
      }

      TH1D *hOut = (TH1D*)hTotal->Clone(name);
      hOut->SetTitle(name);
      
      /* get bin widths of gates */
      double scale =
        (static_cast<double>(peak.GetBinWidth(hProjX)) /
         static_cast<double>(backgroundWidth));
      
      hOut->Add(hBackground, -scale);

      //do correct error propagation
      for (int i=1; i<=hOut->GetNbinsX(); ++i) {
        double sigT = hTotal->GetBinError(i);
        double T = hTotal->GetBinContent(i);
        double sigB = hBackground->GetBinError(i);
        double B = hBackground->GetBinContent(i);
        double sigsquared = pow(sigT, 2) + pow(scale*sigB, 2);
        hOut->SetBinError(i, sqrt(sigsquared)); 
      }

      return hOut;
    }
    
    TH1D *BackgroundSubtractX(TH2 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background)
    {
      return BackgroundSubtractX(hist, peak, background, ((std::string)hist->GetName()+"_bsx").c_str());
    }
    
    TH1D *BackgroundSubtractX(TH2 *hist, GamR::TK::Gate peak, GamR::TK::Gate background, const char *name) {
      std::vector<GamR::TK::Gate > bg = {background};
      return BackgroundSubtractX(hist, peak, bg, name);
    }

    TH1D *BackgroundSubtractX(TH2 *hist, GamR::TK::Gate peak, GamR::TK::Gate background) {
      std::vector<GamR::TK::Gate > bg = {background};
      return BackgroundSubtractX(hist, peak, bg);
    }
         
    TH1D *BackgroundSubtractX(TH2 *hist, GamR::Nucleus::Transition peak, const char *name)
    {
      return BackgroundSubtractX(hist, *peak.GetGate(), *peak.GetGateBG(), name);
    }

    TH1D *BackgroundSubtractX(TH2 *hist, GamR::Nucleus::Transition peak)
    {
      return BackgroundSubtractX(hist, *peak.GetGate(), *peak.GetGateBG());
    }

    TH1D *BackgroundSubtractX(TCanvas *canvas, const char *name)
    {
      /* get histogram */
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      hist->ProjectionX()->Draw("hist");
      std::cout << "Select peak region:" << std::endl;
      GamR::TK::Gate peak(canvas, "x");
      //std::cout << peak << std::endl;
      std::cout << "Select background regions, key press to stop:" << std::endl;
      std::vector<GamR::TK::Gate > background;
      while(true) {
        GamR::TK::Gate bg;
        int retval = bg.SetGate(canvas, "x");
        if (retval<0) { break; }
        background.push_back(bg);
      }

      TH1D *hOut = BackgroundSubtractX(hist, peak, background, name);
      hOut->Draw("hist");
      return hOut;
    }

    TH1D *BackgroundSubtractX(TCanvas *canvas)
    {
      /* get histogram */
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      hist->ProjectionX()->Draw("hist");
      std::cout << "Select peak region:" << std::endl;
      GamR::TK::Gate peak(canvas, "x");
      std::cout << "Select background regions, key press to stop:" << std::endl;
      std::vector<GamR::TK::Gate > background;
      while(true) {
        GamR::TK::Gate bg;
        int retval = bg.SetGate(canvas, "x");
        if (retval<0) { break; }
        background.push_back(bg);
      }

      TH1D *hOut = BackgroundSubtractX(hist, peak, background);
      hOut->Draw("hist");
      return hOut;
    }

    /**
       Carries out a rudimentary background subtraction

       Subtracts a projection of the background region from a
       projection of the peak region, with a scaling factor equal to
       the ratio of the regions' widths.

       Gates are applied on the Y-axis.

       @param hist 2D histogram to act on
       @param peak Gate object for the peak bounds
       @param background Gate object for the background bounds
       @param name Name of the output histogram
       @return 1D histogram containing the background-subtracted projection
    */
    TH1D *BackgroundSubtractY(TH2 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background, const char *name)
    {
      if (background.size()==0) { std::cout << "Must select at least one background region" << std::endl; return NULL; }
      /* applying gates in Y direction */
      TH1D *hTotal = peak.ApplyY(hist, "hTotal");
      TH1D *hProjY = (TH1D*)hist->ProjectionY();
      TH1D *hBackground = background[0].ApplyY(hist, "hBackground");
      int backgroundWidth = background[0].GetBinWidth(hProjY);
      for (int i=1; i<background.size(); ++i) {
        TH1D *hBack = background[i].ApplyY(hist, "hBack");
        hBackground->Add(hBack);
        backgroundWidth += background[i].GetBinWidth(hProjY);
      }

      TH1D *hOut = (TH1D*)hTotal->Clone(name);
      hOut->SetTitle(name);
      
      /* get bin widths of gates */
      double scale =
        (static_cast<double>(peak.GetBinWidth(hProjY)) /
         static_cast<double>(backgroundWidth));
      
      hOut->Add(hBackground, -scale);

      //do correct error propagation
      for (int i=1; i<=hOut->GetNbinsX(); ++i) {
        double sigT = hTotal->GetBinError(i);
        double T = hTotal->GetBinContent(i);
        double sigB = hBackground->GetBinError(i);
        double B = hBackground->GetBinContent(i);
        double sigsquared = pow(sigT, 2) + pow(scale*sigB, 2);
        hOut->SetBinError(i, sqrt(sigsquared));
      }

      return hOut;
    }

    TH1D *BackgroundSubtractY(TH2 *hist, GamR::TK::Gate peak, std::vector<GamR::TK::Gate > background)
    {
      return BackgroundSubtractY(hist, peak, background, ((std::string)hist->GetName()+"_bsy").c_str());
    }
    
    TH1D *BackgroundSubtractY(TH2 *hist, GamR::TK::Gate peak, GamR::TK::Gate background, const char *name)
    {
      std::vector<GamR::TK::Gate > bg = {background};
      return BackgroundSubtractY(hist, peak, bg, name);
    }

    TH1D *BackgroundSubtractY(TH2 *hist, GamR::TK::Gate peak, GamR::TK::Gate background)
    {
      std::vector<GamR::TK::Gate > bg = {background};
      return BackgroundSubtractY(hist, peak, bg);
    }
    
    TH1D *BackgroundSubtractY(TH2 *hist, GamR::Nucleus::Transition peak, const char *name)
    {
      return BackgroundSubtractY(hist, *peak.GetGate(), *peak.GetGateBG(), name);
    }

    TH1D *BackgroundSubtractY(TH2 *hist, GamR::Nucleus::Transition peak)
    {
      return BackgroundSubtractY(hist, *peak.GetGate(), *peak.GetGateBG());
    }
  
    TH1D *BackgroundSubtractY(TCanvas *canvas, const char *name)
    {
      /* get histogram */
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      hist->ProjectionY()->Draw("hist");
      std::cout << "Select peak region:" << std::endl;
      GamR::TK::Gate peak(canvas, "x");
      //std::cout << peak << std::endl;
      std::cout << "Select background regions:" << std::endl;
      std::vector<GamR::TK::Gate > background;
      while(true) {
        GamR::TK::Gate bg;
        int retval = bg.SetGate(canvas, "x");
        if (retval<0) { break; }
        background.push_back(bg);
      }

      TH1D *hOut = BackgroundSubtractY(hist, peak, background, name);
      hOut->Draw("hist");
      return hOut;
    }

    TH1D *BackgroundSubtractY(TCanvas *canvas)
    {
      /* get histogram */
      TH2D *hist = GamR::Utils::GetHist2D(canvas);
      if (!hist) { return NULL; }
      hist->ProjectionY()->Draw("hist");
      std::cout << "Select peak region:" << std::endl;
      GamR::TK::Gate peak(canvas, "x");
      //std::cout << peak << std::endl;
      std::cout << "Select background regions:" << std::endl;
      std::vector<GamR::TK::Gate > background;
      while(true) {
        GamR::TK::Gate bg;
        int retval = bg.SetGate(canvas, "x");
        if (retval<0) { break; }
        background.push_back(bg);
      }

      TH1D *hOut = BackgroundSubtractY(hist, peak, background);
      hOut->Draw("hist");
      return hOut;
    }

    /**
       Implementation of TSpectrum::Background to take a histogram as
       input. For details refer to the ROOT TSpectrum documentation.

       @param[in] hist 2D histogram
       @param[in] NiterX Maximal X width of clipping window
       @param[in] NiterY Maximal Y width of clipping window
       @param[in] direction Direction of clipping window:
       TSpectrum2::kBackIncreasingwindow, TSpectrum2::kBackDecreasingWindow
       @param[in] filtertype Filter algorithm: TSpectrum2::kBackSuccessiveFiltering,
       TSpectrum2::kBackOneStepFiltering
       @return[out] Smart pointer to background estimate of input histogram
    */
    std::shared_ptr<TH2D> BackgroundEstimate(const TH2 *hist, Int_t NiterX, Int_t NiterY, Int_t direction, Int_t filtertype)
    {
      Int_t nbinx = hist->GetNbinsX();
      Int_t nbiny = hist->GetNbinsY();

      Double_t **spectrum = new Double_t *[nbinx];
      for (int x = 0; x < nbinx; ++x) {
        spectrum[x] = new Double_t[nbiny];
        for (int y = 0; y < nbiny; ++y) {
          spectrum[x][y] = hist->GetBinContent(x + 1, y + 1);
        }
      }

      auto analyser = std::make_unique<TSpectrum2>();
      analyser->Background(spectrum, nbinx, nbiny, NiterX, NiterY, direction, filtertype);

      auto name = std::string(hist->GetName()) + "_bg";
      auto output = std::shared_ptr<TH2D>(static_cast<TH2D *>(hist->Clone(name.c_str())));
      output->SetTitle("Background subtracted");
      for (int x = 0; x < nbinx; ++x) {
        for (int y = 0; y < nbiny; ++y) {
          output->SetBinContent(x + 1, y + 1, spectrum[x][y]);
        }
      }
      delete[] spectrum;
      return output;
    }

    TH2D *BackgroundSubtract2D(TH2 *peak, TH2 *background, double scale) {
      TH2D *backsub = (TH2D*)peak->Clone(((std::string)peak->GetName()+"_bs").c_str());
      backsub->Add(background, -scale);
      //correct error propagation
      double lastSigT = 1.0;
      for (int i=0; i<=backsub->GetNbinsX(); ++i) {
        for (int j=0; j<=backsub->GetNbinsY(); ++j) {
          double sigT = peak->GetBinError(i,j);
          double T = peak->GetBinContent(i,j);
          double sigB = background->GetBinError(i,j);
          double B = background->GetBinContent(i,j);

          double sigsquared = pow(sigT, 2) + pow(scale*sigB, 2);
          backsub->SetBinError(i, j, sqrt(sigsquared));
          lastSigT = sigT;
        }
      }

      return backsub;
    }

    TCutG *DrawCut(TVirtualPad *canvas, bool verbose, std::string filename, int ID) {
      TGraph *gr = new TGraph();
      gr->SetLineColor(kRed);
      gr->SetMarkerColor(kRed);
      gr->SetMarkerStyle(8);

      GamR::Utils::Clicker click;
      std::vector<std::string> messages = {"Click for next point, press any key to exit..."};

      int retval = click.GetClicks(canvas, -1, messages, 1);

      for (int i=0; i<click.xs.size(); ++i) {
        gr->AddPoint(click.xs[i], click.ys[i]);
      }
      gr->AddPoint(click.xs[0], click.ys[0]);

      click.line->Delete();
      click.line=NULL;

      gr->Draw("same LP");

      canvas->Update();

      if (verbose) {
        PrintCut((TCutG*)gr);
      }

      
      if (filename.size()>0) {
        std::ofstream ofile(filename.c_str(), std::ios_base::app);
        while (ID<=-1) {
          std::cout << "Enter ID: ";
          std::string sID;
          std::cin >> sID;
          try {
            ID = std::atoi(sID.c_str());
          }
          catch (...) {
            std::cout << "Invalid input!" << std::endl;
          }
          if (ID == 0) {
            std::cout << "Invalid input!" << std::endl;
          }
        }
        std::cout << "Enter name: ";
        std::string name;
        std::cin >> name;
        double x,y;
        gr->SetName(name.c_str());
        ofile << ID << "   " << gr->GetN() << "   " << name << std::endl;
        for (int i=0; i<gr->GetN(); ++i) {
          gr->GetPoint(i,x,y);
          ofile << x << "   " << y << std::endl;
        }
      }

      return (TCutG*)gr;
    }

    TCutG *DrawCut(std::string cutfile, int ID, TVirtualPad *canvas) {
      FILE *file = fopen(cutfile.c_str(), "ra");
      if (file == NULL) { std::cout << "Cuts file " << cutfile << " does not exist" << std::endl; return 0; }
      std::stringstream ss;
      char cline[2048];

      int ind = 0;
      while(std::fgets(cline, sizeof cline, file)!=NULL) {
        std::string line(cline);
        if (line.size() <= 1) { continue; }
        if (line[0] == '#') { continue; }
        if (line[0] == ';') { continue; }

        ss.clear();
        ss.str(line);

        std::string name;
        int id, npoints;        
        ss >> id;
        ss >> npoints;
        ss >> name;

        TCutG *cut = new TCutG();
        cut->SetName(name.c_str());
        cut->SetLineColor(kRed);
        cut->SetMarkerColor(kRed);

        int ct = 0;
        while (ct < npoints) {
          if (std::fgets(cline, sizeof cline, file) == NULL ) { return 0 ; }

          std::string line2(cline);
          if (line2.size() <= 1) { continue; }
          if (line2[0] == '#') { continue; }
          if (line2[0] == ';') { continue; }

          ss.clear();
          ss.str(line2);

          double x, y;
          ss >> x;
          ss >> y;

          cut->AddPoint(x,y);
          ++ct;
        }
        if (id == ID) { fclose(file); canvas->cd(); cut->Draw("same LP"); return cut; }
        else { delete cut; }
      }

      return 0;
    }
    
    void PrintCut(TCutG *cut) {
      double x,y;
      std::cout << "ID    " << cut->GetN() << std::endl;
      for (int i=0; i<cut->GetN(); ++i) {
        cut->GetPoint(i,x,y);
        std::cout << x << "   " << y << std::endl;
      }
    }
      

  } // namespace Spect
} // namespace GamR
