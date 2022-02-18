#include "MonteCarlo.hh"

#include <TStyle.h>
#include <TSystem.h>

namespace GamR {
namespace TK {

std::shared_ptr<TH2D> MonteCarlo(std::function<std::pair<double, double>(TH1 *, TRandom3 &)> func, TH1 *system,
                                 size_t ntoys, Bool_t draw, const Bool_t weight, TCanvas *c1)
{
   TRandom3 rndgen;
   rndgen.SetSeed(0430204771);

   if (!c1) {
      c1 = new TCanvas("montecarlo", "Monte-Carlo Experiment", 1280, 720);
   }
   gStyle->SetOptStat();

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

   auto pad_input = std::make_unique<TPad>("pad_input", "Experiment", 0, 0, 0.5, 1);
   pad_input->Draw();
   auto pad_results = std::make_unique<TPad>("pad_results", "Observations", 0.5, 0, 1, 1);
   pad_results->Draw();
   auto hist_results = std::make_shared<TH2D>("mc_results", "Monte-Carlo Results", 100, 0, 0, 100, 0, 0);
   hist_results->SetCanExtend(TH1::kAllAxes);
   hist_results->Sumw2();

   for (size_t i = 0; i < ntoys; ++i) {
      TH1 *copy = static_cast<TH1 *>(system->Clone());
      std::pair<double, double> result = func(copy, rndgen);
      if (weight) {
         hist_results->Fill(result.first, result.second, result.second);
      } else {
         hist_results->Fill(result.first, result.second);
      }

      if ((i && (i % 200 == 0)) || i == ntoys) {
         pad_input->cd();
         double min = system->GetMinimum() == 0 ? system->GetMinimum(0) : system->GetMinimum();
         double max = system->GetMaximum() == 0 ? system->GetMaximum(0) : system->GetMaximum();
         int minbin;
         system->GetBinWithContent(min, minbin);
         int maxbin;
         system->GetBinWithContent(max, maxbin);
         copy->SetMinimum(min - 5 * system->GetBinError(minbin));
         copy->SetMaximum(max + 3 * system->GetBinError(maxbin));

         copy->Draw("HIST");

         pad_results->cd();
         // double rxmin = hist_results -> GetXaxis() -> GetXmin();
         // double rxmax = hist_results -> GetXaxis() -> GetXmax();

         // double rymin = hist_results -> GetYaxis() -> GetXmin();
         // double rymax = hist_results -> GetYaxis() -> GetXmax();

         // int dx = static_cast<int>(rxmax - rxmin);
         // int dy = static_cast<int>(rymax - rymin);
         // int square = gcd(dx,dy);
         // hist_results -> GetXaxis() -> SetRangeUser(rxmin, rxmin*square);
         // hist_results -> GetYaxis() -> SetRangeUser(rymin, rymin*square);

         hist_results->Draw("COLZ 0");
         // pad_project -> cd();
         // hist_results -> ProjectionX() -> Draw("HIST");
         UpdateCanvas();
      }
      delete copy;
   }
   return hist_results;
}

/* Tim: this is copy/pasted from one of my macros.  Obviously designed for
   the specific purpose of Monte Carlo fitting ratio functions, but it's easily
   adaptable to be pretty general I think.  Pass it a histogram and any TF1, it
   fetches parameter names, makes a TNtuple, and does the Monte Carlo fit, using
   the parameters of the TF1 as initial guesses and storing the results of each
   iteration in the TNTuple, which is written to disk.

   Obviously heaps that's beyond that though, making pictures etc.

*/
/*
  void monteCarlo_fit(TH1 *hist, TF1 *function, int iterations, const char
  *name, const char *fileName){
  //float start, tau, amplitude, omega, phase;
  const int nParams=function->GetNpar();
  cout << nParams << " parameters" << endl;

  float parameters[nParams];
  float * paramPoint;

  TString s(function->GetParName(0));

  for (int i=1; i<nParams; i++){
  s=s.Append(":");
  s=s.Append(function->GetParName(i));
  }

  cout << s.Data() << endl;

  TFile *outFile=new TFile(fileName, "recreate");

  TNtuple *fits= new TNtuple(name, hist->GetTitle(), s.Data());
  TRandom3 *random = new TRandom3();

  TH1D *fitHist=static_cast<TH1D*>(hist->Clone("fitHist"));
  TH1D *rebinHist;
  TH1D *temp=new TH1D("temp", "Frequency Histogram", 200, 0.47, 0.57);

  int nBins=hist->GetNbinsX();

  TCanvas *simulCanvas=new TCanvas("simulCanvas", "Monte Carlo Simulation", 900,
  450);
  //c1->Divide(2,1);
  TPad *ratiopad=new TPad("ratiopad", "Ratio Function", 0, 0, 0.5, 1);
  ratiopad->Draw();
  TPad *histpad=new TPad("histpad", "Frequency Histogram", 0.5, 0, 1, 1);
  histpad->Draw();

  ratiopad->cd();
  rebinHist = dynamic_cast<TH1D*>(fitHist->Rebin(8, "rebinHist"));
  rebinHist->SetTitle("Ratio Function");
  rebinHist->Scale(1./8.);
  rebinHist->Draw("hist");

  histpad->cd();
  temp->Draw();

  rebinHist->GetXaxis()->SetRangeUser(680, 775);
  rebinHist->SetMaximum(0.15);
  rebinHist->SetMinimum(-0.15);
  rebinHist->SetStats(kFALSE);

  fitHist->GetXaxis()->SetRangeUser(680, 775);
  fitHist->SetMaximum(0.15);
  fitHist->SetMinimum(-0.15);
  fitHist->SetStats(kFALSE);

  for (int i=0; i<iterations; i++){
  //fitHist->Reset();

  TF1 *fitFunc = (TF1*)function->Clone("fitFunc");

  //fill histogram with new data
  for (int bin=1; bin<nBins; bin++) {
  fitHist->SetBinContent(bin, random->Gaus(hist->GetBinContent(bin),
  hist->GetBinError(bin)));
  }

  int fitStat = fitHist->Fit(fitFunc, "RWQ");
  if ( fitStat != 0 ){
  cout << "status is " << fitStat << endl;
  }
  else{
  for (int param=0; param<nParams; param++){
  parameters[param]=fitFunc->GetParameter(param);
  }

  paramPoint=parameters;

  fits->Fill(paramPoint);
  temp->Fill(parameters[3]);

  if (i%100==0){
  ratiopad->cd();
  //rebinHist->Reset();

  rebinHist = dynamic_cast<TH1D*>(fitHist->Rebin(8, "rebinHist"));
  rebinHist->Scale(1./8.);
  rebinHist->SetTitle("Ratio Function");

  rebinHist->GetXaxis()->SetRangeUser(680, 775);
  rebinHist->SetMaximum(0.15);
  rebinHist->SetMinimum(-0.15);
  rebinHist->SetStats(kFALSE);

  rebinHist->Draw("hist");

  fitFunc->Draw("same");

  histpad->cd();
  //temp->Reset();
  //fits->Draw("p3>>temp");
  temp->Draw("E1");

  simulCanvas->Draw();
  simulCanvas->Modified();
  simulCanvas->Update();

  TString gifFrame;

  gifFrame.Form("ratioMonteCarlo%04d.gif",i);

  simulCanvas->Print(gifFrame.Data());
  }

  }

  }

  //:simulCanvas->Print("/home/tjg103/ratioMonteCarlo.gif++");


  fits->Write();

  outFile->Close();
  delete outFile;

  }
*/
} /* namespace TK */
} /* namespace GamR */
