#ifndef GAMR_SPECT_DISPLAY_HH
#define GAMR_SPECT_DISPLAY_HH

#include <vector>

#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>

namespace GamR {
  namespace Spect {
    std::vector<TH1*> List1DSpectra(bool quiet=false);
    std::vector<TH2*> List2DSpectra(bool quiet=false);
    void Draw(int i, Option_t *option = "hist");
    void Draw2D(int i, Option_t *option = "colz2");
    void OverlaySpectra(std::vector<int> display_indexes, TCanvas *canvas = NULL, Option_t *option = "hist");
    void OverlaySpectra(int iStart, int iStop, TCanvas *canvas = NULL, Option_t *option = "hist");
    void OverlaySpectra(std::vector<TH1*> hists, TCanvas *canvas = NULL, Option_t *option = "hist");
    void OverlaySpectra(TH2 *hist, int iStart, int iStop, Option_t *option = "hist");
    void OverlaySpectra(TH2 *hist, std::vector<int> indices, Option_t *option = "hist");
    void OverlaySpectra(int i2D, int iStart, int iStop, Option_t *option = "hist");
    void OverlaySpectra(std::vector<std::string> files, std::string name, int iX, Option_t *option = "hist");
    void OverlaySpectra(std::vector<std::string> files, std::string name, int iXstart, int iXstop, Option_t *option = "hist");
    void OverlaySpectra(std::vector<std::string> files, std::string name, Option_t *option = "hist");
    void StackSpectra(std::vector<int> display_indexes, TCanvas *canvas = NULL, Option_t *option = "hist");
    void StackSpectra(int iStart, int iStop, TCanvas *canvas = NULL, Option_t *option = "hist");
    void StackSpectra(std::vector<TH1*> hists, TCanvas *canvas = NULL, Option_t *option = "hist");
    void StackSpectra(TH2 *hist, int iStart, int iStop, Option_t *option = "hist");
    void StackSpectra(int i2D, int iStart, int iStop, Option_t *option = "hist");
    void StackSpectra(std::vector<std::string> files, std::string name, int iX, Option_t *option = "hist");
    void StackSpectra(std::vector<std::string> files, std::string name, Option_t *option = "hist");
    void ContourCalc(TH2 *hist, int ncontours=20, double bias=0.2);
    void ContourCalc(TVirtualPad *canvas = NULL, int ncontours=20, double bias = 0.2);
    void LinAll(TVirtualPad *canvas = NULL);
    void LogAll(TVirtualPad *canvas = NULL);
    void ZoomAllX(double low, double high, TVirtualPad *canvas = NULL);
    void ZoomAllY(double low, double high, TVirtualPad *canvas = NULL);
    void UnZoomAllX(TVirtualPad *canvas = NULL);
    void UnZoomAllY(TVirtualPad *canvas = NULL);

    void NormSpectra(TVirtualPad *canvas = NULL, Option_t *option = "");
    void NormSpectraBackSub(TVirtualPad *canvas = NULL);
    void Rename(TVirtualPad *canvas = NULL);
  }
}

#endif
