#include <iostream>

#include <TROOT.h>
#include <TColor.h>
#include <TFile.h>
#include <TKey.h>
#include <TLegend.h>

#include "Display.hh"

#include <toolkit/Gate.hh>
#include <utils/Utilities.hh>

namespace GamR {
  namespace Spect {
    std::vector<TH1*> List1DSpectra(bool quiet/*=false*/) {
      int iHist=0;
      std::vector<TH1*> spectra;
      for (int i=0; i<(gDirectory->GetList()->GetSize()); ++i) {
        TObject *obj = gDirectory->GetList()->At(i);
        if (!obj->InheritsFrom("TH1") || obj->InheritsFrom("TH2") || obj->InheritsFrom("TH3")) continue;
        if (!quiet) {
          std::cout << iHist << "    " << obj->GetName() << std::endl;
        }
        spectra.push_back((TH1*)obj);
        ++iHist;
      }
      
      for (int i=0; i<(gDirectory->GetListOfKeys()->GetSize()); ++i) {
        TKey *key = static_cast<TKey*>(gDirectory->GetListOfKeys()->At(i));
        TClass *cl = gROOT->GetClass(key->GetClassName());
        if (!cl->InheritsFrom("TH1") || cl->InheritsFrom("TH2") || cl->InheritsFrom("TH3")) continue;
        if (!quiet) {
          std::cout << iHist << "    " << key->GetName() << std::endl;
        }
        //check if already in memory
        int ex = 0;
        for (int j=0; j<(gDirectory->GetList()->GetSize()); ++j) {
          if (ex == 1) { break; }
          if ((std::string)(gDirectory->GetList()->At(j)->GetName()) == (std::string)(key->GetName())) {
            //spectra.push_back((TH1*)gDirectory->GetList()->At(j));
            ex = 1;
          }
        }
        if (ex == 0) {
          spectra.push_back((TH1*)key->ReadObj());
        }
        ++iHist;
      }
      return spectra;
    }

    std::vector<TH2*> List2DSpectra(bool quiet/*=false*/) {
      int iHist=0;
      std::vector<TH2*> spectra;
      for (int i=0; i<(gDirectory->GetListOfKeys()->GetSize()); ++i) {
        TKey *key = static_cast<TKey*>(gDirectory->GetListOfKeys()->At(i));
        TClass *cl = gROOT->GetClass(key->GetClassName());
        if (cl->InheritsFrom("TH2")) {
          if (!quiet) {
            std::cout << iHist << "    " << key->GetName() << std::endl;
          }
          //check if already in memory
          int ex = 0;
          for (int j=0; j<(gDirectory->GetList()->GetSize()); ++j) {
            if (ex == 1) { break; }
            if ((std::string)(gDirectory->GetList()->At(j)->GetName()) == (std::string)(key->GetName())) {
              spectra.push_back((TH2*)gDirectory->GetList()->At(j));
              ex = 1;
            }
          }
          if (ex == 0) {
            spectra.push_back((TH2*)key->ReadObj());
          }
          ++iHist;
        }
      }
      return spectra;
    }

    void Draw(int i, Option_t *option /*= "hist"*/) {
      auto spectra = List1DSpectra(true);
      spectra[i]->Draw(option);
    }
    void Draw2D(int i, Option_t *option /*= "colz2"*/) {
      auto spectra = List2DSpectra(true);
      spectra[i]->Draw(option);
    }
    
    void OverlaySpectra(std::vector<int> display_indexes,  TCanvas *canvas, Option_t *option) {
      auto spectra = List1DSpectra(true);
      std::vector<TH1*> display_spectra;
      for (auto &i : display_indexes) {
        display_spectra.push_back(spectra[i]);
      }
      OverlaySpectra(display_spectra, canvas, option);
    }
    
    void OverlaySpectra(int iStart, int iStop, TCanvas *canvas, Option_t *option) {
      auto spectra = List1DSpectra(true);
      std::vector<TH1*> display_spectra;
      for (int i=iStart; i<=iStop; ++i) {
        display_spectra.push_back(spectra[i]);
      }
      OverlaySpectra(display_spectra, canvas, option);
    }      
    
