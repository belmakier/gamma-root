#ifndef GAMR_NUCLEUS_STATE_HH
#define GAMR_NUCLEUS_STATE_HH

/* ROOT */
#include <Rtypes.h>
#include <TNamed.h>

namespace GamR {
namespace Nucleus {

class State : public TNamed {
private:
   Float_t fEnergy;
   Float_t fMeanlife;
   Char_t fSpin2;
   Bool_t fParity;

public:
   // Constructors
   State(Float_t E = 0, Char_t J2 = 0, Bool_t P = 0, Float_t T = 0)
      : fEnergy(E), fMeanlife(T), fSpin2(J2), fParity(P){};

   // Setters
   void SetEnergy(Float_t E) { fEnergy = E; };
   void SetSpin(Float_t J) { fSpin2 = static_cast<Char_t>(2 * J); };
   void SetSpin(Char_t J) { fSpin2 = 2 * J; }
   void SetPositive() { fParity = kFALSE; };
   void SetNegative() { fParity = kTRUE; };

   // Getters
   Float_t GetEnergy() { return fEnergy; }
   Char_t Get2J() { return fSpin2; };
   Double_t GetMeanlife() { return fMeanlife; };

   // Functions
   Bool_t IsNegative() { return fParity; };
   Bool_t IsPositive() { return !fParity; };

   // Operators
   Bool_t operator==(const State &o) const
   {
      return (fEnergy == o.fEnergy) && (fSpin2 == o.fSpin2) && (fParity == o.fParity);
   };
   Bool_t operator!=(const State &other) const { return !(*this == other); };
   Bool_t operator<(const State &other) const { return fEnergy < other.fEnergy; };
   Bool_t operator>(const State &other) const { return !(*this < other); };

   ClassDef(State, 1);
};

} // namespace Nucleus
} // namespace GamR

#endif
