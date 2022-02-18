#ifndef GAMROOT_TREE_EVENT_HH
#define GAMROOT_TREE_EVENT_HH

/* STD */
#include <tuple>
#include <vector>

/* ROOT */
#include <Rtypes.h>
#include <TObject.h>

/* GAMR */
#include <utils/Tuples.hh>

namespace GamR {
namespace Tree {

template <class... ADets>
class TEvent : public TObject {
public:
   template <size_t GroupN>
   using detector_type = typename std::tuple_element<GroupN, std::tuple<ADets...>>::type;
   std::tuple<std::vector<ADets>...> DetGroup;
   ULong64_t EventNum;

private:
   struct ClearVector;
   struct EventTupleFiller;
   struct IgnoreTObject;

public:
   TEvent()
   {
      auto tmp = std::tuple<ADets...>();
      GamR::Utils::for_each_in_tuple(tmp, IgnoreTObject());
   };
   ~TEvent(){};

   void SetEventNum(ULong64_t n) { EventNum = n; }
   size_t GetNumGroups() const { return sizeof...(ADets); }
   template <int N>
   auto GetGroup() -> decltype(std::get<N>(DetGroup)) &
   {
      return std::get<N>(DetGroup);
   }
   auto GetGroups() -> decltype(DetGroup) & { return DetGroup; }
   template <typename T>
   void FillEvent(T &detdefntup)
   {
     GamR::Utils::for_both_in_tuple(detdefntup, DetGroup, EventTupleFiller(), EventNum);
   }
   void Reset() { GamR::Utils::for_each_in_tuple(DetGroup, ClearVector()); }

   ClassDef(TEvent, 1);
};

} /* namespace Tree */
} /* namespace GamR */

#include "Event.tt"

#endif
