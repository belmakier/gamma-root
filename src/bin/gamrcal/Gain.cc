/* STD */
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

/* ROOT */
#include <TCanvas.h>
#include <TFitResult.h>
#include <TGraph.h>
#include <TPaveText.h>
#include <TSpectrum.h>
#include <TSystem.h>

/* GAMR */
#include "Gain.hh"

namespace GamR {
namespace TK {

Int_t GainMatchEnergy(TH1 *spec1, TH1 *spec2, std::vector<Double_t> &pars, bool draw, UInt_t target, std::string outfn,
                      Double_t step, TCanvas *c1)
{
   if (!pars.size()) {
      std::cout << "ERROR: parameter vector should have some size. use resize(n)." << std::endl;
      return -1;
   }
   if (step > 1 || step < 0) {
      std::cout << "ERROR: step should be between 0 and 1" << std::endl;
      return -1;
   }
   if (!c1) {
      c1 = new TCanvas("gainmatchenergy", "Gain Match: Energy", 1280, 720);
   }

   auto UpdateCanvas = [&]() {
      c1->Modified();
      c1->Update();
      c1->Draw();
      gSystem->ProcessEvents();
   };

   UpdateCanvas();

   if (draw) {
      c1->SetBatch(kFALSE);
   } else {
      c1->SetBatch(kTRUE);
   }
   // xlo, ylo, xhi, yhi
   TPad *padspec1 = new TPad("padspec1", "Spectrum 1", 0.0, 0.5, 0.6, 1.0);
   padspec1->Draw();
   padspec1->SetGrid(); // Top left
   TPad *padspec2 = new TPad("padspec2", "Spectrum 2", 0.0, 0.0, 0.6, 0.5);
   padspec2->Draw();
   padspec2->SetGrid(); // Bottom left
   TPad *padgraph = new TPad("padgraph", "Peak Correlation", 0.6, 0.3, 1.0, 1.0);
   padgraph->Draw();
   padgraph->SetGrid();
   padgraph->SetLeftMargin(0.15); // Top Right
   TPad *padtext = new TPad("padtext", "Fit Results", 0.6, 0.0, 1.0, 0.3);
   padtext->Draw(); // Top Right
   TSpectrum analyser;

   UInt_t nspec1 = 1;
   Double_t thresh1 = 0.05;
   UInt_t nspec2 = 0;
   Double_t thresh2 = 0.05;
   int nsigma1 = 3;
   int nsigma2 = 3;

   std::vector<Double_t> peaks1(target);
   std::vector<Double_t> peaks2(target);

   // Graph to display detected
   TGraph graph((nspec1 > nspec2) ? nspec2 : nspec1, peaks1.data(), peaks2.data());
   graph.SetMarkerStyle(21);
   graph.SetTitle("Peak positions");
   graph.GetXaxis()->SetTitle(spec1->GetTitle());
   graph.GetYaxis()->SetTitle(spec2->GetTitle());

   Int_t steps = 0;
   while (nspec1 != target or nspec2 != target) {
      if (nspec1 < target) {
         thresh1 *= step;
      } else if (nspec1 > target) {
         thresh1 *= (1 + step);
      }
      if (nspec2 < target) {
         thresh2 *= step;
      } else if (nspec2 > target) {
         thresh2 *= (1 + step);
         thresh2 = (nspec2 > nspec1) ? thresh2 : (1 + step) * thresh2;
      }

      if (thresh1 < 0.002 || thresh2 < 0.002) {
         std::cout << "hit threshold limit (0.002) on search, try lower target." << std::endl;
         break;
      }
      // search
      bool update = false;
      // spectrum 1
      nspec1 = analyser.Search(spec1, nsigma1, "nodraw", thresh1);
      if (nspec1 != peaks1.size() || !steps) {
         peaks1.clear();
         peaks1.insert(peaks1.begin(), analyser.GetPositionX(), analyser.GetPositionX() + nspec1);
         std::sort(peaks1.begin(), peaks1.end());
         update = true;
      }
      // spectrum 2
      nspec2 = analyser.Search(spec2, nsigma2, "nodraw", thresh2);
      if (nspec2 != peaks2.size() || !steps) {
         peaks2.clear();
         peaks2.insert(peaks2.begin(), analyser.GetPositionX(), analyser.GetPositionX() + nspec2);
         std::sort(peaks2.begin(), peaks2.end());
         update = true;
      }

      if (update || !steps) {
         padspec1->cd();
         nspec1 = analyser.Search(spec1, nsigma1, "", thresh1);

         padspec2->cd();
         nspec2 = analyser.Search(spec2, nsigma2, "", thresh2);

         padgraph->cd();
         graph.DrawGraph((nspec1 > nspec2) ? nspec2 : nspec1, peaks1.data(), peaks2.data(), "AP");
         UpdateCanvas();
      }
      ++steps;
   } // Done searching for peaks

   if (nspec1 != nspec2) {
      std::cout << "num peaks found in spec1 != spec2 ... " << nspec1 << "!=" << nspec2 << std::endl;
      steps *= -1;
   }

   // Lambda functions

   auto MakeCalibration = [&pars, &padgraph, &spec1, &spec2](std::vector<double> uncal, std::vector<double> cal) {
      padgraph->cd();
      auto maxn = uncal.size() > cal.size() ? uncal.size() : cal.size();
      TGraph *calgr = new TGraph(maxn, uncal.data(), cal.data());
      // calgr -> LeastSquareFit(pars.size(), pars.data());
      TF1 *calfunc = new TF1("cal", ("pol" + std::to_string(pars.size() - 1)).c_str(), 0, 1.1 * uncal.back());
      calgr->Fit(calfunc);
      pars.assign(calfunc->GetParameters(), calfunc->GetParameters() + pars.size());

      // calfunc -> SetParameters(pars.data());
      // Pretty
      calgr->SetMarkerStyle(21);
      calgr->SetTitle("Peak positions");
      calgr->GetXaxis()->SetTitle(spec1->GetTitle());
      calgr->GetYaxis()->SetTitle(spec2->GetTitle());
      calgr->Draw("AP");
      // And the function
      calfunc->Draw("SAME");
   };

   auto UpdateFitText = [&]() {
      // The text
      padtext->cd();
      padtext->Clear();
      TPaveText *pavetext = new TPaveText(0.1, 0.1, 0.9, 0.9); // margins low / high in %
      pavetext->SetTextFont(53);
      pavetext->SetTextSize(18);
      std::stringstream ss;
      ss << "Polynomial order " << pars.size() - 1;
      pavetext->AddText(ss.str().c_str());
      for (size_t i = 0; i < pars.size(); ++i) {
         ss.str("");
         ss << "p_{" << i << "} = " << pars[i];
         pavetext->AddText(ss.str().c_str());
      }
      pavetext->Draw();
   };

   MakeCalibration(peaks1, peaks2);
   UpdateFitText();
   UpdateCanvas();

   // If all else fails, let's go manual -- else return here

   std::string input("");
   while (true) {
      std::cout << std::endl << "Proceed manually? [y/n] ";
      std::getline(std::cin, input);

      if (input == "y")
         break;
      if (input == "n") {
         if (outfn != "") {
            c1->SaveAs(outfn.c_str());
         }
         return steps;
      }
      std::cout << "Please answer y or n" << std::endl;
   }

   // Lambda helper
   auto PrintVector = [](std::vector<double> vec) {
      for (auto i : vec)
         std::cout << i << ", ";
      std::cout << std::endl;
   };

   while (true) {
      std::vector<Double_t> accepted_uncal;
      std::vector<std::unique_ptr<TH1>> accepted_uncal_hists;

      std::vector<Double_t> accepted_cal;
      std::vector<std::unique_ptr<TH1>> accepted_cal_hists;

      // First go through the uncalibrated spectrum.

      padspec1->cd();
      padspec1->Clear();
      spec1->Draw();

      for (size_t n = 0; n < peaks1.size();) {
         auto &X = peaks1[n];
         float window = 10;

         padspec1->cd();
         auto highlighter = std::unique_ptr<TH1>(static_cast<TH1 *>(spec1->Clone()));
         highlighter->SetFillColor(kMagenta);
         highlighter->GetXaxis()->SetRangeUser(X - window, X + window);
         highlighter->Draw("SAME");

         auto zoomed = std::unique_ptr<TH1>(static_cast<TH1 *>(spec1->Clone()));
         zoomed->SetFillColor(kBlue);
         zoomed->SetFillStyle(3001);
         zoomed->GetXaxis()->SetRangeUser(X - 20 * window, X + 20 * window);
         zoomed->Draw("SAME");

         padgraph->cd();
         zoomed->Draw();
         highlighter->Draw("SAME");

         // perm highlighter
         accepted_uncal_hists.push_back(std::unique_ptr<TH1>(static_cast<TH1 *>(spec1->Clone(""))));

         UpdateCanvas();

         while (true) {
            UpdateCanvas();
            std::cout << "Accept peak at " << X << " [y/n/z/u/p] ";
            std::getline(std::cin, input);

            if (input == "p") {
               std::cout << "Raw Histogram: " << accepted_uncal.size() << std::endl;
               PrintVector(accepted_uncal);
               std::cout << "   Calibrated: " << accepted_cal.size() << std::endl;
               PrintVector(accepted_cal);
               break;
            } else if (input == "u") {
               if (n > 0) {
                  accepted_uncal.pop_back();
                  accepted_uncal_hists.pop_back();
                  accepted_uncal_hists.pop_back();
                  std::cout << "UNDO!" << std::endl;
                  --n;
               }
               break;
            } else if (input == "z") {
               window *= 0.5;
               padgraph->cd();
               padgraph->Clear();
               highlighter->GetXaxis()->SetRangeUser(X - window, X + window);
               zoomed->GetXaxis()->SetRangeUser(X - 15 * window, X + 15 * window);
               zoomed->Draw();
               highlighter->Draw("SAME");
               UpdateCanvas();
            } else if (input == "y") {
               accepted_uncal.push_back(X);
               padspec1->cd();
               auto &accepted = accepted_uncal_hists.back();
               accepted->SetFillColor(kGreen);
               accepted->GetXaxis()->SetRangeUser(X - window, X + window);
               accepted->Draw("SAME");
               UpdateCanvas();
               ++n;
               break;
            } else if (input == "n") {
               ++n;
               break;
            } else {
               std::cout << "Please answer y or n" << std::endl;
            }
         }
      } // for peaks1

      // Now the calibrated histograms

      padspec2->cd();
      padspec2->Clear();
      spec2->Draw();

      for (size_t n = 0; n < peaks2.size();) {
         auto &X = peaks2[n];
         float window = 10;

         padspec2->cd();
         auto highlighter = std::unique_ptr<TH1>(static_cast<TH1 *>(spec2->Clone()));
         highlighter->SetFillColor(kMagenta);
         highlighter->GetXaxis()->SetRangeUser(X - window, X + window);
         highlighter->Draw("SAME");

         auto zoomed = std::unique_ptr<TH1>(static_cast<TH1 *>(spec2->Clone()));
         zoomed->SetFillColor(kBlue);
         zoomed->SetFillStyle(3001);
         zoomed->GetXaxis()->SetRangeUser(X - 20 * window, X + 20 * window);
         zoomed->Draw("SAME");

         padgraph->cd();
         zoomed->Draw();
         highlighter->Draw("SAME");

         // perm highlighter
         accepted_cal_hists.push_back(std::unique_ptr<TH1>(static_cast<TH1 *>(spec2->Clone(""))));
         UpdateCanvas();

         while (true) {
            UpdateCanvas();
            std::cout << "Accept peak at " << X << " [y/n/z/u/p] ";
            std::getline(std::cin, input);

            if (input == "p") {
               std::cout << "Raw Histogram: " << accepted_uncal.size() << std::endl;
               PrintVector(accepted_uncal);
               std::cout << "   Calibrated: " << accepted_cal.size() << std::endl;
               PrintVector(accepted_cal);
               break;
            } else if (input == "u") {
               if (n > 0) {
                  accepted_cal.pop_back();
                  accepted_cal_hists.pop_back();
                  accepted_cal_hists.pop_back();
                  std::cout << "UNDO!" << std::endl;
                  --n;
               }
               break;
            } else if (input == "z") {
               window *= 0.5;
               padgraph->cd();
               padgraph->Clear();
               highlighter->GetXaxis()->SetRangeUser(X - window, X + window);
               zoomed->GetXaxis()->SetRangeUser(X - 15 * window, X + 15 * window);
               zoomed->Draw();
               highlighter->Draw("SAME");
               UpdateCanvas();
            } else if (input == "y") {
               accepted_cal.push_back(X);
               padspec2->cd();
               auto &accepted = accepted_cal_hists.back();
               accepted->SetFillColor(kGreen);
               accepted->GetXaxis()->SetRangeUser(X - window, X + window);
               accepted->Draw("SAME");
               UpdateCanvas();
               ++n;
               break;
            } else if (input == "n") {
               ++n;
               break;
            } else {
               std::cout << "Please answer y or n" << std::endl;
            }
         }
      } // for peaks1

      // All selected, fit

      MakeCalibration(accepted_uncal, accepted_cal);
      UpdateFitText();
      UpdateCanvas();

      std::cout << "Raw Histogram: ";
      PrintVector(accepted_uncal);
      std::cout << "   Calibrated: ";
      PrintVector(accepted_cal);

      std::cout << std::endl << "Restart? [y/n] ";
      std::getline(std::cin, input);

      if (input == "y")
         continue;
      else if (input == "n") {
         if (outfn != "") {
            c1->SaveAs(outfn.c_str());
         }
         return 0;
      }
   }

   if (outfn != "") {
      c1->SaveAs(outfn.c_str());
   }
   return 0;
}

} // namespace TK
} // namespace GamR
