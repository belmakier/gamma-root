#include "Sorter.hh"

#include <chrono>
#include <iomanip>

namespace GamR {
namespace Sort {

Sorter::Sorter(std::vector<std::string> fns, std::string out, Int_t compression)
   : fInFilename(fns), fChain("EventTree"), fCounter(0), fTotalEvents(0), fStatus(kFALSE), fXbins(4096), fXlow(0),
     fXhigh(4096), fYbins(4096), fYlow(0), fYhigh(4096), fZbins(512), fZlow(0), fZhigh(512)
{
   ROOT::EnableImplicitMT(std::thread::hardware_concurrency());

   for (const auto &fn : fInFilename) {
      fChain.Add(fn.c_str());
   }
   fTotalEvents = fChain.GetEntries();

   // fProcessor = std::make_unique<ROOT::TTreeProcessorMT>(fChain);
   fProcessor = new ROOT::TTreeProcessorMT(fChain);

   fOutFile = new TFile(out.c_str(), "UPDATE");
   if (fOutFile->IsZombie() || !fOutFile->IsOpen())
      throw std::runtime_error("Error opening output file: " + out);
   fOutFile->SetCompressionSettings(compression);
}

Sorter::~Sorter()
{
   fOutFile->Close();
   delete fProcessor;
}

void Sorter::Begin()
{
   fCounter.store(0);
   fTimeStart = std::chrono::system_clock::now();
}

void Sorter::Halt()
{
   fStatus.store(kTRUE);
}

void Sorter::End()
{
   PrintStatus();
   Halt();
}

void Sorter::PrintStatus()
{
   if (fMutex.try_lock()) {
      auto now = std::chrono::system_clock::now();
      std::cout << "\rProcessed Events: ";
      std::cout << fCounter << " / " << fTotalEvents;

      std::cout << std::fixed;
      std::cout << std::setprecision(0);
      std::cout << std::noshowpoint;
      std::cout << " [" << 100.0 * fCounter / fTotalEvents << "%] ";

      std::chrono::duration<double> sec = now - fTimeStart;
      auto speed = fCounter / sec.count();
      auto remain = static_cast<ULong64_t>((fTotalEvents - fCounter) / speed);
      std::cout << "Time Remaining: ";
      std::cout << remain / 3600 << ":";
      std::cout << std::setw(2) << std::setfill('0') << remain / 60 % 60 << ":";
      std::cout << std::setw(2) << std::setfill('0') << remain % 60;
      std::cout << " [" << speed / 1000 << " k/s]";
      std::cout << std::flush;
      fMutex.unlock();
   }
}

void Sorter::Tick()
{
   ++fCounter;
}

void Sorter::Clear()
{
   fSafeSpecs.clear();
   fSafeMats.clear();
   fSafeCubes.clear();
}

Bool_t Sorter::Done()
{
   return fStatus.load();
}
void Sorter::Write(std::string folder)
{
   std::cout << std::endl << "Spectra" << std::endl;
   for (auto &h : fSafeSpecs) {
      fOutFile->cd(folder.c_str());
      auto m = h.second.Merge();
      m->Write("", TObject::kWriteDelete);
      std::cout << "\nWritten\t" << m->GetName();
      std::cout << "\t=>\t" << fOutFile->GetName() << std::endl;
   }

   std::cout << std::endl << "Matrices" << std::endl;
   for (auto &h : fSafeMats) {
      fOutFile->cd(folder.c_str());
      auto m = h.second.Merge();
      m->Write("", TObject::kWriteDelete);
      std::cout << "Written\t" << m->GetName();
      std::cout << "\t=>\t" << fOutFile->GetName() << std::endl;
   }

   std::cout << std::endl << "Cubes" << std::endl;
   for (auto &h : fSafeCubes) {
      fOutFile->cd(folder.c_str());
      auto m = h.second.Merge();
      m->Write("", TObject::kWriteDelete);
      std::cout << "Written\t" << m->GetName();
      std::cout << "\t=>\t" << fOutFile->GetName() << std::endl;
   }
}

void Sorter::WriteObject(TObject *obj, const char *folder /* = "/"*/, const char *rename /* = "" */, bool quiet)
{
   if (fMutex.try_lock()) {
      if (!fOutFile->GetDirectory(folder)) {
         fOutFile->cd("/");
         fOutFile->mkdir(folder);
      }
      fOutFile->cd(folder);
      obj->Write(rename, TObject::kWriteDelete);
      if (!quiet) {
         std::cout << std::endl << "Objects" << std::endl;
         std::cout << "Written\t" << obj->GetName();
         std::cout << "\t=>\t" << fOutFile->GetName() << ":" << folder << "/" << std::endl;
      }
      fOutFile->cd("/");
      fMutex.unlock();
   }
}

void Sorter::SetXsize(ULong64_t bins, Long64_t low, Long64_t high)
{
   fXbins = bins;
   fXlow = low;
   fXhigh = high;
}

void Sorter::SetYsize(ULong64_t bins, Long64_t low, Long64_t high)
{
   fYbins = bins;
   fYlow = low;
   fYhigh = high;
}

void Sorter::SetZsize(ULong64_t bins, Long64_t low, Long64_t high)
{
   fZbins = bins;
   fZlow = low;
   fZhigh = high;
}

std::shared_ptr<TH1D> Sorter::GetSpectrum(std::string s)
{
   std::shared_ptr<TH1D> h = fSafeSpecs[s].Get();
   h->SetName(s.c_str());
   h->SetTitle(s.c_str());
   h->SetBins(fXbins, fXlow, fXhigh);
   std::cout << std::endl << "Spectrum\t" << s << std::endl;
   return h;
}

std::shared_ptr<TH2D> Sorter::GetMatrix(std::string s)
{
   std::shared_ptr<TH2D> h = fSafeMats[s].Get();
   h->SetName(s.c_str());
   h->SetTitle(s.c_str());
   h->SetBins(fXbins, fXlow, fXhigh, fYbins, fYlow, fYhigh);
   std::cout << std::endl << "Matrix\t" << s << std::endl;
   return h;
}

std::shared_ptr<TH3D> Sorter::GetCube(std::string s)
{
   std::shared_ptr<TH3D> h = fSafeCubes[s].Get();
   h->SetName(s.c_str());
   h->SetTitle(s.c_str());
   h->SetBins(fXbins, fXlow, fXhigh, fYbins, fYlow, fYhigh, fZbins, fZlow, fZhigh);
   std::cout << std::endl << "Cube\t" << s << std::endl;
   return h;
}

} // namespace Sort
} // namespace GamR
