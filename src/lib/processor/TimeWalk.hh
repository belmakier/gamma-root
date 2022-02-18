#ifndef GAMR_PROCESSOR_TIMEWALK_HH
#define GAMR_PROCESSOR_TIMEWALK_HH

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <Rtypes.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TH2.h>
#include <TRandom3.h>

#include <nucleus/Photon.hh>

namespace GamR {
namespace Processor {

class TimeWalk {
private:
   std::vector<Int_t> fDetIds;
   std::map<std::pair<Int_t, Int_t>, std::unique_ptr<TF1>> fFits;
   std::map<std::string, std::unique_ptr<GamR::Nucleus::Photon>> fReference;
   std::map<std::string, std::vector<std::pair<GamR::Nucleus::Photon, Double_t>>> fRelative;
   std::map<std::string, std::map<std::pair<Int_t, Int_t>, std::unique_ptr<TGraphErrors>>> fGraphs;
   std::map<std::pair<Int_t, Int_t>, Double_t> fFitResults;

private:
   class GlobalChiSquare;
   Int_t AddDataSet(std::string fn);

public:
   TimeWalk(std::vector<Int_t> ids);
   ~TimeWalk();
   Int_t AddPeak(std::string dataset, GamR::Nucleus::Photon photon, Double_t time);
   void MakeGraphs(Int_t ntoys, Bool_t showmc = kTRUE);

   void Draw(TCanvas *c, Bool_t fits = kFALSE, std::string saveas = "");
   void Fit();
};

} // namespace Processor
} // namespace GamR

#endif