    void OverlaySpectra(std::vector<TH1*> hists, TCanvas *canvas, Option_t *option) {
      if (!canvas) { if (gPad) { canvas = gPad->GetCanvas(); } else { canvas = new TCanvas(); } }
      canvas->cd();
      canvas->Clear();

      //std::vector<int> colors = {602, 632, 419, 616, 1, 435, 417, 884};

      std::vector<std::string> colors_hex = {"#000076",
        "#ff1c00",
        "#00b500",
        "#008bdf",
        "#fa4900",
        "#9b37dc",
        "#e9d100",
        "#ff008c"};

      std::vector<int> colors;
      for (int i=0; i<(int)colors_hex.size(); ++i) {
        colors.push_back(TColor::GetColor(colors_hex[i].c_str()));
      }

      TLegend *leg = new TLegend(0.1, 0.7, 0.3, 0.9);
      for (int i=0; i<(int)hists.size(); ++i) {
        TH1 *hist = hists[i];
        hist->SetLineColor(colors[i%colors.size()]);
        leg->AddEntry(hist, hist->GetName(), "l");
        hist->GetXaxis()->UnZoom();
        if (i==0) { hist->Draw(option); }
        else { hist->Draw(((std::string)option+" same").c_str()); }
      }
      leg->Draw();
    }

    void OverlaySpectra(TH2 *hist, int iStart, int iStop, Option_t *option) {
      std::vector<TH1*> hists;
      for (int i=iStart; i<=iStop; ++i) {
        std::string name = (std::string)hist->GetName()+"_px_"+std::to_string(i);
        hists.push_back((TH1*)hist->ProjectionX(name.c_str(), i,i));
      }
      OverlaySpectra(hists);
    }

    void OverlaySpectra(TH2 *hist, std::vector<int> indices, Option_t *option) {
      std::vector<TH1*> hists;
      for (int i=0; i<indices.size(); ++i) {
        int indx = indices[i];
        std::string name = (std::string)hist->GetName()+"_px_"+std::to_string(indx);
        hists.push_back((TH1*)hist->ProjectionX(name.c_str(), indx,indx));
      }
      OverlaySpectra(hists);
    }

    void OverlaySpectra(int i2D, int iStart, int iStop, Option_t *option) {
      auto spectra = List2DSpectra(true);
      OverlaySpectra(spectra[i2D], iStart, iStop, option);
    }

    void OverlaySpectra(std::vector<std::string> files, std::string name, int iX, Option_t *option) {
      std::vector<TH1*> hists;
      for (int iFile = 0; iFile<files.size(); ++iFile) {
        TFile *file = new TFile(files[iFile].c_str());
        TH2D* hist2 = (TH2D*)file->Get<TH2>(name.c_str());
        TH1* hist = (TH1*)hist2->ProjectionX(files[iFile].substr(0, files[iFile].size()-5).c_str(), iX, iX);
        hists.push_back(hist);
      }
      OverlaySpectra(hists);
    }

    void OverlaySpectra(std::vector<std::string> files, std::string name, Option_t *option) {
      std::vector<TH1*> hists;
      for (int iFile = 0; iFile<files.size(); ++iFile) {
        TFile *file = new TFile(files[iFile].c_str());
        TH1* hist = (TH1*)file->Get<TH1>(name.c_str());
        hist->SetName(files[iFile].substr(0, files[iFile].size()-5).c_str());
        hists.push_back(hist);
      }
      OverlaySpectra(hists);
    }
    
    void StackSpectra(std::vector<int> display_indexes,  TCanvas *canvas, Option_t *option) {
      auto spectra = List1DSpectra(true);
      std::vector<TH1*> display_spectra;
      for (auto &i : display_indexes) {
        display_spectra.push_back(spectra[i]);
      }
      StackSpectra(display_spectra, canvas, option);
    }
    
    void StackSpectra(int iStart, int iStop, TCanvas *canvas, Option_t *option) {
      auto spectra = List1DSpectra(true);
      std::vector<TH1*> display_spectra;
      for (int i=iStart; i<=iStop; ++i) {
        display_spectra.push_back(spectra[i]);
      }
      StackSpectra(display_spectra, canvas, option);
    }      

    void StackSpectra(std::vector<TH1*> hists, TCanvas *canvas, Option_t *option) {
      if (!canvas) { if (gPad) { canvas = gPad->GetCanvas(); } else { canvas = new TCanvas(); } }
      canvas->cd();
      canvas->Clear();

      int num_hists = hists.size();
      int nx = 0;
      int ny = 0;
      if (hists.size() < 2 ) { nx = 1; ny = 1; }
      else {
        //work out dimensions to divide into
        nx = (int)(std::sqrt((double)num_hists));
        ny = (int)((double)(num_hists - 1)/(double)(nx) + 1);
      }
      canvas->Divide(nx, ny, 0, 0);

      for (int i=0; i<num_hists; ++i) {
        TH1 *hist = hists[i];
        hist->GetXaxis()->UnZoom();
        canvas->cd(i+1);
        hist->Draw(option);
      }
      canvas->cd();
    }

