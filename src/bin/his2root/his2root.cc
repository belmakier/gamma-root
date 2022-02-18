#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <TFile.h>
#include <TH1.h>
#include <TH2.h>

/**
   Converts a *.his file containing 1-D and 2-D histograms
   into a ROOT file.  Assumes the existence of a *.list file with the
   same name.  Not tested extensively.

   @param cHisFileName Name of the input *.his file
   @return The number of histograms converted
*/
int main(int argc, char *argv[])
{
   int nHists = 0; // counter for number of histograms processed
   for (int i = 1; i < argc; ++i) {
      const char *cHisFileName = argv[i];
      std::cout << "Converting file " << cHisFileName << std::endl;
      std::stringstream ss;
      std::string line, sListFileName, sHisFileName(cHisFileName), sRootFileName;
      sListFileName = sHisFileName.substr(0, sHisFileName.length() - 3);
      sListFileName.append("list");
      sRootFileName = sHisFileName.substr(0, sHisFileName.length() - 3);
      sRootFileName.append("root");
      std::ifstream listFile;
      listFile.open(sListFileName);
      std::string first;
      int details = 0; // flag to mark if we're in the "detailed info" part of the
                       // list file or not

      int HID;  /*histogram ID*/
      int dim;  /* dimension of histogram: assuming 1 or 2 */
      int hwpc; /* half words per channel */
      // int len;   /* length in characters of array */
      // int compr; /* compression, not used */
      int minX;          /* minimum (X) value of array */
      int maxX;          /* max value (X) */
      int minY;          /* minimum (Y) value of array */
      int maxY;          /* max value (Y) */
      std::string title; /* title of histogram */
      uint32_t datum;    /* 64 bit integer to store a single channel */

      FILE *hisFile;
      int read;
      hisFile = std::fopen(cHisFileName, "rb");
      TFile *outFile = new TFile(sRootFileName.c_str(), "recreate");

      while (std::getline(listFile, line)) {
         ss.clear();
         ss.str(line);
         ss >> first;
         if (details == 1) { /* if past the list of IDs */
            std::cout << "processing line: " << line << std::endl;
            HID = stoi(line.substr(0, 5));
            dim = stoi(line.substr(5, 5));
            hwpc = stoi(line.substr(10, 4));
            // compr = stoi(line.substr(23, 8));
            minX = stoi(line.substr(31, 6));
            maxX = stoi(line.substr(37, 6));
            title = line.substr(54);

            if (hwpc > 2) {
               std::cout << "warning! more than 64 bit integer, expect bad behaviour" << std::endl;
            }
            if (dim == 2) { /* 2D histogram */
               std::getline(listFile, line);
               ss.clear();
               ss.str(line);
               minY = stoi(line.substr(31, 6));
               maxY = stoi(line.substr(37, 6));

               /* make the histogram */
               TString sHistName;
               sHistName.Form("ID%d", HID);
               TH2I *hist = new TH2I(sHistName.Data(), title.c_str(), maxX - minX + 1, minX, maxX + 1, maxY - minY + 1,
                                     minY, maxY + 1);

               /* fill the histogram */
               for (int iyChannel = 0; iyChannel <= maxY; iyChannel++) {
                  for (int ixChannel = 0; ixChannel <= maxX; ixChannel++) {
                     read = std::fread(&datum, (size_t)hwpc * 2, (size_t)1, hisFile);
                     if (read == 1) {
                        for (int count = 0; count < (int)datum; ++count)
                           hist->Fill(ixChannel, iyChannel);
                        // hist->SetBinContent(ixChannel, iyChannel, datum);
                     } else {
                        std::cout << "error occurred in reading data" << std::endl;
                     }
                  }
               }

               hist->Write();
            } else { /* 1D histogram */
               TString sHistName;
               sHistName.Form("ID%d", HID);
               TH1I *hist = new TH1I(sHistName.Data(), title.c_str(), maxX - minX + 1, minX, maxX + 1);

               /* fill the histogram */
               for (int ixChannel = 0; ixChannel <= maxX; ixChannel++) {
                  read = std::fread(&datum, (size_t)hwpc * 2, (size_t)1, hisFile);
                  if (read == 1) {
                     for (int count = 0; count < (int)datum; ++count)
                        hist->Fill(ixChannel);
                  } else {
                     std::cout << "error occurred in reading data" << std::endl;
                  }
               }

               hist->Write();
            }

            nHists = nHists + 1;
         }
         if (first == "HID") {
            details = 1;
         }

      } // *.list file loop
      outFile->Close();
   }
   return nHists;
} // his2root
