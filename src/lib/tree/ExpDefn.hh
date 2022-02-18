#ifndef GAMROOT_TREE_EXPDEFN_HH
#define GAMROOT_TREE_EXPDEFN_HH

/* STD */
#include <memory>
#include <string>
#include <thread>

#include <map>
#include <tuple>
#include <vector>

/* ROOT */
#include <TChain.h>
#include <TFile.h>
#include <TObject.h>
#include <TROOT.h>
#include <TTree.h>

/* VENDOR */
#include <inih/INIReader.h>

namespace GamR {
namespace Tree {

template <class... ADefns>
class TExpDefn : public TObject {
public:
   // TFile* fRawFile;
   TFile *fOutFile;
   // TTree* fRawTree;
   TChain *fRawChain;
   TTree *fOutTree;
   std::tuple<std::vector<ADefns>...> fDetDefns;
   std::map<std::string, void *> fBranchMap;
   std::vector<std::string> fDetGroups;
   INIReader fINIReader;
   std::string fINI;

private:
   struct FillDetDefns; // Load(...)

public:
  TExpDefn() { ROOT::EnableImplicitMT(std::thread::hardware_concurrency()); }
   ~TExpDefn()
   {
      for (auto itr : fBranchMap) {
         std::free(itr.second);
      }
      gROOT->CloseFiles();
   }

   template <int N>
   auto GetDetDefns() -> decltype(std::get<N>(fDetDefns)) &
   {
      return std::get<N>(fDetDefns);
   }
   auto GetAllDetDefns() -> decltype(fDetDefns) & { return fDetDefns; }
   void CloseFiles() { gROOT->CloseFiles(); }
   Int_t Load(std::vector<std::string> rootfn, std::string inifn, Bool_t quiet = kFALSE);
  Int_t LoadRaw(std::vector<std::string> branchlist, std::string inifn, Bool_t quiet);
  void ResetBranches(std::vector<std::string>);
   template <typename EventType>
   ULong64_t Convert(std::string outfn, ULong64_t eventoffset, ULong64_t nevents = 0, Bool_t quiet = kFALSE,
                     Int_t compression = 201, ULong64_t splitmb = 2000, Bool_t overwrite = kFALSE);

   ClassDef(TExpDefn, 1);
};

} // namespace Tree
} // namespace GamR

#include "ExpDefn.tt"

#endif
