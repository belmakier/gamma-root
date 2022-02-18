#include <fstream>

#include "Transition.hh"

void GamR::Nucleus::Transition::AddBackground() {
  GamR::TK::Gate tempgate;
  tempgate.SetGate();
  this->fBackground.push_back(tempgate);
}

void GamR::Nucleus::Transition::AddBackground(double Low, double High) {
  GamR::TK::Gate tempgate;
  tempgate.SetGate(Low,High);
  this->fBackground.push_back(tempgate);
}

GamR::Nucleus::TransitionMap::TransitionMap(const char *name, std::string asciimapfilename) : TNamed(name, name) {
  this->ReadFile(asciimapfilename);
}

void GamR::Nucleus::TransitionMap::ReadFile(std::string asciimapfilename) {
  std::ifstream asciimapfile (asciimapfilename.c_str());
  std::string type;
  std::string key;
  double lowin;
  double highin;
  fMap.clear();
  while (asciimapfile >> type >> key >> lowin >> highin) {
    if (type=="[peak]") {
      this->fMap[key].SetPeak(lowin,highin);
    } else if (type=="[back]") {
      this->fMap[key].AddBackground(lowin,highin);
    }
  }
}

void GamR::Nucleus::TransitionMap::WriteFile(std::string asciimapfilename) {
  std::ofstream asciimapfile(asciimapfilename.c_str());

  for (auto i = fMap.begin(); i != fMap.end(); ++i) {
    asciimapfile << "[peak]" << "   " << i->first << "   "
                 << (i->second).GetGate()->GetLow() << "   " << (i->second).GetGate()->GetHigh() << std::endl;
    for (int ibackgate = 0; ibackgate<(i->second.GetGateBGs())->size(); ++ibackgate ) {
      asciimapfile << "[back]" << "   " << i->first << "   "
                   << (*(i->second).GetGateBGs())[ibackgate].GetLow() << "   " << (*(i->second).GetGateBGs())[ibackgate].GetHigh() << std::endl;
      
    }
  }

  asciimapfile.close();
}

double GamR::Nucleus::Transition::Apply(TH1D *hist) const {
  return this->GetGate()->GetIntegral(hist, *(this->GetGateBGs()));
}
double GamR::Nucleus::Transition::ApplyError(TH1D *hist) const {
  return this->GetGate()->GetIntegralError(hist, *(this->GetGateBGs()));
}
double GamR::Nucleus::Transition::ApplyCounts(TH1D *hist) const {
  return this->GetGate()->GetCounts(hist, *(this->GetGateBGs()));
}
double GamR::Nucleus::Transition::ApplyCountsError(TH1D *hist) const {
  return this->GetGate()->GetCountsError(hist, *(this->GetGateBGs()));
}
