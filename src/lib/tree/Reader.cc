#include "Reader.hh"

namespace GamR {
namespace Tree {

Reader::DetGroup::DetGroup(const Reader *parent, size_t g, std::vector<size_t> measn)
   : p(parent), ID(*(p->pTreeReader),
                   ("DetGroup._" + std::to_string(g) + ".ID").c_str()) //,
// Eff(*(p->pTreeReader), ("DetGroup._"+std::to_string(g)+".Eff").c_str())
{
   std::string prefix = "DetGroup._" + std::to_string(g);
   // ID = TTreeReaderArray<UShort_t>(*(p->pTreeReader), (prefix+".ID").c_str());
   // Eff = TTreeReaderArray<Float_t>(*(p->pTreeReader),
   // (prefix+".Eff").c_str());
   for (auto &n : measn) {
      Meas.emplace(
         std::piecewise_construct, std::forward_as_tuple(n),
         std::forward_as_tuple(*(p->pTreeReader), (prefix + ".Meas._" + std::to_string(n) + ".second").c_str()));
   }
}

Reader::Reader(TTreeReader &R, std::vector<std::pair<size_t, size_t>> branches)
   : pTreeReader(&R), EventNum(*pTreeReader, "EventNum")
{
   // extract detector branches
   std::unordered_map<size_t, std::vector<size_t>> group_meas;
   for (auto &g_m : branches) {
      group_meas[g_m.first].push_back(g_m.second);
   }
   // create readers
   for (auto &g_ms : group_meas) {
      Groups.emplace(std::piecewise_construct, std::forward_as_tuple(g_ms.first),
                     std::forward_as_tuple(this, g_ms.first, g_ms.second));
   }
}

} // namespace Tree
} // namespace GamR
