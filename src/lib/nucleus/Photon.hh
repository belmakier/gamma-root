#ifndef GAMR_NUCLEUS_PHOTON_HH
#define GAMR_NUCLEUS_PHOTON_HH

#include "Transition.hh"

namespace GamR {
namespace Nucleus {

class Photon : public Transition {
private:
   Char_t fSpin;
   Bool_t fElectric;

public:
   using Transition::Transition;

   void SetElectric() { fElectric = kTRUE; };
   void SetMagnetic() { fElectric = kFALSE; };

   void SetSpin(Int_t L) { fSpin = L; };
   Char_t GetSpin() { return fSpin; };

   // Functions
   Bool_t IsElectric() { return fElectric; };
   Bool_t IsMagnetic() { return !fElectric; };

   // Operators
   Bool_t operator==(const Photon &o) const
   {
      return (fEnergy == o.fEnergy) && (fSpin == o.fSpin) && (fElectric == o.fElectric);
   };
   Bool_t operator!=(const Photon &other) const { return !(*this == other); };
   Bool_t operator<(const Photon &other) const { return fEnergy < other.fEnergy; };
   Bool_t operator>(const Photon &other) const { return !(*this < other); };

   ClassDef(Photon, 1);
};

} // namespace Nucleus
} // namespace GamR

#endif
