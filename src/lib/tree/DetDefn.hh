#ifndef GAMROOT_TREE_DETDEFN_HH
#define GAMROOT_TREE_DETDEFN_HH

/* STD */
#include <array>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

/* ROOT */
#include <TFormula.h>
#include <TH1D.h>
#include <TObject.h>
#include <TRandom3.h>

/* GAMR */
#include <utils/Tuples.hh>

namespace GamR {
namespace Tree {

template <class... Ts>
class TDetDefn : public TObject {
private:
   TRandom3 fRnd;
   // std::tuple<std::shared_ptr<Ts>...> fRawDatum;
   std::tuple<Ts *...> fRawDatum;
   std::tuple<std::pair<Ts, Double_t>...> fDatum;
   std::tuple<std::vector<Ts>...> fRunning;
   std::vector<std::shared_ptr<TFormula>> fCalFunc;
   std::vector<std::shared_ptr<TFormula>> fPollGate;
   // std::vector<std::shared_ptr<TH1D> > fRawHists;
   Int_t fMeasCount;
   Int_t fAtleast;
   TFormula fEffFunc;

   std::array<std::pair<Double_t, Double_t>, sizeof...(Ts)> fMean;   // Means first X, last X
   std::array<std::pair<Double_t, Double_t>, sizeof...(Ts)> fStdDev; // Stdev, first X, last X

   std::string fType;
   std::string fName;
   Int_t fID;
   std::array<Int_t, sizeof...(Ts)> fRunningIndex;
   std::array<Double_t, sizeof...(Ts)> fRunningSquared; // sum(x^2)/size
   Int_t fPollFreq;

private:
   struct UpdateGoodness;      // IsGood()
   struct InterpretPointers;   // SetPtrs()
   struct DereferencePointers; // Calibrate(...)
   // struct FillHistogram; // Calibrate(...)
   struct CalFunctor; // Calibrate(...)

public:
   TDetDefn(std::string t = "", int id = -1, std::string n = "", int I = 50000)
      : fDatum(), fType(t), fName(n), fID(id), fPollFreq(I)
   {
      fRawDatum = std::make_tuple(new Ts...);
      fRunning = std::make_tuple(std::vector<Ts>(I)...);
      fRnd.SetSeed(std::rand());
      fRunningIndex.fill(0);
      fRunningSquared.fill(0);
   }
   ~TDetDefn()
   {
      fCalFunc.resize(0);
      fPollGate.resize(0);
   }

   template <int N>
   auto GetDatum(ULong64_t eventNum) -> decltype(std::get<N>(fDatum)) &
   {
      Calibrate(eventNum);
      return std::get<N>(fDatum);
   }
   auto GetAllDatums(ULong64_t eventNum) -> decltype(fDatum) &
   {
      Calibrate(eventNum);
      return fDatum;
   }
   size_t GetNumMeasurements() const { return sizeof...(Ts); }

   Int_t GetID() { return fID; }
   Double_t GetEfficiency() { return fEffFunc.Eval(0); }

   Bool_t IsGood();
   void SetPtrs(std::map<std::string, void *> &branchmap, std::string branches);
   void SetRequired(Int_t n) { fAtleast = n; };
   void SetCalFuncs(std::string funcstrs);
   void SetPollGates(std::string pollstrs);
   void SetEffFunc(std::string function);
   void Calibrate(ULong64_t eventNum=0);

   ClassDef(TDetDefn, 1);
};

} // namespace Tree
} // namespace GamR

#include "DetDefn.tt"

#endif
