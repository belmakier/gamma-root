#include "Nucleus.hh"

namespace GamR {
namespace Bateman {
  void Nucleus::Print(std::ostream &stream) {
    stream << "=========== " << name << " ============" << std::endl;
    stream << " tau = " << lifetime << std::endl;
    stream << " " << feeders.size() << " feeders";
    if (feeders.size() > 0) {
      stream << ": " << std::endl; 
      for (int j=0; j<feeders.size(); ++j) {
        stream << "        " << feeders[j]->name << "  " << branches[j] << " +/- " << branch_errs[j] << std::endl;
      }
    }
    else {
      stream << std::endl;
    }
  }


}
}
