#ifndef GAMRSORT_TIMEDIFFERENCE_HH
#define GAMRSORT_TIMEDIFFERENCE_HH

#include "Sorter.hh"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <TH2.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

#include <nucleus/Photon.hh>

namespace GamR {
namespace Sort {
namespace Type {

template <class Det, size_t E, size_t T>
class TimeDifference {
private:
   Sorter *p;
   std::shared_ptr<TH2D> ptrPkMatrixSum;
   std::shared_ptr<TH2D> ptrBgMatrixSum;
   std::shared_ptr<GamR::Nucleus::Photon> ptrRefPhoton;
   std::vector<int> detIds;
   std::string gid;

public:
   TimeDifference(Sorter *parent, std::vector<std::string> opts) : p(parent)
   {
      if (opts.size() < 7)
         throw std::length_error("Invalid arguments, expect: prefix group ref_E "
                                 "ref_p ref_P ref_b ref_B");

      std::stringstream ss;
      std::copy(opts.begin(), opts.end(), std::ostream_iterator<std::string>(ss, "\n"));

      std::string prefix;
      ss >> prefix;
      ss >> gid;
      float energy;
      ss >> energy;
      float pklow;
      ss >> pklow;
      float pkhigh;
      ss >> pkhigh;
      float bglow;
      ss >> bglow;
      float bghigh;
      ss >> bghigh;
      std::string nameprefix(prefix + "_g" + gid + "m" + E + "td" + T);

      ptrRefPhoton = std::make_shared<GamR::Nucleus::Photon>(energy, pklow, pkhigh, bglow, bghigh);
      ptrRefPhoton->SetName((nameprefix + "R").c_str());

      p->WriteObject(ptrRefPhoton.get());

      int id;
      while (ss >> id) {
         detIds.push_back(id);
      };

      // Create the histogram objects
      ptrPkMatrixSum = p->GetMatrix((nameprefix + "P").c_str());
      ptrBgMatrixSum = p->GetMatrix((nameprefix + "B").c_str());

      // Setting bins
      ptrPkMatrixSum->SetBins(4096, 0, 4096, 8192, -4096, 4096);
      ptrBgMatrixSum->SetBins(4096, 0, 4096, 8192, -4096, 4096);
      // ptrPkMatrixSum -> SetCanExtend(TH1::kAllAxes);
      // ptrBgMatrixSum -> SetCanExtend(TH1::kAllAxes);

      // Set titles

      std::stringstream ssTitle;
      ssTitle.str("");
      ssTitle << "$E_{1}=" << ptrRefPhoton->GetEnergy() << "$  Gate: $";
      ssTitle << ptrRefPhoton->GetGate()->GetLow() << "\\to";
      ssTitle << ptrRefPhoton->GetGate()->GetHigh();
      ssTitle << "$;Gamma Energy, E_{2}";
      ssTitle << "[keV];$\\Delta t = t_{2}-t_{1}$";

      ptrPkMatrixSum->SetTitle(ssTitle.str().c_str());

      // Background
      ssTitle.str("");
      ssTitle << "$E_{1}=" << ptrRefPhoton->GetEnergy() << "$  GateBG: $";
      ssTitle << ptrRefPhoton->GetGateBG()->GetLow() << "\\to";
      ssTitle << ptrRefPhoton->GetGateBG()->GetHigh();
      ssTitle << "$;Gamma Energy, E_{2}";
      ssTitle << "[keV];$\\Delta t = t_{2}-t_{1}$";

      ptrBgMatrixSum->SetTitle(ssTitle.str().c_str());

   } // Sorter::TimeWalk

   void operator()(TTreeReader &R)
   {
      std::string group = "DetGroup._" + gid;
      TTreeReaderValue<std::vector<Det>> rdrDets(R, group.c_str());
      while (R.Next() && !p->Done()) {
         std::vector<Det> vecDets = *rdrDets;
         p->Tick();
         if (vecDets.size() < 2) {
            continue;
         }
         for (auto &deti : vecDets) {
            for (auto &detj : vecDets) {
               if (deti.ID == detj.ID) {
                  continue;
               }
               Bool_t pkgated = ptrRefPhoton->GetGate()->Pass(deti.template GetCal<E>());
               Bool_t bggated = ptrRefPhoton->GetGateBG()->Pass(deti.template GetCal<E>());

               if ((pkgated || bggated) && (deti.template Get<T>() > 0) && (detj.template Get<T>() > 0)) {
                  // tdiff = T2 - T1 ALWAYS.
                  auto tdiff = detj.template GetCal<T>() - deti.template GetCal<T>();
                  if (pkgated) {
                     ptrPkMatrixSum->Fill(detj.template GetCal<E>(), tdiff);
                  } else if (bggated) {
                     ptrBgMatrixSum->Fill(detj.template GetCal<E>(), tdiff);
                  }
               } // gated
            }    // fold 2
         }       // fold 1
      }          // all events
   }             // Sorter::TimeWalk::operator()
};

} // namespace Type
} // namespace Sort
} // namespace GamR

#endif
