#ifndef GAMROOT_TREE_READER_HH
#define GAMROOT_TREE_READER_HH

#include <string>
#include <unordered_map>
#include <vector>

#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

namespace GamR {
namespace Tree {

class Reader {
public: // Objects
   struct DetGroup {
      const Reader *p;
      std::unordered_map<size_t, TTreeReaderArray<Double_t>> Meas;
      TTreeReaderArray<UShort_t> ID;
      // TTreeReaderArray<Float16_t> Eff;
      DetGroup(const Reader *parent, size_t g, std::vector<size_t> measn);
      size_t NumFired() const { return ID.GetSize(); }
      const TTreeReaderArray<Double_t> &operator[](const size_t n) const { return Meas.at(n); }
   };

private: // Member variables
   TTreeReader *pTreeReader;
   std::unordered_map<size_t, DetGroup> Groups;
   TTreeReaderValue<ULong64_t> EventNum;

public: // Public interface
   Reader(TTreeReader &R, std::vector<std::pair<size_t, size_t>> branches);

   Bool_t Next() { return pTreeReader->Next(); }
   ULong64_t GetEventNum() { return *EventNum; }

   const DetGroup &operator[](const size_t n) const { return Groups.at(n); }
};

} // namespace Tree
} // namespace GamR

#endif