    void StackSpectra(TH2 *hist, int iStart, int iStop, Option_t *option) {
      std::vector<TH1*> hists;
      for (int i=iStart; i<=iStop; ++i) {
        std::string name = (std::string)hist->GetName()+"_px_"+std::to_string(i);
        hists.push_back((TH1*)hist->ProjectionX(name.c_str(), i,i));
      }
      StackSpectra(hists);
    }

    void StackSpectra(int i2D, int iStart, int iStop, Option_t *option) {
      auto spectra = List2DSpectra(true);
      StackSpectra(spectra[i2D], iStart, iStop, option);
    }

    void StackSpectra(std::vector<std::string> files, std::string name, int iX, Option_t *option) {
      std::vector<TH1*> hists;
      for (int iFile = 0; iFile<files.size(); ++iFile) {
        TFile *file = new TFile(files[iFile].c_str());
        TH2D* hist2 = (TH2D*)file->Get<TH2>(name.c_str());
        TH1* hist = (TH1*)hist2->ProjectionX(files[iFile].substr(0, files[iFile].size()-5).c_str(), iX, iX);
        hists.push_back(hist);
      }
      StackSpectra(hists);
    }

    void StackSpectra(std::vector<std::string> files, std::string name, Option_t *option) {
      std::vector<TH1*> hists;
      for (int iFile = 0; iFile<files.size(); ++iFile) {
        TFile *file = new TFile(files[iFile].c_str());
        TH1* hist = (TH1*)file->Get<TH1>(name.c_str());
        hist->SetName(files[iFile].substr(0, files[iFile].size()-5).c_str());
        hists.push_back(hist);
      }
      StackSpectra(hists);
    }
    
    void LinAll(TVirtualPad *canvas) {
      if (!canvas) { if (!gPad) { return; } canvas = gPad; }

      int nPads = GamR::Utils::GetNPads(canvas);
      if (!nPads) {
        canvas->SetLogy(0);
      }
      
      for (int i=0; i<nPads; ++i) {
        canvas->cd(i+1);
        LinAll(canvas->cd(i+1));
      }
      canvas->Modified();
      canvas->cd();      
    }

    void LogAll(TVirtualPad *canvas) {
      if (!canvas) { if (!gPad) { return; } canvas = gPad; }

      int nPads = GamR::Utils::GetNPads(canvas);
      
      if (!nPads) {
        canvas->SetLogy(1);
      }
      
      for (int i=0; i<nPads; ++i) {
        canvas->cd(i+1);
        LogAll(canvas->cd(i+1));
      }
      canvas->Modified();
      canvas->cd();
    }

    void ZoomAllX(double low, double high, TVirtualPad *canvas) {
      if (!canvas) { if (!gPad) { return; } canvas = gPad; }

      int nPads = GamR::Utils::GetNPads(canvas);
      
      if (!nPads) {
        TH1D *hist = GamR::Utils::GetHist1D(canvas);
        if (hist) {
          hist->GetXaxis()->SetRangeUser(low, high);
        }
        canvas->Modified();
      }
      
      for (int i=0; i<nPads; ++i) {
        canvas->cd(i+1);
        ZoomAllX(low, high, canvas->cd(i+1));
      }
      canvas->Modified();
      canvas->cd();
    }

    void ZoomAllY(double low, double high, TVirtualPad *canvas) {
      if (!canvas) { if (!gPad) { return; } canvas = gPad; }

      int nPads = GamR::Utils::GetNPads(canvas);
      
      if (!nPads) {
        TH1D *hist = GamR::Utils::GetHist1D(canvas);
        if (hist) {
          hist->GetYaxis()->SetRangeUser(low, high);
        }
        canvas->Modified();
      }
      
      for (int i=0; i<nPads; ++i) {
        canvas->cd(i+1);
        ZoomAllY(low, high, canvas->cd(i+1));
      }
      canvas->Modified();
      canvas->cd();
    }

