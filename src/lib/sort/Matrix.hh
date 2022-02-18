#ifndef GAMRSORT_MATRIX_HH
#define GAMRSORT_MATRIX_HH

#include "Sorter.hh"

#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>

#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include <toolkit/Gate.hh>
#include <tree/Reader.hh>

namespace GamR {
namespace Sort {
namespace Type {

class Matrix {
public:
   enum Axis {
      kCoincidence, // YAxis = DetJ[MeasY]
      kSum,         // YAxis = DetJ[MeasY] + DetI[MeasY]
      kDiff,        // YAxis = DetJ[MeasY] - DetI[MeasY]
      kProduct,     // YAxis = DetJ[MeasY] * DetI[MeasY]
      kRatio        // YAxis = DetJ[MeasY] / DetI[MeasY]
   };

private:
   // Typedefs
   using GroupID_t = size_t;
   using MeasID_t = size_t;
   using DetID_t = Int_t; // -1 for wildcard, else could have used a UShort_t

   // Gates
   // AND across the vector OR within map
   using Gates_t = std::vector<std::unordered_map<
      GroupID_t, std::unordered_map<DetID_t, std::unordered_map<MeasID_t,
                                                                GamR::TK::GateMap>>>>; // woah...

public:
   // Member variables
   std::shared_ptr<TH2D> ptrMatrix;

   Gates_t fGates;
   // std::unordered_set<size_t> gatespassed;
   std::unordered_map<GroupID_t, size_t> fInNumAndGates;
   std::vector<std::pair<GroupID_t, MeasID_t>> fReaderMeasurements;

   // Configuration
   const std::string fPrefix;
   const GroupID_t fGroupI, fGroupJ;
   const MeasID_t fMeasX, fMeasY;
   const Axis XAxis, YAxis;
   const size_t GatedSort;
   Sorter *p;

private:
   // Helper functions

   inline const Bool_t
   SkipEvent(const GamR::Tree::Reader &myreader, std::map<std::pair<GroupID_t, DetID_t>, Bool_t> &skipdet) const
   {
      // All gates must be passed otherwise the gate is skipped and vici
      // versa
      std::set<size_t> gatespassed; // the gate groups that passed
      for (auto &d : skipdet) {
         d.second = kFALSE;
      } // assume detectors don't gate
      // the following detector groups are involved in gates
      for (const auto &gid_n : fInNumAndGates) {
         const GroupID_t &itrGroup = gid_n.first;
         // if a detector group doesn't have enough unique detectors
         // to pass all of the detectors we should pass immediately

         // if (myreader[itrGroup].NumFired() < gid_n.second) { return kTRUE; } //
         // not enough data

         // however counting how many unique detectors we need is a bit tricky
         // skip this optimisation for now

         // across all the gate groups
         for (size_t idxGate = 0; idxGate < fGates.size(); ++idxGate) {
            // if there are no gates relevant for this detector group
            if (!fGates[idxGate].count(itrGroup)) {
               continue;
            } else if (gatespassed.count(idxGate)) {
               continue;
            } // no point this gate passed
            else if (gatespassed.size() == fGates.size()) {
               return kFALSE;
            } // we're actually done

            // does a detector pass this group?
            Bool_t pass = kFALSE;
            // go through all the detectors but break out early if we pass
            for (size_t idxDet0 = 0; !pass && (idxDet0 < myreader[itrGroup].NumFired()); ++idxDet0) {
               const DetID_t &itrDet = myreader[itrGroup].ID[idxDet0];

               // If there is gate specific for this detector id check it first
               if (fGates.at(idxGate).at(itrGroup).count(itrDet)) {
                  for (const auto &m_g : fGates.at(idxGate).at(itrGroup).at(itrDet)) {
                     const MeasID_t &itrMeas = m_g.first;
                     const auto &itrGateMap = m_g.second;
                     if (itrGateMap.PassAny(myreader[itrGroup][itrMeas][idxDet0])) {
                        skipdet[{itrGroup, itrDet}] = kTRUE;
                        pass = kTRUE;
                        gatespassed.insert(idxGate);
                        break;
                     }
                  }
               }
               // Otherwise, check if this detector passes the wildcard gate
               if (!pass && fGates.at(idxGate).at(itrGroup).count(-1)) {
                  for (const auto &m_g : fGates.at(idxGate).at(itrGroup).at(-1)) {
                     const MeasID_t &itrMeas = m_g.first;
                     const auto &itrGateMap = m_g.second;
                     if (itrGateMap.PassAny(myreader[itrGroup][itrMeas][idxDet0])) {
                        skipdet[{itrGroup, itrDet}] = kTRUE;
                        pass = kTRUE;
                        gatespassed.insert(idxGate);
                        break;
                     }
                  }
               }
            } // endfor detector
         }    // endfor gates
      }       // endfor detector group
      if (gatespassed.size() == fGates.size()) {
         return kFALSE;
      }
      return kTRUE;
   }

