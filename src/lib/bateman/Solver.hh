#ifndef GAMR_BATEMAN_SOLVER_HH
#define GAMR_BATEMAN_SOLVER_HH

#include "Nucleus.hh"
#include "Scheme.hh"

#include <boost/numeric/odeint.hpp>

namespace GamR {
namespace Bateman {
  class Solver {
  public:
    boost::numeric::odeint::runge_kutta4<std::vector<double> > rk;
    double stepsize = 0.1; // same units as lifetimes
    double N0 = 100.0;  //initial population
    double max_time = 300.0;

    void solve(Scheme &scheme);
  };
}
}

#endif
  
