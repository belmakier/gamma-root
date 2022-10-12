#ifndef GAMR_BATEMAN_SCHEME_HH
#define GAMR_BATEMAN_SCHEME_HH

#include <string>
#include <vector>

#include "Nucleus.hh"

namespace GamR {
namespace Bateman {
  class Solver;
  
  class Scheme {
  public:
    std::vector<Nucleus*> nuclei;
  public:
    void AddNucleus(std::string n, double lt, double eff, double lt_err, double eff_err, double N0) { nuclei.push_back(new Nucleus((int)nuclei.size(), n, lt, eff, lt_err, eff_err, N0)); }
    void ReadScheme(std::string f);
    void NormBranches();
    void NormN0();

    void operator()(const std::vector<double> &x, std::vector<double> &dxdt, const double);
    void PrintSummary(std::ostream &stream);
    void PrintPops(std::ostream &stream, Solver &solver);
    void PrintDecays(std::ostream &stream, Solver &solver);
    double GetTotal(double t, Solver &solver);
    double Get(int indx, double t, Solver &solver);
  };
}
}

#endif
