#ifndef GAMR_VIEWER_VIEWER
#define GAMR_VIEWER_VIEWER

#include <tree/Tree.hh>

namespace GamR {
  namespace Viewer {
    template <class TExpDefn, class TEvent>
    class Viewer {
    public:
      TExpDefn fExpDefn;
      ULong64_t nRawEntries;
      ULong64_t ixEventNum;
      TEvent *fEvent;
      Viewer(std::vector<std::string> infile, std::string conf) : ixEventNum(0) {
        fExpDefn.Load(infile, conf, 0);
        nRawEntries = static_cast<ULong64_t>(fExpDefn.fRawChain->GetEntries());
        fEvent = new TEvent();
        ROOT::DisableImplicitMT();
      }

      int Next() {
        if (ixEventNum == nRawEntries) { return 0; }
        ULong64_t ixLocalNum = fExpDefn.fRawChain->LoadTree(ixEventNum);
        fExpDefn.fRawChain->GetTree()->GetEntry(ixLocalNum);
        fEvent->Reset();
        fEvent->FillEvent(fExpDefn.fDetDefns);
        ++ixEventNum;
        return 1;
      }
    };
  }
}

#endif
