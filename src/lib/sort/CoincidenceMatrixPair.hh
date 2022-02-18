#ifndef GAMRSORT_COINCIDENCEMATRIXPAIR_HH
#define GAMRSORT_COINCIDENCEMATRIXPAIR_HH

#include "Sorter.hh"

#include <string>
#include <vector>

#include <TTreeReader.h>
#include <TTreeReaderValue.h>

namespace GamR {
namespace Sort {
namespace Type {

template <class DetX, class DetY, size_t X, size_t Y>
class CoincidenceMatrixPair {
private:
   Sorter *p;
   std::shared_ptr<TH2D> ptrMatrix;
   std::string Prefix;
   std::string GroupX;
   std::string GroupY;
   std::string IDX;
   std::string IDY;

public:
   CoincidenceMatrixPair(Sorter *parent, std::vector<std::string> opts) : p(parent)
   {
      if (opts.size() < 5)
         throw std::runtime_error("Invalid arguments, expect: Prefix GroupX GroupY IDX IDY");
      Prefix = opts[0];
      GroupX = opts[1];
      GroupY = opts[2];
      IDX = opts[3];
      IDY = opts[4];
      std::string name(Prefix + "_g" + GroupX + "m" + X + "id" + IDX + "g" + GroupY + "m" + Y + "id" + IDY);
      ptrMatrix = p->GetMatrix(name);
      ptrMatrix->SetBins(4096, 0, 4096, 4096, 0, 4096);
   }

   void operator()(TTreeReader &R)
   {
      TTreeReaderValue<std::vector<DetX>> rDetsX(R, ("DetGroup._" + GroupX).c_str());
      TTreeReaderValue<std::vector<DetY>> rDetsY(R, ("DetGroup._" + GroupY).c_str());
      while (R.Next() && !p->Done()) {
         p->Tick();
         std::vector<DetX> vecDetsX = *rDetsX;
         std::vector<DetY> vecDetsY = *rDetsY;
         if (vecDetsX.size() + vecDetsY.size() < 2) {
            continue;
         }
         for (auto &Det1 : vecDetsX) {
            for (auto &Det2 : vecDetsY) {
               if ((Det1.ID != std::stoi(IDX)) || (Det2.ID != std::stoi(IDY))) {
                  continue;
               }
               auto x = Det1.template GetCal<X>();
               auto y = Det2.template GetCal<Y>();
               if (!(x && y)) {
                  continue;
               }
               ptrMatrix->Fill(x, y);
            } // fold 2
         }    // fold 1
      }       // all events
   }          // Sorter::CoincidenceMatrix::operator()
};

} // namespace Type
} // namespace Sort
} // namespace GamR

#endif
