#ifndef GAMRSORT_COINCIDENCECUBEDIFF_HH
#define GAMRSORT_COINCIDENCECUBEDIFF_HH

#include "Sorter.hh"

namespace GamR {
namespace Sort {
namespace Type {

template <class DetX, class DetY, size_t X, size_t Y, size_t Z>
class CoincidenceCubeDiff {
private:
   Sorter *p;
   std::shared_ptr<TH3D> ptrCube;
   std::string Prefix;
   std::string GroupX;
   std::string GroupY;
   std::string GroupZ;

public:
   CoincidenceCubeDiff(Sorter *parent, std::vector<std::string> opts) : p(parent)
   {
      if (opts.size() < 3)
         throw std::length_error("Invalid arguments, expect: Prefix GroupX GroupY");
      Prefix = opts[0];
      GroupX = opts[1];
      GroupY = opts[2];
      std::string name(Prefix + "_g" + GroupX + "m" + X + "g" + GroupY + "m" + Y + "d" + Z);
      ptrCube = p->GetCube(name);
      ptrCube->SetBins(512, 0, 2048, 512, 0, 2048, 256, -128 * 24.41,
                       128 * 24.41); // Make knob?
                                     // ptrCube -> SetCanExtend(TH1::kAllAxes);
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
               if (Det1.ID == Det2.ID) {
                  continue;
               }
               auto x = Det1.template GetCal<X>();
               auto y = Det2.template GetCal<Y>();
               auto z1 = Det1.template GetCal<Z>();
               auto z2 = Det2.template GetCal<Z>();

               auto rx = Det1.template Get<X>();
               auto ry = Det2.template Get<Y>();
               auto rz1 = Det1.template Get<Z>();
               auto rz2 = Det2.template Get<Z>();

               if (!(rx && ry && rz1 && rz2)) {
                  continue;
               }
               ptrCube->Fill(x, y, z2 - z1);
            } // fold 2
         }    // fold 1
      }       // all events
   }          // Sorter::CoincidenceMatrix::operator()
};

} // namespace Type
} // namespace Sort
} // namespace GamR

#endif
