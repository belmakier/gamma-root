/**
   @file
   @author Tim Gray <timothy.gray@anu.edu.au>
   @date 19/09/2017

   @section DESCRIPTION

   Toolkit to convert between Oak Ridge National Laboratory data formats/tools
   and ROOT.

*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#include <TClass.h>
#include <TKey.h>

#include "OakRidge.hh"
ClassImp(GamR::ORNL::BananaGate);

namespace GamR {
namespace ORNL {
BananaGate::BananaGate() : TCutG()
{
   this->iIH = 0;
   this->iIB = 0;
   this->iDG = 0;
   this->iNP = 0;
   this->iIPX = 0;
   this->iIPY = 0;
   this->iLXD = 0;
   this->iLXG = 0;
   this->iLYD = 0;
   this->iLYG = 0;
   this->iNUPM = 0;
   this->iIAUX = 0;
   this->iJAUX = 0;
   this->fileName = "default-name";
}

BananaGate::~BananaGate()
{
   this->iIH = 0;
   this->iIB = 0;
   this->iDG = 0;
   this->iNP = 0;
   this->iIPX = 0;
   this->iIPY = 0;
   this->iLXD = 0;
   this->iLXG = 0;
   this->iLYD = 0;
   this->iLYG = 0;
   this->iNUPM = 0;
   this->iIAUX = 0;
   this->iJAUX = 0;
   this->fileName.clear();
}

BananaGate::BananaGate(const char *name, int n /*=0*/) : TCutG(name, n)
{
   this->iIH = 0;
   this->iIB = 0;
   this->iDG = 0;
   this->iNP = 0;
   this->iIPX = 0;
   this->iIPY = 0;
   this->iLXD = 0;
   this->iLXG = 0;
   this->iLYD = 0;
   this->iLYG = 0;
   this->iNUPM = 0;
   this->iIAUX = 0;
   this->iJAUX = 0;
   this->fileName = "default-name";
}

BananaGate::BananaGate(const TCutG &cutg, TH2 &hist, int iBID, int iHID, const char *fileName) : TCutG(cutg)
{
   this->iIH = iHID;
   this->iIB = iBID;
   this->iDG = 0;
   this->iNP = cutg.GetN();
   this->iIPX = 0;
   this->iIPY = 0;
   this->iLXD = hist.GetNbinsX();
   this->iLXG = hist.GetNbinsX();
   this->iLYD = hist.GetNbinsY();
   this->iLYG = hist.GetNbinsY();
   this->iNUPM = 0;
   this->iIAUX = 0;
   this->iJAUX = 0;
   this->fileName = fileName;
}

void BananaGate::SetFileName(const char *fileName)
{
   this->fileName = fileName;
}

std::string BananaGate::WriteBan()
{
   /* returns string that is the relevant part of the *.ban file */
   char cInpLine[81], cFileName[27], cHID[7], cBID[7], cDG[7], cNP[7];
   std::sprintf(cFileName, "%-26s", (this->fileName).c_str());
   std::sprintf(cHID, "%6d", this->iIH);
   std::sprintf(cBID, "%6d", this->iIB);
   std::sprintf(cDG, "%6d", this->iDG);
   std::sprintf(cNP, "%6d", this->iNP);
   std::sprintf(cInpLine, "INP %s%s%s%s%s%*c", cFileName, cHID, cBID, cDG, cNP, 26, ' ');

   char cTitleLine[81];
   std::sprintf(cTitleLine, "TIT %-76s", this->GetTitle());

   char cGateLine[81];
   char cIPX[7], cIPY[7], cLXD[7], cLXG[7], cLYD[7], cLYG[7];
   char cNUPM[9], cIAUX[9], cJAUX[9];
   std::sprintf(cIPX, "%6d", this->iIPX);
   std::sprintf(cIPY, "%6d", this->iIPY);
   std::sprintf(cLXD, "%6d", this->iLXD);
   std::sprintf(cLXG, "%6d", this->iLXG);
   std::sprintf(cLYD, "%6d", this->iLYD);
   std::sprintf(cLYG, "%6d", this->iLYG);
   std::sprintf(cNUPM, "%8d", this->iNUPM);
   std::sprintf(cIAUX, "%8d", this->iIAUX);
   std::sprintf(cJAUX, "%8d", this->iJAUX);
   std::sprintf(cGateLine, "GATE %s%s%s%s%s%s%s%s%s%*c", cIPX, cIPY, cLXD, cLXG, cLYD, cLYG, cNUPM, cIAUX, cJAUX, 15,
                ' ');

   char cCXYLine[721] = "CXY  ";
   int nPoint = 0;
   int nPoints = this->iNP;
   /* 9x CXY lines */
   for (int i = 0; i < 9; i++) {
      if (i > 0)
         std::sprintf(cCXYLine, "%sCXY  ", cCXYLine);
      int nLinePoints = 0;
      while (nPoint < nPoints) { /* point loop */
         double dx;
         double dy;
         this->GetPoint(nPoint, dx, dy);
         int x = (int)dx;
         int y = (int)dy;
         if (x < 0)
            x = 0;
         if (y < 0)
            y = 0;
         /* check if we have room on this line */
         if (nLinePoints < 7) {
            /* append to this line */
            std::sprintf(cCXYLine, "%s%5d%5d", cCXYLine, x, y);
            /* go to next point */
            nLinePoints = nLinePoints + 1;
            nPoint = nPoint + 1;
         } else { /* no room on the line */
            std::sprintf(cCXYLine, "%s%*c", cCXYLine, 75 - nLinePoints * 10, ' ');
            /* go to next line */
            break;
         }
      }
      if (nPoint == nPoints)
         std::sprintf(cCXYLine, "%s%*c", cCXYLine, 75 - nLinePoints * 10, ' ');
   }

   char cBanLine[961];
   std::sprintf(cBanLine, "%s%s%s%s", cInpLine, cTitleLine, cGateLine, cCXYLine);
   std::string sBanLine(cBanLine);
   return sBanLine;
}

