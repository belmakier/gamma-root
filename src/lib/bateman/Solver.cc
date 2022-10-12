#include "Nucleus.hh"
#include "Scheme.hh"
#include "Solver.hh"

namespace GamR {
namespace Bateman {

    void Solver::solve(Scheme &scheme) {
      std::vector<double> x;
      for (int i=0; i<scheme.nuclei.size(); ++i) {
        x.push_back(N0 * scheme.nuclei[i]->N0);
      }

      double time = 0.0;
      int step = 0;
      while (time < max_time) {
        rk.do_step(scheme, x, time, stepsize);
        for (int i=0; i<scheme.nuclei.size(); ++i) {
          scheme.nuclei[i]->population[step] = x[i];
        }
        ++step;
        time += stepsize;
      }
    }
  }
}

