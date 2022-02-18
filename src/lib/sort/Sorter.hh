#ifndef GAMRSORT_SORTER_HH
#define GAMRSORT_SORTER_HH

/* STD */
#include <atomic>
#include <map>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

/* ROOT */
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TObject.h>

#include <ROOT/TThreadedObject.hxx>
#include <ROOT/TTreeProcessorMT.hxx>

namespace GamR {
namespace Sort {

class Sorter {
private:
   std::vector<std::string> fInFilename;
   TFile *fOutFile;
   TChain fChain;
   ROOT::TTreeProcessorMT *fProcessor;
   // std::unique_ptr<ROOT::TTreeProcessorMT> fProcessor;
   std::map<std::string, ROOT::TThreadedObject<TH1D>> fSafeSpecs;
   std::map<std::string, ROOT::TThreadedObject<TH2D>> fSafeMats;
   std::map<std::string, ROOT::TThreadedObject<TH3D>> fSafeCubes;
   std::chrono::system_clock::time_point fTimeStart;
   std::atomic<size_t> fCounter;
   std::atomic<size_t> fTotalEvents;
   std::atomic<Bool_t> fStatus;
   std::mutex fMutex;
   ULong64_t fXbins;
   Long64_t fXlow;
   Long64_t fXhigh;
   ULong64_t fYbins;
   Long64_t fYlow;
   Long64_t fYhigh;
   ULong64_t fZbins;
   Long64_t fZlow;
   Long64_t fZhigh;

private:
   void Begin();
   void End();

public:
   Sorter(std::vector<std::string> fns, std::string out, Int_t compression = 101);
   ~Sorter();

   Bool_t Done();
   void Tick();

   void SetXsize(ULong64_t bins, Long64_t low, Long64_t high);
   void SetYsize(ULong64_t bins, Long64_t low, Long64_t high);
   void SetZsize(ULong64_t bins, Long64_t low, Long64_t high);

   std::shared_ptr<TH1D> GetSpectrum(std::string s);
   std::shared_ptr<TH2D> GetMatrix(std::string s);
   std::shared_ptr<TH3D> GetCube(std::string s);

   template <class Sort>
   void Process(std::vector<std::string> args)
   {
      Begin();
      auto sort = Sort(this, args);
      fProcessor->Process(sort);
      End();
   }

   template <class Sort>
   void Process(Sort &sort)
   {
      Begin();
      fProcessor->Process(sort);
      End();
   }

   void PrintStatus();
   void Halt();
   void Write(std::string folder = "/");
   void WriteObject(TObject *obj, const char *folder = "/", const char *rename = "", bool quiet = kFALSE);
   void Clear();
};
} // namespace Sort
} // namespace GamR
#endif
