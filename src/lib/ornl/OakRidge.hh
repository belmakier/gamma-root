/* header file for OakRidge.cc
   author Tim Gray - timothy.gray@anu.edu.au
*/

#ifndef GAMR_OAKRIDGE_HH
#define GAMR_OAKRIDGE_HH

#include <string.h>
#include <vector>

#include <TCutG.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TROOT.h>

namespace GamR {
/*!
  \addtogroup ORNL
  @{
*/

//! Library of tools to convert and process Oak Ridge National Laboratory
//! formats
namespace ORNL {
class BananaGate : public TCutG {
   /* ROOT implimentation of an ORNL style Banana Gate
      For details of parameters see upak/Ddoc/banco.doc
      Many of the attributes will be completely useless,
      however they are necessary for writing out to a
      *.ban file.
      */
private:
   int iIH, iIB, iDG, iNP;
   int iIPX, iIPY, iLXD, iLXG, iLYD, iLYG, iNUPM, iIAUX, iJAUX;
   std::string fileName;

public:
   BananaGate();
   BananaGate(const char *name, int n = 0);
   BananaGate(const TCutG &cutg, TH2 &hist, int iBID, int iHID, const char *fileName);
   ~BananaGate();

   void SetFileName(const char *fileName);
   void SetIH(int iIH) { this->iIH = iIH; };
   void SetIB(int iIB) { this->iIB = iIB; };
   void SetDG(int iDG) { this->iDG = iDG; };
   void SetNP(int iNP) { this->iNP = iNP; };
   void SetIPX(int iIPX) { this->iIPX = iIPX; };
   void SetIPY(int iIPY) { this->iIPY = iIPY; };
   void SetLXD(int iLXD) { this->iLXD = iLXD; };
   void SetLXG(int iLXG) { this->iLXG = iLXG; };
   void SetLYD(int iLYD) { this->iLYD = iLYD; };
   void SetLYG(int iLYG) { this->iLYG = iLYG; };
   void SetNUPM(int iNUPM) { this->iNUPM = iNUPM; };
   void SetIAUX(int iIAUX) { this->iIAUX = iIAUX; };
   void SetJAUX(int iJAUX) { this->iJAUX = iJAUX; };
   void SetFileName(std::string fileName) { this->fileName = fileName; };
   int GetIH() { return this->iIH; };
   int GetIB() { return this->iIB; };
   int GetDG() { return this->iDG; };
   int GetNP() { return this->iNP; };
   int GetIPX() { return this->iIPX; };
   int GetIPY() { return this->iIPY; };
   int GetLXD() { return this->iLXD; };
   int GetLXG() { return this->iLXG; };
   int GetLYD() { return this->iLYD; };
   int GetLYG() { return this->iLYG; };
   int GetNUPM() { return this->iNUPM; };
   int GetIAUX() { return this->iIAUX; };
   int GetJAUX() { return this->iJAUX; };
   TCutG GetTCutG() { return TCutG(this->GetName(), this->GetN(), this->GetX(), this->GetY()); };
   std::string GetFileName() { return this->fileName; };

   std::string WriteBan();

   /// \cond CLASSIMP
   ClassDef(BananaGate, 1);
   /// \endcond
};

// int his2root(const char *cHisFileName);

BananaGate *readBanana(const char *cBanFileName, int iID);
void readAllBananas(const char *cBanFileName);

void writeBananas(const char *cBanFileName, std::vector<BananaGate> vBananas);
void writeAllBananas(const char *cBanFileName);

} // namespace ORNL
/* @} */
} // namespace GamR

#endif // OAKRIDGE_HH
