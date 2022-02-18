#ifndef GAMRSORT_TIMEWALKCAL_HH
#define GAMRSORT_TIMEWALKCAL_HH

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
class TimeWalkCal {
private:
   Sorter *p;
   std::map<std::pair<int, int>, std::shared_ptr<TH2D>> ptrPkMatrix;
   std::map<std::pair<int, int>, std::shared_ptr<TH2D>> ptrBgMatrix;
   std::shared_ptr<TH2D> ptrPkMatrixSum;
   std::shared_ptr<TH2D> ptrBgMatrixSum;
   std::shared_ptr<GamR::Nucleus::Photon> ptrRefPhoton;
   std::vector<int> detIds;
   std::string gid;

public:
   TimeWalkCal(Sorter *parent, std::vector<std::string> opts) : p(parent)
   {
      if (opts.size() < 8)
         throw std::length_error("Invalid arguments, expect: group ref_E ref_p "
                                 "ref_P ref_b ref_B id1 id2 ... idn");

      std::stringstream ss;
      std::copy(opts.begin(), opts.end(), std::ostream_iterator<std::string>(ss, "\n"));

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
      ptrRefPhoton = std::make_shared<GamR::Nucleus::Photon>(energy, pklow, pkhigh, bglow, bghigh);
      ptrRefPhoton->SetName("TC_REF");
      p->WriteObject(ptrRefPhoton.get());

      int id;
      while (ss >> id) {
         detIds.push_back(id);
      };

      // Create the histogram objects
      ptrPkMatrixSum = p->GetMatrix("P_TCAL");
      ptrBgMatrixSum = p->GetMatrix("B_TCAL");

      ptrPkMatrixSum->SetBins(2048, 0, 2048, 2048, -1024, 1024);
      ptrBgMatrixSum->SetBins(2048, 0, 2048, 2048, -1024, 1024);

      std::stringstream ssTitle;
      for (const auto &i : detIds) {
         for (const auto &j : detIds) {
            if (i == j) {
               continue;
            }
            ssTitle.str("");
            ss.clear();
            ss.str("");
            ss << i << "_" << j;
            ptrPkMatrix[{i, j}] = p->GetMatrix(("P" + ss.str()));
            ptrBgMatrix[{i, j}] = p->GetMatrix(("B" + ss.str()));

            ssTitle << "$E_{" << i << "}=" << ptrRefPhoton->GetEnergy() << "$  Gate: $";
            ssTitle << ptrRefPhoton->GetGate()->GetLow() << "\\to";
            ssTitle << ptrRefPhoton->GetGate()->GetHigh();
            ssTitle << "$;Gamma Energy, E_{" << j;
            ssTitle << "} [keV];$\\Delta t = t_{" << j << "}-t_{" << i << "}$";

            ptrPkMatrix[{i, j}]->SetTitle(ssTitle.str().c_str());
            ptrPkMatrix[{i, j}]->SetBins(2048, 0, 2048, 2048, -1024, 1024);
            // ptrPkMatrix[{i,j}] -> SetCanExtend(TH1::kYaxis); // better have a
            // knob
            // todo find out how many bins to actually use

            ptrBgMatrix[{i, j}]->SetTitle(ssTitle.str().c_str());
            ptrBgMatrix[{i, j}]->SetBins(2048, 0, 2048, 2048, -1024, 1024);
         }
      }
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
                  auto tdiff = detj.template Get<T>() - deti.template Get<T>(); // uncalibrated, think, document
                  if (pkgated) {
                     ptrPkMatrix[{deti.ID, detj.ID}]->Fill(detj.template GetCal<E>(), tdiff);
                     ptrPkMatrixSum->Fill(detj.template GetCal<E>(), tdiff);
                  } else if (bggated) {
                     ptrBgMatrix[{deti.ID, detj.ID}]->Fill(detj.template GetCal<E>(), tdiff);
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
