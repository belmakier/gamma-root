#include <iomanip>
#include <iostream>
#include <sstream>

#include <TMinuit.h>
#include <TPaveText.h>
#include <TRandom3.h>

#include <toolkit/MonteCarlo.hh>

#include "TimeWalk.hh"

// ignoring npar, gin, iflag in GlobalChiSquare::doit
// TMinuit expects these extra variables that we don't use
#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace GamR {
namespace Processor {

/**
 * @brief TimeWalk Calibration Processor
 *
 * @param[in] ids Detector IDs.
 * @return TimeWalk
 */
TimeWalk::TimeWalk(std::vector<Int_t> ids) : fDetIds(ids)
{
   // Fit Function String
   // x = E_j
   // [0] = a_j, [1] = b_j, [2] = f_j
   // [3] = a_i, [4] = b_i, [5] = f_i
   // [6] = E_i,ref

   std::string funcstr("([0]/sqrt(x+[1])+[2]) - ([3]/sqrt([6]+[4])+[5])");
   for (const auto &i : fDetIds) {
      for (const auto &j : fDetIds) {
         if (i == j) {
            continue;
         }
         std::string pairing = std::to_string(i) + "_" + std::to_string(j);
         fFits[{i, j}] = std::make_unique<TF1>(("TCF_" + pairing).c_str(), funcstr.c_str(), 0, 4096);
      }
   }

} // TimeWalk::TimeWalk

TimeWalk::~TimeWalk() {}

/**
 * @brief Adds a data set to be processed.
 *
 * @param[in] fn Filename of of ROOT file. Expects output from
 * GamR::Sort::Type::TimeWalkCal
 * @return int Error code: 0 successful, 1 error opening file, 2
 * can't find reference photon in specified file.
 */
Int_t TimeWalk::AddDataSet(std::string fn)
{
   TFile f(fn.c_str());
   if (!f.IsOpen() || f.IsZombie()) {
      return 1;
   }

   GamR::Nucleus::Photon *ref;
   f.GetObject("TC_REF", ref);
   f.Close();

   if (ref) {
      fReference[fn] = std::unique_ptr<GamR::Nucleus::Photon>(ref);
      return 0;
   } else {
      return 2;
   }
}

/**
 * @brief Draws Time Walk graphs.
 *
 * @param[in] c Canvas to draw on.
 * @param[in] fits Draw fits behind graphs
 * @param[in] saveas (optional) save to file
 */
void TimeWalk::Draw(TCanvas *c, Bool_t fits, std::string saveas)
{
   c->Clear();
   c->Divide(fDetIds.size(), fDetIds.size());
   c->SetTitle("Time Walk Calibration Graphs");
   int i = 0;
   int j = 0;
   for (auto &idi : fDetIds) {
      for (auto &idj : fDetIds) {
         if (idi == idj) {
            ++j;
            continue;
         }
         c->cd(i * fDetIds.size() + j + 1);
         // auto mg = std::make_shared<TMultiGraph>("mg", "");
         Bool_t first = kTRUE;
         for (auto &dataset : fReference) {
            auto datafn = dataset.first;
            if (first) {
               fGraphs[datafn][{idi, idj}]->Draw("AP");
               first = kFALSE;
            } else {
               fGraphs[datafn][{idi, idj}]->Draw("P SAME");
            }
         }
         // c -> BuildLegend();
         c->Update();
         ++j;
      }
      ++i;
      j = 0;
   }
   std::vector<Bool_t> equation(fDetIds.size());
   if (fits) {
      i = 0;
      j = 0;
      for (auto &idi : fDetIds) {
         for (auto &idj : fDetIds) {
            if (idi == idj) {
               ++j;
               continue;
            }
            if (!equation[i]) {
               c->cd(i * fDetIds.size() + i + 1);
               TPaveText *pavetext = new TPaveText(0.1, 0.1, 0.9, 0.9);
               pavetext->SetTextFont(53);
               pavetext->SetTextSize(12);
               pavetext->SetTextAlign(11);
               std::stringstream ss;
               ss.precision(10);
               ss << "Detector " << idi;
               pavetext->AddText(ss.str().c_str());
               ss.str("");
               ss << "a_{" << idi << "} = " << fFitResults[{idi, 0}];
               pavetext->AddText(ss.str().c_str());
               ss.str("");
               ss << "b_{" << idi << "} = " << fFitResults[{idi, 1}];
               pavetext->AddText(ss.str().c_str());
               ss.str("");
               ss << "f_{" << idi << "} = " << fFitResults[{idi, 2}];
               pavetext->AddText(ss.str().c_str());
               pavetext->Draw();
               equation[i] = kTRUE;
            }
            c->cd(i * fDetIds.size() + j + 1);
            // auto mg = std::make_shared<TMultiGraph>("mg", "");
            for (auto &dataset : fReference) {
               double xmin;
               double xmax;
               fFits[{idi, idj}]->GetRange(xmin, xmax);
               xmin = fFitResults[{idj, 1}];
               xmin = xmin < 0 ? -1 * xmin : 0;
               fFits[{idi, idj}]->SetRange(xmin + 0.1, xmax);
               fFits[{idi, idj}]->SetLineColorAlpha(1, 0.8);
               fFits[{idi, idj}]->SetLineWidth(1);
               fFits[{idi, idj}]->SetParameter(6, dataset.second->GetEnergy());
               fFits[{idi, idj}]->DrawCopy("SAME");
            }
            // c -> BuildLegend();
            c->Update();
            ++j;
         }
         ++i;
         j = 0;
      }
   }
   if (!saveas.empty()) {
      c->SaveAs(saveas.c_str());
   }
}

/**
 * @brief Add a calibration peak to be used to create a data point
 * in the time walk curve.
 *
 * @param[in] dataset Filename of Data Set, expects output from
 * GamR::Sort::Type::TimeWalkCal
 * @param[in] photon Calibration peak to measure time relative to
 * reference photon.
 * @param[in] time Early/Delay time correction of this peak.
 * Positive corrects for delayed transitions, negative for
 * early.
 * @return int Error code: 0 successful, 1 error opening file, 2
 * can't find reference photon in data set.
 */
Int_t TimeWalk::AddPeak(std::string dataset, GamR::Nucleus::Photon photon, Double_t time)
{
   if (fReference.count(dataset) == 0) {
      int error = AddDataSet(dataset);
      if (error)
         return error;
   } else {
      fRelative[dataset].push_back({photon, time}); // peak, bg, time correction
   }
   return 0;
}

/**
 * @brief Iterating through calibration peaks for each detector
 * pair: calculate the time difference spectrum (with full
 * background subtraction), monte-carlo the first order moment,
 * correct for any early/delay shifts due to lifetimes, to create
 * one data point on the graph.
 *
 * @param ntoys Number of toy experiments to conduct during the
 * Monte-Carlo simulation.
 * @param showmc Shows visualisation of Monte Carlo simulation
 */
void TimeWalk::MakeGraphs(Int_t ntoys, Bool_t showmc)
{
   // Setting up
   TH1::SetDefaultSumw2(kTRUE);
   TCanvas *c1 = new TCanvas("canvas", "First Order Moment", 1280, 720);
   TH2D *pkhist;
   TH2D *bghist;
   std::vector<Double_t> energy, tdiff, energyerr, tdifferr;
   int colour = 0;

   auto mcmean = [](TH1 *h, TRandom3 &rnd) {
      int low = h->GetXaxis()->FindBin(h->GetMean() - 5 * h->GetStdDev());
      int high = h->GetXaxis()->FindBin(h->GetMean() + 5 * h->GetStdDev());
      h->GetXaxis()->SetRange(low, high);
      // higher order iterations
      for (int order = 2; order <= 3; ++order) {
         low = h->GetXaxis()->FindBin(h->GetMean() - order * 5 * h->GetStdDev());
         high = h->GetXaxis()->FindBin(h->GetMean() + order * 5 * h->GetStdDev());
         h->GetXaxis()->SetRange(low, high);
      }
      for (int x = low; x <= high; ++x) {
         Double_t error = h->GetBinError(x);
         Double_t count = h->GetBinContent(x);
         h->SetBinContent(x, rnd.Gaus(count, error));
         h->SetBinError(x, 0);
      }
      double mean = h->GetMean();
      double median;
      double q = 0.5;
      h->GetQuantiles(1, &median, &q);
      return std::pair<double, double>(median, mean);
   };

   // Graph for each data set
   for (const auto &dataset : fReference) {
      auto &datafn = dataset.first;
      auto &refpeak = dataset.second;
      TFile datafile(datafn.c_str());

      Double_t width_refpk = refpeak->GetGate()->GetWidth();
      Double_t width_refbg = refpeak->GetGateBG()->GetWidth();
      std::stringstream ss;

      // Each pairing
      for (auto &i : fDetIds) {
         for (auto &j : fDetIds) {
            if (i == j) {
               continue;
            }
            energy.clear();
            energyerr.clear();
            tdiff.clear();
            tdifferr.clear();
            std::string pairing(std::to_string(i) + "_" + std::to_string(j));

            datafile.GetObject(("P" + pairing).c_str(), pkhist);
            datafile.GetObject(("B" + pairing).c_str(), bghist);

            std::cout << "Generating data points for pairing " << i << " " << j << std::endl;
            for (auto &relative : fRelative[dataset.first]) {
               auto &photon = relative.first;
               auto &correc = relative.second;
               ss.str("");
               ss << pairing << "_" << static_cast<int>(photon.GetEnergy());

               TH1D *pp = photon.GetGate()->ApplyX(pkhist, ss.str().c_str());
               TH1D *bp = photon.GetGate()->ApplyX(bghist, "bg_pk");
               TH1D *pb = photon.GetGateBG()->ApplyX(pkhist, "pk_bg");
               TH1D *bb = photon.GetGateBG()->ApplyX(bghist, "bg_bg");

               Double_t width_pk = photon.GetGate()->GetWidth();
               Double_t width_bg = photon.GetGateBG()->GetWidth();

               // Full subtraction
               pp->Add(pb, -1 * width_refpk / width_bg);
               pp->Add(bp, -1 * width_refbg / width_pk);
               pp->Add(bb, +2 * width_refbg / width_bg);

               // If low stats, ignore it
               if (pp->Integral() < 15) {
                  continue;
               }

               // Fill the data
               // Energy
               energy.push_back(photon.GetEnergy());
               energyerr.push_back(0);

               // HistMean(pp, ntoys)
               c1->Clear();
               auto mcresult = GamR::TK::MonteCarlo(mcmean, pp, ntoys, showmc, kFALSE, c1);

               // Time
               tdiff.push_back(mcresult->GetMean(1) - correc);
               tdifferr.push_back(mcresult->GetStdDev(1));

               // Print back
               std::cout << "Energy:\t" << energy.back();
               std::cout << "\tTime:\t" << tdiff.back() << " +/- " << tdifferr.back();
               std::cout << std::endl;

            } // got data

            // Make the graph
            fGraphs[datafn][{i, j}] = std::make_unique<TGraphErrors>(energy.size(), energy.data(), tdiff.data(),
                                                                     energyerr.data(), tdifferr.data());
            // Title
            ss.str("");
            ss << "TCG_" << pairing;
            fGraphs[datafn][{i, j}]->SetName((ss.str() + "_" + datafn).c_str());

            // Title and xis labels
            ss << " Time Walk Calibration E_{" << i << "}=" << refpeak->GetEnergy() << " [keV]";
            ss << ";Gamma Energy, E_{" << j << "} [keV]";
            ss << ";$\\Delta t = t_{" << i << "} - t_{" << j << "}$ [ps]";
            fGraphs[datafn][{i, j}]->SetTitle(ss.str().c_str());

            // Better Markers
            colour += 1;
            fGraphs[datafn][{i, j}]->SetLineColorAlpha((colour % 9) + 40, 0.9);
            fGraphs[datafn][{i, j}]->SetLineWidth(1);
            fGraphs[datafn][{i, j}]->SetMarkerColorAlpha((colour % 9) + 40, 0.9);
            fGraphs[datafn][{i, j}]->SetMarkerColor(kOpenSquare);
            fGraphs[datafn][{i, j}]->SetMarkerSize(2);

         } // det j
      }    // det i
      datafile.Close();
   } // data set

   this->Draw(c1, kFALSE);

   return;
} // TimeWalk::MakeGraphs

class TimeWalk::GlobalChiSquare {
private:
   static TimeWalk *p;

public:
   GlobalChiSquare(TimeWalk *parent) { p = parent; }