   inline const Double_t GetValue(const Matrix::Axis &Axis, const size_t &MeasN,
                                  const GamR::Tree::Reader::DetGroup &Group1, const size_t &Det1,
                                  const GamR::Tree::Reader::DetGroup &Group2, const size_t &Det2) const
   {
      if (Axis == Matrix::Axis::kCoincidence) {
         return Group1[MeasN][Det1];
      } else if (Axis == Matrix::Axis::kSum) {
         return Group1[MeasN][Det1] + Group2[MeasN][Det2];
      } else if (Axis == Matrix::Axis::kDiff) {
         return Group1[MeasN][Det1] - Group2[MeasN][Det2];
      } else if (Axis == Matrix::Axis::kProduct) {
         return Group1[MeasN][Det1] * Group2[MeasN][Det2];
      } else if (Axis == Matrix::Axis::kRatio) {
         return Group1[MeasN][Det1] / Group2[MeasN][Det2];
      } else {
         return -1;
      }
   }

   inline const Double_t GetX(const GamR::Tree::Reader &myR, const size_t &Det1, const size_t &Det2) const
   {
      return GetValue(XAxis, fMeasX, myR[fGroupI], Det1, myR[fGroupJ], Det2);
   }
   inline const Double_t GetY(const GamR::Tree::Reader &myR, const size_t &Det1, const size_t &Det2) const
   {
      // note switched order on Y axis
      return GetValue(YAxis, fMeasY, myR[fGroupJ], Det2, myR[fGroupI], Det1);
   }

public: // Public Interface
   Matrix(Sorter *parent, std::string prefix, size_t g1, size_t g2, size_t m1, size_t m2,
          std::vector<std::string> gates, Matrix::Axis x = Matrix::Axis::kCoincidence,
          Matrix::Axis y = Matrix::Axis::kCoincidence)
      : fGates(gates.size()), fPrefix(prefix), fGroupI(g1), fGroupJ(g2), fMeasX(m1), fMeasY(m2), XAxis(x), YAxis(y),
        GatedSort(gates.size()), p(parent)
   {

      // Going to need to read at least these
      fReaderMeasurements.push_back({fGroupI, fMeasX});
      fReaderMeasurements.push_back({fGroupI, fMeasY});
      fReaderMeasurements.push_back({fGroupJ, fMeasX});
      fReaderMeasurements.push_back({fGroupJ, fMeasY});

      // Need to get the shared matrix
      std::stringstream ssname;
      ssname << fPrefix << "_";
      ssname << "g" << fGroupI << "m" << fMeasX;
      ssname << "g" << fGroupJ << "m" << fMeasY;
      ptrMatrix = p->GetMatrix(ssname.str());

      // Extract gates if defined
      std::cout << std::endl;
      if (!GatedSort) {
         std::cout << "No gates defined.";
      } else {
         std::cout << "Gates" << std::endl;
         static const std::regex gateregex("^\\s*([0-9]+).([0-9]+).([0-9*]+) ([0-9]+) ([0-9]+)\\s*$");
         static std::smatch gatematches;

         std::unordered_map<GroupID_t, std::unordered_set<MeasID_t>> trackmeasurements;
         for (size_t idxGate = 0; idxGate < gates.size(); ++idxGate) {
            std::stringstream ss(gates[idxGate]);
            // extract the gates defined for this gate group
            std::string gate;
            size_t n = 0; // sub (OR) gate number
            std::unordered_set<GroupID_t> groupsingate;
            while (!ss.eof() && std::getline(ss, gate, '|')) {
               ++n;
               std::stringstream key;
               Bool_t matched = std::regex_match(gate, gatematches, gateregex);
               // if (!matched) { throw some error }
               GroupID_t groupid = std::stoi(gatematches[1]);
               MeasID_t measid = std::stoi(gatematches[2]);
               DetID_t detid = !gatematches[3].compare("*") ? -1 : std::stoi(gatematches[3]);
               key << "g" << groupid << "m" << measid << "d";
               if (detid < 0) {
                  key << "X";
               } else {
                  key << detid;
               }
               fGates[idxGate][groupid][detid][measid].SetName(key.str().c_str());
               key << "G" << n;
               fGates[idxGate][groupid][detid][measid][key.str()].SetGate(std::stod(gatematches[4]),
                                                                          std::stod(gatematches[5]));
               std::cout << "(Group: " << groupid << " Meas: " << measid << " Det: " << gatematches[3];
               std::cout << " LO: " << gatematches[4] << " HI: " << gatematches[5] << ") ";
               if (trackmeasurements[groupid].empty() || trackmeasurements[groupid].count(measid)) {
                  groupsingate.emplace(groupid);
               }
               trackmeasurements[groupid].emplace(measid);
               fReaderMeasurements.push_back({groupid, measid});
               // being lazy and writing to disk each time
               p->WriteObject(&fGates[idxGate][groupid][detid][measid], ("gates/" + ssname.str()).c_str(), "", kTRUE);
            } // endwhile each sub (OR) gate
            for (auto &group : groupsingate) {
               ++fInNumAndGates[group];
            }
            if (idxGate < gates.size() - 1) {
               std::cout << std::endl << "AND" << std::endl;
            }
            TNamed gatestr(("gatestr" + std::to_string(idxGate)).c_str(), gates[idxGate].c_str());
            p->WriteObject(&gatestr, ("gates/" + ssname.str()).c_str(), "", kTRUE);
         } // endfor each gate (AND) group
         for (auto &g_n : fInNumAndGates) {
            std::cout << std::endl << "Group " << g_n.first << " min required => " << g_n.second;
         }
      } // end if GatedSort
      std::cout << std::endl;

   } // end Sort::Type::Matrix::Matrix(...)

