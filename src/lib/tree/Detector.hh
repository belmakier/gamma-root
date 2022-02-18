#ifndef GAMROOT_TREE_DETECTOR_HH
#define GAMROOT_TREE_DETECTOR_HH

/* STD */
#include <iostream>
#include <tuple>

/* ROOT */
#include <TObject.h>

/* GAMR */
#include "DetDefn.hh"

namespace GamR {
namespace Tree {

template <typename... Ts>
class TDetector : public TObject {
public:
   template <size_t n>
   using meas_type = typename std::tuple_element<n, std::tuple<Ts...>>::type;
   using measurements_type = std::tuple<std::pair<Ts, Double_t>...>;

public:
   measurements_type Meas;
   UShort_t ID;
   Float16_t Eff;

public:
   TDetector() {}
  TDetector(TDetDefn<Ts...> &defn, ULong64_t eventNum)
   {
      // defn.Calibrate();
      ID = defn.GetID();
      Eff = defn.GetEfficiency();
      Meas = defn.GetAllDatums(eventNum);
   }
   ~TDetector() {}
   template <int N>
   auto Get() -> decltype(std::get<N>(Meas).first) &
   {
      return std::get<N>(Meas).first;
   }
   template <int N>
   auto GetCal() -> decltype(std::get<N>(Meas).second) &
   {
      return std::get<N>(Meas).second;
   }
   auto GetAll() -> decltype(Meas) & { return Meas; }
   size_t GetNumMeasurements() const { return sizeof...(Ts); }
   void Reset()
   {
      ID = UShort_t(0);
      Eff = Float16_t(1);
      Meas = measurements_type();
   }

   ClassDef(TDetector, 1);
};

} /* namespace Tree */
} /* namespace GamR */

#endif