    void UnZoomAllX(TVirtualPad *canvas) {
      if (!canvas) { if (!gPad) { return; } canvas = gPad; }

      int nPads = GamR::Utils::GetNPads(canvas);
      
      if (!nPads) {
        TH1D *hist = GamR::Utils::GetHist1D(canvas);
        if (hist) {
          hist->GetXaxis()->UnZoom();
          canvas->Modified();
        }
        else {
          TH2D *hist2 = GamR::Utils::GetHist2D(canvas);
          if (hist2) {
            hist2->GetXaxis()->UnZoom();
            canvas->Modified();
          }
        }
      }      
      
      for (int i=0; i<nPads; ++i) {
        canvas->cd(i+1);
        UnZoomAllX(canvas->cd(i+1));
      }
      canvas->Modified();
      canvas->cd();
    }

    void UnZoomAllY(TVirtualPad *canvas) {
      if (!canvas) { if (!gPad) { return; } canvas = gPad; }

      int nPads = GamR::Utils::GetNPads(canvas);
      
      if (!nPads) {
        TH1D *hist = GamR::Utils::GetHist1D(canvas);
        if (hist) {
          hist->GetYaxis()->UnZoom();
          canvas->Modified();
        }
        else {
          TH2D *hist2 = GamR::Utils::GetHist2D(canvas);
          if (hist2) {
            hist2->GetYaxis()->UnZoom();
            canvas->Modified();
          }
        }
      }
      
      for (int i=0; i<nPads; ++i) {
        canvas->cd(i+1);
        UnZoomAllY(canvas->cd(i+1));
      }
      canvas->Modified();
      canvas->cd();
    }

    void NormSpectra(TVirtualPad *canvas, Option_t *option) {
      if (!canvas) { if (gPad) { canvas = gPad->GetCanvas(); } else { std::cout << "No active canvas" << std::endl; return; } }

      TString opts(option);
      opts.ToLower();
      
      std::vector<TH1D*> spectra = Utils::GetHists1D(canvas);
      for (int i=0; i<spectra.size(); ++i) {
        printf("%i     %s\n", i, spectra[i]->GetName());
      }
      std::cout << "Enter normalising spectrum: ";
      int ind;
      std::cin >> ind;
      TH1D* norm_hist = spectra[ind];
      if (opts.Contains("m")) {
        for (int i=0; i<spectra.size(); ++i) {
          if (i != ind) {
            double scale = (double)norm_hist->GetMaximum()/(double)spectra[i]->GetMaximum();
            spectra[i]->Scale(scale);
          }
        }
      }
      else {
        GamR::TK::Gate gate;
        gate.SetGate(canvas, "x");
        for (int i=0; i<spectra.size(); ++i) {
          if (i != ind) {
            gate.Norm(spectra[i], norm_hist);
          }
        }
      }
      canvas->Update();        
    }

    void NormSpectraBackSub(TVirtualPad *canvas) {
      if (!canvas) { if (gPad) { canvas = gPad->GetCanvas(); } else { std::cout << "No active canvas" << std::endl; return; } }
      std::vector<TH1D*> spectra = Utils::GetHists1D(canvas);
      for (int i=0; i<spectra.size(); ++i) {
        printf("%i     %s\n", i, spectra[i]->GetName());
      }
      std::cout << "Enter normalising spectrum: ";
      int ind;
      std::cin >> ind;
      TH1D* norm_hist = spectra[ind];
      std::cout << "Set peak region: " << std::endl;
      GamR::TK::Gate gate;
      gate.SetGate(canvas, "x");
      std::cout << "Set background region: " << std::endl;
      GamR::TK::Gate back;
      back.SetGate(canvas, "x");
      for (int i=0; i<spectra.size(); ++i) {
        gate.NormBackSub(spectra[i], norm_hist, back);
      }
      canvas->Update();        
    }
    
    void Rename(TVirtualPad *canvas) {
      if (!canvas) { if (gPad) { canvas = gPad->GetCanvas(); } else { std::cout << "No active canvas" << std::endl; return; } }
      std::vector<TH1D*> spectra = Utils::GetHists1D(canvas);
      int ind = 0;
      if (spectra.size() > 1) {
        for (int i=0; i<spectra.size(); ++i) {
          printf("%i     %s\n", i, spectra[i]->GetName());
        }
        std::cout << "Enter spectrum to rename: ";
        std::cin >> ind;
      }
      TH1D* hist = spectra[ind];
      std::cout << "Enter new name: ";
      std::string name;
      std::cin >> name;
      spectra[ind]->SetName(name.c_str());
      return;
    }        
  }
}

