#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <TApplication.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TTree.h>

/* Vendor */
#include <args/args.hxx>

#include "Gain.hh"

int main(int argc, char *argv[])
{
   args::ArgumentParser parser("GammaROOT Calibration Helper for RawTree",
                               "Aqeel Akber <aqeel.akber@anu.edu.au>\n"
                               "Contribute! <i.believe.in.you@yourdesk.io>");
   args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

   args::Group parser_io(parser, "Input / Output", args::Group::Validators::All);
   args::ValueFlag<std::string> infilename(parser_io, "raw.root", "RawTree ROOT file.", {'i'});
   args::ValueFlag<std::string> inbranchname(parser_io, "branch", "RawTree branch name", {'b'});
   args::ValueFlag<std::string> targetfilename(parser_io, "targets.root", "Targets ROOT file.", {'t'});
   args::ValueFlag<std::string> targethistname(parser_io, "calhist", "Target histogram name", {'c'});
   args::ValueFlag<std::string> outfilename(parser_io, "output.pdf", "Output graphic.", {'o'});

   args::Group parser_sort(parser, "Raw sort out parameters");
   args::ValueFlag<std::string> cutstring(parser_sort, "", "Cut string", {'C'});

   args::Group parser_tune(parser, "Peak search parameters");
   args::ValueFlag<Int_t> npeaks(parser_tune, "5", "Minimum target number of peaks", {'p', "npeaks"}, 5);
   args::ValueFlag<Long64_t> xlow(parser_tune, "2", "Target X low inclusive", {'x', "xlo"}, 2);
   args::ValueFlag<Long64_t> xhigh(parser_tune, "4000", "Target X high inclusive", {'X', "xhi"}, 4000);

   args::Group parser_fit(parser, "Fitting options");
   args::ValueFlag<UInt_t> polyorder(parser_fit, "2", "Polynomial order [0=constant]", {'n', "poly"}, 2);

   try {
      parser.ParseCLI(argc, argv);
   } catch (args::Help) {
      std::cout << parser;
      return 0;
   } catch (args::ParseError e) {
      std::cerr << e.what() << std::endl;
      std::cerr << parser;
      return 1;
   } catch (args::ValidationError e) {
      std::cerr << e.what() << std::endl;
      std::cerr << parser;
      return 1;
   }
   // gErrorIgnoreLevel = kWarning;
   TApplication theApp("gamrcal", 0, 0);

   auto infile = new TFile(infilename.Get().c_str());

   if (infile->IsZombie() || !infile->IsOpen()) {
      std::cerr << "Error opening input file" << std::endl;
      return 1;
   }

   auto rawtree = new TTree;
   infile->GetObject("RawTree", rawtree);

   auto targetfile = new TFile(targetfilename.Get().c_str());
   if (infile->IsZombie() || !infile->IsOpen()) {
      std::cerr << "Error opening target file" << std::endl;
      return 1;
   }

   auto targethist = new TH1D;
   targetfile->GetObject(targethistname.Get().c_str(), targethist);
   targethist->GetXaxis()->SetRangeUser(xlow.Get(), xhigh.Get());
   TCanvas c("gainmatchenergy", "Gain Match: Energy", 1280, 720);
   c.Draw();

   // Generate histogram from tree
   // Ignoring Channel 0 and 4096
   auto rawhist = new TH1D((inbranchname.Get() + "_hist").c_str(),
                           (infilename.Get() + " >> " + inbranchname.Get()).c_str(), 4096, 0, 4096);

   rawtree->Draw((inbranchname.Get() + ">>" + inbranchname.Get() + "_hist").c_str(), cutstring.Get().c_str());

   std::vector<Double_t> pars(polyorder.Get() + 1);
   auto n = GamR::TK::GainMatchEnergy(rawhist, targethist, pars, kTRUE, npeaks.Get(), outfilename.Get(), 0.98, &c);
   int order = 0;
   std::stringstream ss;
   for (const auto &p : pars) {
      ss << ((p < 0) ? std::to_string(p).insert(1, "(") : "+(" + std::to_string(p));
      if (order) {
         ss << "*([0]+x)";
         if (order > 1) {
            ss << "^" << order << ")";
         }
      }
      ss << ")";
      ++order;
   }
   std::cout << ss.str() << std::endl;

   // theApp.Run();

   return n;
}