   static void minuit(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
   {
      f = 0;
      for (const auto &dataset : p->fReference) {
         std::string data = dataset.first;

         for (size_t i = 0; i < p->fDetIds.size(); ++i) {
            for (size_t j = 0; j < p->fDetIds.size(); ++j) {
               if (i == j) {
                  continue;
               }
               auto &idi = p->fDetIds[i];
               auto &idj = p->fDetIds[j];
               p->fFits[{idi, idj}]->SetParameter(0, par[j * 3 + 0]); // A_j
               p->fFits[{idi, idj}]->SetParameter(1, par[j * 3 + 1]); // B_j
               p->fFits[{idi, idj}]->SetParameter(2, par[j * 3 + 2]); // f_j

               p->fFits[{idi, idj}]->SetParameter(3, par[i * 3 + 0]); // A_i
               p->fFits[{idi, idj}]->SetParameter(4, par[i * 3 + 1]); // B_i
               p->fFits[{idi, idj}]->SetParameter(5, par[i * 3 + 2]); // f_i

               p->fFits[{idi, idj}]->SetParameter(6, dataset.second->GetEnergy());

               f += p->fGraphs[data][{idi, idj}]->Chisquare(p->fFits[{idi, idj}].get());
            }
         }
      }
   } // end operator()
};
TimeWalk *TimeWalk::GlobalChiSquare::p = nullptr;

/**
 * @brief Conducts a global \f$ \Chi^2 \f$ fit to solve for an absolute
 * time calibration for each detector.
 *
 */
void TimeWalk::Fit()
{
   Int_t npars = 3 * fDetIds.size();
   auto gMinuit = new TMinuit(npars);

   GlobalChiSquare func(this);
   gMinuit->SetFCN(func.minuit);

   Double_t arglist[10];
   arglist[0] = 1;   // ???
   Int_t ierflg = 0; // some error flag ???

   gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
   arglist[0] = 2;
   gMinuit->mnexcm("SET STR", arglist, 1, ierflg);

   /* Ye olde stringstream */
   std::stringstream ss;

   TRandom3 rnd;

   /* SET INITIAL VALUES */
   Int_t parnum = 0;
   ss.str("");
   for (auto &detid : fDetIds) {
      /* Curvature: A */
      ss << "a" << detid;
      gMinuit->mnparm(parnum, ss.str(), 2500, 1, -1e4, 1e4, ierflg);
      ss.str("");
      ++parnum;

      /* Bend point: B */
      ss << "b" << detid;
      gMinuit->mnparm(parnum, ss.str(), -10, 0.01, -1e4, 1e4, ierflg);
      ss.str("");
      ++parnum;

      /* Constant flight time: F */
      ss << "f" << detid;
      gMinuit->mnparm(parnum, ss.str(), 0, 0.1, -1e3, 1e3, ierflg);
      ss.str("");
      ++parnum;

      /* Linear correction: L */
      // ss << "l" << detid;
      // gMinuit -> mnparm(parnum, ss.str(), 0, 0.0001, -0.01, 0.01, ierflg);
      // ss.str(""); ++parnum;
   }
   gMinuit->FixParameter(2); // Fix Flight of Detector 1

   /* MINIMIZE */
   arglist[0] = 100000; // Max Iterations
   arglist[1] = 1;      // Number of sigma max step
   gMinuit->mnexcm("MINIGRAD", arglist, 2, ierflg);
   gMinuit->mnimpr(); // Improve fit by searching for other minima
   gMinuit->mnexcm("HESSE", arglist, 2, ierflg);
   gMinuit->mnexcm("MINOS", arglist, 2, ierflg);

   TCanvas *c1 = new TCanvas("cTCAL", "Time Walk Calibration Fit Results", 1280, 720);
   this->Draw(c1, kTRUE);

   // Print results
   std::cout << "\nFit Results\n";
   double param, err;
   for (size_t i = 0; i < fDetIds.size(); ++i) {
      std::cout << std::endl << "Detector " << fDetIds[i] << std::endl;
      // Curvature
      gMinuit->GetParameter(i * 3 + 0, param, err);
      fFitResults[{fDetIds[i], 0}] = param;
      std::cout << "(([1]+x)-((" << param << "+(y*" << err << "))";

      // Bend point
      gMinuit->GetParameter(i * 3 + 1, param, err);
      fFitResults[{fDetIds[i], 1}] = param;
      std::cout << "/sqrt([0]+(" << param << "+(y*" << err << ")))";

      // Linear correction
      // gMinuit -> GetParameter(i*4+3, param, err);
      // std::cout << "+[0]*(" << param << "+(y*" << err << "))";

      // Flight
      gMinuit->GetParameter(i * 3 + 2, param, err);
      fFitResults[{fDetIds[i], 2}] = param;
      std::cout << "+(" << param << "+(y*" << err << "))))";
      std::cout << std::endl;
   }

   std::cout << "All Done" << std::endl;
   return;
} // TimeWalk::Fit

} // namespace Processor
} // namespace GamR
