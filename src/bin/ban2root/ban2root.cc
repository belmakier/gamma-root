#include <iostream>
#include <string>

#include <TFile.h>

#include <lib/ornl/OakRidge.hh>

/**
   Converts a *.ban file containing 2-D ORNL format "Banana" gates to a ROOT
   file containing GamR::ORNL::BananaGate objects

   @param cBanFileName Name of the input *.ban file
   @return 0 for success, -1 for failure
*/
int main(int argc, char *argv[])
{
   for (int i = 1; i < argc; ++i) {
      const char *cBanFileName = argv[i];
      std::string sBanFileName(cBanFileName), sRootFileName;
      sRootFileName = sBanFileName.substr(0, sBanFileName.length() - 3);
      sRootFileName.append("root");
      TFile *file = new TFile(sRootFileName.c_str(), "recreate");
      file->cd();

      GamR::ORNL::readAllBananas(cBanFileName);

      file->Close();
   }

   return 0;
}