   void operator()(TTreeReader &R)
   {
      const auto myR = GamR::Tree::Reader(R, fReaderMeasurements);
      std::map<std::pair<GroupID_t, DetID_t>, Bool_t> mSkipDetector;

      while (R.Next() && !p->Done()) {
         p->Tick();
         // not enough data for a matrix -> insta pass
         if (myR[fGroupI].NumFired() + myR[fGroupJ].NumFired() < 2) {
            continue;
         }
         if (GatedSort && SkipEvent(myR, mSkipDetector)) {
            continue;
         }

         for (size_t idxDet1 = 0; idxDet1 < myR[fGroupI].NumFired(); ++idxDet1) {
            const auto &DetID1 = myR[fGroupI].ID[idxDet1];
            if (mSkipDetector[{fGroupI, DetID1}]) {
               continue;
            }
            for (size_t idxDet2 = 0; idxDet2 < myR[fGroupJ].NumFired(); ++idxDet2) {
               const auto &DetID2 = myR[fGroupJ].ID[idxDet2];
               if (mSkipDetector[{fGroupJ, DetID2}]) {
                  continue;
               } else if (DetID1 == DetID2) {
                  continue;
               } else {
                  ptrMatrix->Fill(GetX(myR, idxDet1, idxDet2), GetY(myR, idxDet1, idxDet2));
               }
            }
         }
      }
   } // end Sort::Type::Matrix::operator(...)
};

} // namespace Type
} // namespace Sort
} // namespace GamR

#endif