/**
   Converts a *.his file containing 1-D and 2-D histograms
   into a ROOT file.  Assumes the existence of a *.list file with the
   same name.  Not tested extensively.

   @param cHisFileName Name of the input *.his file
   @return The number of histograms converted
*/
int his2root(const char *cHisFileName)
{
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
   int nHists = 0;  // counter for number of histograms processed

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
            TH2D *hist = new TH2D(sHistName.Data(), title.c_str(), maxX - minX + 1, minX, maxX + 1, maxY - minY + 1,
                                  minY, maxY + 1);

            /* fill the histogram */
            for (int iyChannel = 0; iyChannel <= maxY; iyChannel++) {
               for (int ixChannel = 0; ixChannel <= maxX; ixChannel++) {
                  read = std::fread(&datum, (size_t)hwpc * 2, (size_t)1, hisFile);
                  if (read == 1) {
                     hist->SetBinContent(ixChannel, iyChannel, datum);
                  } else {
                     std::cout << "error occurred in reading data" << std::endl;
                  }
               }
            }

            hist->Write();
         } else { /* 1D histogram */
            TString sHistName;
            sHistName.Form("ID%d", HID);
            TH1D *hist = new TH1D(sHistName.Data(), title.c_str(), maxX - minX + 1, minX, maxX + 1);

            /* fill the histogram */
            for (int ixChannel = 0; ixChannel <= maxX; ixChannel++) {
               read = std::fread(&datum, (size_t)hwpc * 2, (size_t)1, hisFile);
               if (read == 1) {
                  hist->SetBinContent(ixChannel, datum);
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
   return nHists;
} // his2root

/**
   Creates a BananaGate object from a *.ban file

   @param cBanFileName Name of input *.ban file
   @param iID ID of the desired banana gate in the *.ban file
   @return The created BananaGate object
*/
BananaGate *readBanana(const char *cBanFileName, int iID)
{
   std::stringstream ss;
   std::string sBanString, line;
   std::ifstream banFile;
   banFile.open(cBanFileName);
   std::getline(banFile, sBanString);

   size_t pos = 0;
   BananaGate *banGate;

   pos = sBanString.find("INP ", pos);
   line = sBanString.substr(0, pos);
   /* check if ID exists */
   if (line.find(std::to_string(iID)) > line.length()) {
      std::cout << "ID not present in *.ban file" << std::endl;
      return NULL;
   }

   pos = pos + 4;
   /* find relevant part */
   while (true) {
      std::string junk;
      /* next INP */
      std::string sBananaGate = sBanString.substr(pos - 4, sBanString.find("INP ", pos + 4) - pos);

      int iTIT = sBananaGate.find("TIT ");
      int iGATE = sBananaGate.find("GATE ");
      int iCXY = sBananaGate.find("CXY  ");
      std::string sINPLine = sBananaGate.substr(0, iTIT);
      std::string sTITLine = sBananaGate.substr(iTIT, iGATE - iTIT);
      std::string sGATELine = sBananaGate.substr(iGATE, iCXY - iGATE);
      std::string sCXYLine = sBananaGate.substr(iCXY);

      /*
        std::cout << sINPLine << std::endl;
        std::cout << sTITLine << std::endl;
        std::cout << sGATELine << std::endl;
        std::cout << sCXYLine << std::endl;
      */

      /* process first line */
      std::stringstream ssINP(sINPLine);
      std::string fileName;
      int iIH, iIB, iDG, iNP;
      ssINP >> junk;
      ssINP >> fileName;
      ssINP >> iIH;
      ssINP >> iIB;
      ssINP >> iDG;
      ssINP >> iNP;

      if (iIB == iID) {
         /* found correct Banana gate, process */
         TString sCutName;
         sCutName.Form("bID%d", iID);
         banGate = new BananaGate(sCutName.Data(), iNP);
         banGate->SetName(sCutName.Data());
         banGate->Set(iNP);

         banGate->SetIH(iIH);
         banGate->SetIB(iIB);
         banGate->SetDG(iDG);
         banGate->SetNP(iNP);
         banGate->SetFileName(fileName);

         /* second line */
         std::string sTitle = sTITLine.substr(4);
         // std::cout << sTitle << std::endl;
         banGate->SetTitle(sTitle.c_str());

         /* third line */
         std::stringstream ssGATE(sGATELine);
         int iIPX, iIPY, iLXD, iLXG, iLYD, iLYG, iNUPM, iIAUX, iJAUX;
         ssGATE >> junk;
         ssGATE >> iIPX;
         ssGATE >> iIPY;
         ssGATE >> iLXD;
         ssGATE >> iLXG;
         ssGATE >> iLYD;
         ssGATE >> iLYG;
         ssGATE >> iNUPM;
         ssGATE >> iIAUX;
         ssGATE >> iJAUX;

         banGate->SetIPX(iIPX);
         banGate->SetIPY(iIPY);
         banGate->SetLXD(iLXD);
         banGate->SetLXG(iLXG);
         banGate->SetLYD(iLYD);
         banGate->SetLYG(iLYG);
         banGate->SetNUPM(iNUPM);
         banGate->SetIAUX(iIAUX);
         banGate->SetJAUX(iJAUX);

         /* final line: coordinates */
         std::stringstream ssCXY(sCXYLine);
         int nPoint = 0;
         junk.clear();
         while (true) {
            ssCXY >> junk;
            if (junk == "CXY") {
               continue;
            } else {
               int x;
               int y;
               x = std::atoi(junk.c_str());
               ssCXY >> y;
               banGate->SetPoint(nPoint, x, y);
               nPoint = nPoint + 1;
            }
            if (nPoint == iNP)
               break; // CXY loop
         }
         break; // INP loop
      }         // iIB == iID

      pos = sBanString.find("INP", pos);
      if (pos >= sBanString.length()) {
         std::cout << "End of file reached" << std::endl;
         return NULL;
      } else {
         pos = pos + 4; // move past INP characters
      }

   } // INP loop

   return banGate;

} // readBanana

/**
   Reads all Banana Gates from a specified *.ban file and writes them to the
   current directory.

   @param cBanFileName Input *.ban file name
*/
void readAllBananas(const char *cBanFileName)
{
   std::string sBanString;
   std::string line;
   std::ifstream banFile;
   banFile.open(cBanFileName);
   std::getline(banFile, sBanString);

   BananaGate *banGate;

   line = sBanString.substr(0, sBanString.find("INP"));
   std::stringstream ss(line);

   while (true) {
      int iID;
      ss >> iID;
      if (iID == 0) {
         break;
      }
      banGate = readBanana(cBanFileName, iID);
      if (banGate) {
         banGate->Write();
      }
   }
}

/**
   Takes a vector of BananaGates and writes the corresponding *.ban file

   @param cBanFileName output *.ban file name
   @param vBananas vector of BananaGate objects
*/
void writeBananas(const char *cBanFileName, std::vector<BananaGate> vBananas)
{

   /* write header of file */
   char cHeader[401];
   int n = 0;
   for (auto &bananaGate : vBananas) {
      n = n + 1;
      /* append to cHeader */
      if (n == 1) {
         std::sprintf(cHeader, "%5d", bananaGate.GetIB());
      } else {
         std::sprintf(cHeader, "%s%5d", cHeader, bananaGate.GetIB());
      }
   }
   for (int i = n; i < 80; i++) {
      std::sprintf(cHeader, "%s%5d", cHeader, 0);
   }

   std::ofstream outFile;
   outFile.open(cBanFileName);
   outFile << cHeader;

   for (auto &bananaGate : vBananas) {
      /* append to file */
      outFile << bananaGate.WriteBan().c_str();
   }

   outFile.close();
}

/**
   Iterates through all BananaGate objects in current directory, puts them into
   a vector, and writes to a *.ban file

   @param cBanFileName Output *.ban file name
*/
void writeAllBananas(const char *cBanFileName)
{
   TIter next(gDirectory->GetListOfKeys());
   TKey *key;
   std::vector<BananaGate> vBananas;
   while ((key = (TKey *)next())) {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      if (!cl->InheritsFrom("GamR::ORNL::BananaGate"))
         continue;
      vBananas.push_back(*(BananaGate *)key->ReadObj());
   }
   writeBananas(cBanFileName, vBananas);
}

} // namespace ORNL
} // namespace GamR
