#include "Scheme.hh"
#include "Solver.hh"

namespace GamR {
  namespace Bateman {
    void Scheme::ReadScheme(std::string f) {
      FILE *file = fopen(f.c_str(), "ra");
      if (file == NULL) { std::cout << "Scheme file " << f << " does not exist!" << std::endl; return; }
      std::stringstream ss;
      char cline[2048];

      int ind = 0;
      double branches[100][100];
      double branch_errs[100][100];
      for (int i=0; i<100; ++i) {
        for (int j=0; j<100; ++j) {
          branches[i][j] = 0;
          branch_errs[i][j] = 0;
        }
      }
      while(std::fgets(cline, sizeof cline, file)!=NULL) {
        std::string line(cline);
        if (line.size() == 0) { continue; }
        if (line[0] == '#') { continue; }
        if (line[0] == ';') { continue; }

        ss.clear();
        ss.str(line);

        std::string type;
        ss >> type;
        if (type == "N") {
          int id;
          std::string name;
          double tau;
          double tau_err;
          double eff;
          double eff_err;
          ss >> id >> name >> tau >> tau_err >> eff >> eff_err;
          AddNucleus(name, tau, eff, tau_err, eff_err);          
        }
        else if (type == "B") {
          int id1, id2;
          double br, br_err;
          ss >> id1 >> id2 >> br >> br_err;
          branches[id1][id2] = br;
          branch_errs[id1][id2] = br_err;
        }
      }

      for (int i=0; i<100; ++i) {
        for (int j=0; j<100; ++j) {
          if (branches[i][j] == 0) { continue; }
          nuclei[j]->feeders.push_back(nuclei[i]);
          nuclei[j]->branches.push_back(branches[i][j]);
          nuclei[j]->branch_errs.push_back(branch_errs[i][j]);
        }
      }

      NormBranches();

      fclose(file);
    }

    void Scheme::NormBranches() {
      double branches[100][100];
      double branch_errs[100][100];
      for (int i=0; i<100; ++i) {
        for (int j=0; j<100; ++j) {
          branches[i][j] = 0;
          branch_errs[i][j] = 0;
        }
      }

      for (int j=0; j<nuclei.size(); ++j) {
        for (int i=0; i<nuclei[j]->feeders.size(); ++i) {
          branches[nuclei[j]->feeders[i]->index][nuclei[j]->index] = nuclei[j]->branches[i];
          branch_errs[nuclei[j]->feeders[i]->index][nuclei[j]->index] = nuclei[j]->branch_errs[i];
        }
      }

      for (int j=0; j<nuclei.size(); ++j) {
        nuclei[j]->feeders.clear();
        nuclei[j]->branches.clear();
        nuclei[j]->branch_errs.clear();
      }
      
      for (int i=0; i<100; ++i) {
        double br_tot = 0;
        for (int j=0; j<100; ++j) {
          if (branches[i][j] == 0) { continue; }
          br_tot += branches[i][j];
        }

      
        for (int j=0; j<100; ++j) {
          if (branches[i][j] == 0) { continue; }
          double br = branches[i][j]/br_tot;
          double err_tot = 0;
          for (int k=0; k<100; ++k) {
            if (branches[i][k] == 0) { continue; }
            if (j == k ) { continue; }
            err_tot += std::pow(branches[i][j]/(br_tot*br_tot) * branch_errs[i][k], 2);
          }
            
          double br_err = std::sqrt(std::pow((br_tot - branches[i][j])/(br_tot*br_tot) * branch_errs[i][j], 2) + err_tot);
          nuclei[j]->feeders.push_back(nuclei[i]);
          nuclei[j]->branches.push_back(br);
          nuclei[j]->branch_errs.push_back(br_err);        
        }
      }    

    }
  
    void Scheme::operator()(const std::vector<double> &x, std::vector<double> &dxdt, const double) {
      for (int i=0; i<x.size(); ++i) {
        dxdt[i] = -(1.0/nuclei[i]->lifetime) * x[i];
        for (int j=0; j<nuclei[i]->feeders.size(); ++j) {
          dxdt[i] += nuclei[i]->branches[j] * (1.0/nuclei[i]->feeders[j]->lifetime) * x[nuclei[i]->feeders[j]->index];
        }
      }
    }

    void Scheme::PrintSummary(std::ostream &stream) {
      for (int i=0; i<nuclei.size(); ++i) {
        nuclei[i]->Print(stream);
      }
    }

    void Scheme::PrintPops(std::ostream &stream, Solver &solver) {
      double time = 0;
      int i = 0;
      while (time < solver.max_time) {
        stream << time << "   ";
        for (int j=0; j<nuclei.size(); ++j) {
          stream << nuclei[j]->population[i] << "    ";
        }
        stream << std::endl;
        ++i;
        time += solver.stepsize;
      }    
    }

    void Scheme::PrintDecays(std::ostream &stream, Solver &solver) {
      double time = 0;
      int i = 0;
      while (time < solver.max_time) {
        stream << time << "   ";
        for (int j=0; j<nuclei.size(); ++j) {
          stream << nuclei[j]->population[i] * 1.0/nuclei[j]->lifetime << "    ";
        }
        stream << std::endl;
        ++i;
        time += solver.stepsize;
      }    
    }

    double Scheme::GetTotal(double t, Solver &solver) {
      int i=0;
      double time = 0.0;
      if (t >= solver.max_time) { std::cout << "Evaluation ouside bounds!" << std::endl; return -1; }
      if (t < 0 ) { std::cout << "Evaluation ouside bounds!" << std::endl; return -1; }
      while (time < solver.max_time) {
        if (t >= time && t < time+solver.stepsize) { break; }      
        ++i;
        time += solver.stepsize;
      }

      //now we interpolate between i and i+1
      double n0 = 0.0;
      double n1 = 0.0;    
      for (int j=0; j<nuclei.size(); ++j) {
        n0 += nuclei[j]->efficiency * nuclei[j]->population[i] * 1.0/nuclei[j]->lifetime;
        n1 += nuclei[j]->efficiency * nuclei[j]->population[i+1] * 1.0/nuclei[j]->lifetime;
      }
      double frac = (t - time)/solver.stepsize;
      return n0+frac*(n1-n0);
    }
    
  }
}
