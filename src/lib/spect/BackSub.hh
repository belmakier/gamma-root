#ifndef GAMR_SPECT_BACKSUB_HH
#define GAMR_SPECT_BACKSUB_HH

#include <vector>

#include <TCanvas.h>
#include <TH2.h>

#include <toolkit/Gate.hh>

namespace GamR {
  namespace Spect {
    class BackSub2D {
    public:
      GamR::TK::Gate fPeakX;
      GamR::TK::Gate fPeakY;

      std::vector<GamR::TK::Gate > fBackY; //rectangle using fPeakX
      std::vector<GamR::TK::Gate > fBackX; //rectangle using fPeakY

      //diagonal backgrounds for compton subtraction
      std::vector<GamR::TK::Gate > fBackDiagX;
      std::vector<GamR::TK::Gate > fBackDiagY;

      //for background-background addition
      std::vector<GamR::TK::Gate > fBackBackX;
      std::vector<GamR::TK::Gate > fBackBackY;

      TH1D *y_sub;
      TH1D *x_sub;

      TH2D *unsubtracted;
      TH2D *subtracted;

      void GetClick(Int_t,Int_t,Int_t,TObject *selected);

      int SetPeak(GamR::TK::Gate x, GamR::TK::Gate y) {
        fPeakX = x;
        fPeakY = y;
        return 0;
      }
      
      int SetPeak(double x1, double y1, double x2, double y2) {
        GamR::TK::Gate x(x1, x2);
        GamR::TK::Gate y(y1, y2);
        return SetPeak(x,  y);
      }

      int AddBackX(GamR::TK::Gate x) {
        fBackX.push_back(x);
        return 0;
      }

      int AddBackY(GamR::TK::Gate y) {
        fBackY.push_back(y);
        return 0;
      }

      int AddBackX(double x1, double x2) {
        GamR::TK::Gate x(x1, x2);
        return AddBackX(x);
      }

      int AddBackY(double y1, double y2) {
        GamR::TK::Gate y(y1, y2);
        return AddBackY(y);
      }

      int AddBackDiag(GamR::TK::Gate x, GamR::TK::Gate y) {
        fBackDiagX.push_back(x);
        fBackDiagY.push_back(y);
        return 0;
      }

      int AddBackDiag(double x1, double y1, double x2, double y2) {
        GamR::TK::Gate x(x1, x2);
        GamR::TK::Gate y(y1, y2);
        return AddBackDiag(x, y);
      }

      int AddBackBack(GamR::TK::Gate x, GamR::TK::Gate y) {
        fBackBackX.push_back(x);
        fBackBackY.push_back(y);
        return 0;
      }

      int AddBackBack(double x1, double y1, double x2, double y2) {
        GamR::TK::Gate x(x1, x2);
        GamR::TK::Gate y(y1, y2);
        return AddBackBack(x, y);
      }      

      BackSub2D(TH2D *hist);
      
      int SetPeak(TCanvas *canvas);
      int AddBackX(TCanvas *canvas);
      int AddBackY(TCanvas *canvas);
      int AddBackBack(TCanvas *canvas);
      int AddBackDiag(TCanvas *canvas);

      TH2D *Subtract(TH2D *hist);
      
      double GetPeakArea();
      double GetPeakAreaError();
      double GetPeakCounts();
      double GetPeakCountsError();

      
    };
  }
}

#endif
