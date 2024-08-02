#ifndef GAMR_ABBREVIATIONS
#define GAMR_ABBREVIATIONS

#include <TH1.h>
#include <TCanvas.h>

#include <spect/Integral.hh>
#include <spect/Cut.hh>
#include <spect/Fit.hh>
#include <spect/Display.hh>
#include <spect/Transform.hh>
#include <spect/Calibrate.hh>
#include <toolkit/Gate.hh>
#include <toolkit/Peak.hh>


//////////
// HELP //
//////////
void help(std::string topic="");

////////////
// GATING //
////////////

TH1D *gx(TCanvas *canvas = gPad->GetCanvas());
TH1D *gy(TCanvas *canvas = gPad->GetCanvas());
TH1D *bsx(TCanvas *canvas = gPad->GetCanvas());
TH1D *bsy(TCanvas *canvas = gPad->GetCanvas());
TH1D *bsx(TCanvas *canvas, const char *name);
TH1D *bsy(TCanvas *canvas, const char *name);

///////////
// PEAKS //
///////////
void pfprint();
void pfconf();
void pfsave();
void pfsave(std::string filename);
GamR::Spect::PeakFit *pf(TCanvas *canvas = gPad->GetCanvas(), Option_t *foption = "", Option_t *option = "");
GamR::TK::BPeak *bp(TCanvas *canvas = gPad->GetCanvas(), Option_t *foption = "", Option_t *option="sl");
GamR::TK::BPeak *cbp(TCanvas *canvas = gPad->GetCanvas());

std::pair<double, double> ig(TCanvas *canvas = gPad->GetCanvas());
std::pair<double, double> igbs(TCanvas *canvas = gPad->GetCanvas());

std::pair<double, double> ct(TCanvas *canvas = gPad->GetCanvas());
std::pair<double, double> ctbs(TCanvas *canvas = gPad->GetCanvas());

TSpectrum* fp(TCanvas *canvas = gPad->GetCanvas(), double sigma = 2, Option_t *option="", double threshold = 0.05);

//////////////////////////
// VIEWING/MANIPULATING //
//////////////////////////

//1-D
void ls();
void sp(int i, Option_t *option = "hist");
void px(TVirtualPad *canvas = gPad->GetCanvas());
void py(TVirtualPad *canvas = gPad->GetCanvas());
void os(std::vector<int> indexes, TCanvas *canvas = NULL, Option_t *option = "hist");
void os(std::vector<TH1*> hists, TCanvas *canvas = NULL, Option_t *option = "hist");
void os(int iStart, int iStop, TCanvas *canvas = NULL, Option_t *option = "hist");
void os(TH2 *hist, int iStart, int iStop);
void os(TH2 *hist, std::vector<int> indices);
void os(int i2D, int iStart, int iStop);
void os(std::vector<std::string> files, std::string name, int iX, Option_t *option = "hist");
void os(std::vector<std::string> files, std::string name, Option_t *option = "hist");
void ss(std::vector<int> indexes, TCanvas *canvas = NULL, Option_t *option = "hist");
void ss(std::vector<TH1*> hists, TCanvas *canvas = NULL, Option_t *option = "hist");
void ss(int iStart, int iStop, TCanvas *canvas = NULL, Option_t *option = "hist");
void ss(TH2 *hist, int iStart, int iStop);
void ss(int i2D, int iStart, int iStop);
void ss(std::vector<std::string> files, std::string name, int iX, Option_t *option = "hist");
void ss(std::vector<std::string> files, std::string name, Option_t *option = "hist");
void lin(TVirtualPad *canvas = NULL);
void log(TVirtualPad *canvas = NULL);
void zx(double low, double high, TVirtualPad *canvas = NULL);
void zy(double low, double high, TVirtualPad *canvas = NULL);
void uzx(TVirtualPad *canvas = NULL);
void uzy(TVirtualPad *canvas = NULL);
void uz(TVirtualPad *canvas = NULL);
std::pair<double, double> ca(TVirtualPad *canvas = NULL, double sigma = 2);
std::pair<double, double> ca2(TVirtualPad *canvas = NULL);
std::pair<double, double> ca(TH1 *hist, double lowEst, double highEst, double lowEn, double highEn, double sigma);
TH1 *add(std::vector<TH1*> hists, const char *name = "sum");
TH1 *add(std::vector<int> hists, const char *name = "sum");
TH1 *add(int iStart, int iStop, const char *name = "sum");
TH1 *rb(TH1 *hist, int rebin);
void rb(TVirtualPad *canvas = NULL, int rebin = 2);
void ns(TVirtualPad *canvas = NULL, Option_t *option = "");
void nsbs(TVirtualPad *canvas = NULL);
void rn(TVirtualPad *canvas = NULL);

//2-D
void ls2();
void sp2(int i, Option_t *option = "colz2");
TH2 *add2(std::vector<TH2*> hists, const char *name = "sum");
TH2 *add2(std::vector<int> hists, const char *name = "sum");
TH2 *add2(int iStart, int iStop, const char *name = "sum");
TH2 *rbx(TH2 *hist, int rebin);
void rbx(TVirtualPad *canvas = NULL, int rebin = 2);
TH2 *rby(TH2 *hist, int rebin);
void rby(TVirtualPad *canvas = NULL, int rebin = 2);
void cc(TH2 *hist, int ncontours=20, double bias=0.2);
void cc(TVirtualPad *canvas=NULL, int ncontours=20, double bias=0.2);


#endif
