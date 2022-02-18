#include <iostream>
#include <string>

#include <TFile.h>

#include <lib/ornl/OakRidge.hh>

/**
   Converts a *.root file containing GamR::ORNL::BananaGate objects to a *.ban
   file containing 2-D ORNL format "Banana" gates.

   @param cRootFileName Name of the input *.root file
   @return 0 for success, -1 for failure
*/
int main(int argc, char *argv[])
{
   for (int i = 1; i < argc; ++i) {
      const char *cRootFileName = argv[i];
      std::string sRootFileName(cRootFileName), sBanFileName;
      sBanFileName = sRootFileName.substr(0, sRootFileName.length() - 4);
      sBanFileName.append("ban");
      TFile *file = new TFile(sRootFileName.c_str());
      file->cd();

      GamR::ORNL::writeAllBananas(sBanFileName.c_str());

      file->Close();
   }

   return 0;
}
