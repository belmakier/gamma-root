#ifndef GAMROOT_SPECT_IO_HH
#define GAMROOT_SPECT_IO_HH

/* STD */
#include <string>
#include <vector>

/* ROOT */
#include <TH1.h>
#include <TH2.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TCutG.h>

namespace GamR {
  namespace Spect {

    std::string ToText(const TH1 *h, std::string outfile = "", std::string delimiter=",");
    std::string ToText(const TH2 *h, std::string outfile = "", std::string delimiter=",", int binx_lo = -1, int binx_hi = -1, int biny_lo = -1, int biny_hi = -1);
    std::string ToText(const TGraphErrors *g, std::string outfile = "", std::string delimiter=",");
    std::string ToText(const TGraph *g, std::string outfile = "", std::string delimiter=",");
    std::string ToText(const TGraph *g, int ID, std::string outfile = "", std::string delimiter=",");
    std::string ToText(const TF1 *f, std::string outfile = "", std::string delimiter=",");
    void ToBin(const TH2 *h, std::string outfile = "", int padx=0, int pady=0);
    void ToBin(const TH1 *h, std::string outfile = "");
    void ToSPE(const TH1 *h, std::string outfile = "");
    TH1D FromText(std::string s, std::string name);
    TH1D *FromBin(std::string s, std::string name, std::string title, int nx, double low, double high, int size);
    TCutG *CutFromText(std::string s, std::string name);
    TH2D *FromBin(std::string s, std::string name, std::string title,
                  int nx, double xlow, double xhigh,
                  int ny, double ylow, double yhigh,
                  int size);

  } // namespace Spect
} // namespace GamR

#endif
