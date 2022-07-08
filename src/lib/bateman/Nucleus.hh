#ifndef GAMR_BATEMAN_NUCLEUS_HH
#define GAMR_BATEMAN_NUCLEUS_HH

#include <iostream>
#include <string>
#include <vector>

#define GAMR_BATEMAN_MAX_STEPS 16384

namespace GamR {
namespace Bateman {
  class Nucleus {
  public:
    int index;
    double lifetime;
    double lifetime_err;
    std::string name;
    double efficiency;
    double efficiency_err;

    std::vector<Nucleus*> feeders;
    std::vector<double> branches; //branching ratios from each feeder
    std::vector<double> branch_errs; 

    float *population;  //population as a function of time    
  public:
    Nucleus() : index(-1), lifetime(-1), efficiency(1.0), lifetime_err(0.0), efficiency_err(0.0) { population = new float[GAMR_BATEMAN_MAX_STEPS]; }
    Nucleus(int indx, std::string n, double lt, double eff, double lt_err, double eff_err) : index(indx), name(n), lifetime(lt), efficiency(eff), lifetime_err(lt_err), efficiency_err(eff_err) { population = new float[GAMR_BATEMAN_MAX_STEPS]; };
    double GetDC() { return 1.0/lifetime; }
    void AddFeeder(Nucleus *nuc, double branch) { feeders.push_back(nuc); branches.push_back(branch); }
    void Print(std::ostream &stream);
  };
}
}

#endif
