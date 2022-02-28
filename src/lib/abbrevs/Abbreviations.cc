#include "Abbreviations.hh"

////////////
// GATING //
////////////

TH1D *gx(TCanvas *canvas) { return GamR::Spect::GateX(canvas); }
TH1D *gy(TCanvas *canvas) { return GamR::Spect::GateY(canvas); }
TH1D *bsx(TCanvas *canvas) { return GamR::Spect::BackgroundSubtractX(canvas); }
TH1D *bsy(TCanvas *canvas) { return GamR::Spect::BackgroundSubtractY(canvas); }
TH1D *bsx(TCanvas *canvas, const char* name) { return GamR::Spect::BackgroundSubtractX(canvas, name); }
TH1D *bsy(TCanvas *canvas, const char* name) { return GamR::Spect::BackgroundSubtractY(canvas, name); }

///////////
// PEAKS //
///////////
void pfprint() { GamR::Spect::gFitGuesses->Print(); }
void pfconf() { GamR::Spect::gFitGuesses->Set(); }
void pfsave() { GamR::Spect::gFitGuesses->Save(); }
void pfsave(std::string filename) { GamR::Spect::gFitGuesses->Save(filename); }
GamR::Spect::PeakFit *pf(TCanvas *canvas, Option_t *foption , Option_t *option ) { return GamR::Spect::FitPeaks(canvas, foption, option); }
GamR::TK::BPeak *bp(TCanvas *canvas, Option_t *foption, Option_t *option) { return GamR::TK::FitBPeak(canvas, foption, option); }
GamR::TK::BPeak *cbp(TCanvas *canvas) { return GamR::TK::ClickBPeak(canvas); }

std::pair<double, double> ig(TCanvas *canvas ) { return GamR::Spect::Integral(canvas); }
std::pair<double, double> igbs(TCanvas *canvas ) { return GamR::Spect::IntegralBS(canvas); }

std::pair<double, double> ct(TCanvas *canvas ) { return GamR::Spect::Counts(canvas); }
std::pair<double, double> ctbs(TCanvas *canvas ) { return GamR::Spect::CountsBS(canvas); }

TSpectrum* fp(TCanvas *canvas , double sigma, Option_t *option, double threshold) { return GamR::Spect::FindPeaks(canvas, sigma, option, threshold); }

//////////////////////////
// VIEWING/MANIPULATING //
//////////////////////////

//1-D
void ls() { GamR::Spect::List1DSpectra(); }
void sp(int i, Option_t *option) { GamR::Spect::Draw(i, option); }
void px(TVirtualPad *canvas ) { GamR::Spect::ProjX(canvas); }
void py(TVirtualPad *canvas ) { GamR::Spect::ProjY(canvas); }
void os(std::vector<int> indexes, TCanvas *canvas , Option_t *option ) { GamR::Spect::OverlaySpectra(indexes, canvas, option); }
void os(std::vector<TH1*> hists, TCanvas *canvas , Option_t *option ) { GamR::Spect::OverlaySpectra(hists, canvas, option); }
void os(int iStart, int iStop, TCanvas *canvas , Option_t *option ) { GamR::Spect::OverlaySpectra(iStart, iStop, canvas, option); }
void os(TH2 *hist, int iStart, int iStop) { GamR::Spect::OverlaySpectra(hist, iStart, iStop); }
void os(int i2D, int iStart, int iStop) { GamR::Spect::OverlaySpectra(i2D, iStart, iStop); }
void os(std::vector<std::string> files, std::string name, int iX, Option_t *option) { GamR::Spect::OverlaySpectra(files, name, iX, option); }
void os(std::vector<std::string> files, std::string name, Option_t *option) { GamR::Spect::OverlaySpectra(files, name, option); }
void ss(std::vector<int> indexes, TCanvas *canvas , Option_t *option ) { GamR::Spect::StackSpectra(indexes, canvas, option); }
void ss(std::vector<TH1*> hists, TCanvas *canvas , Option_t *option ) { GamR::Spect::StackSpectra(hists, canvas, option); }
void ss(int iStart, int iStop, TCanvas *canvas , Option_t *option ) { GamR::Spect::StackSpectra(iStart, iStop, canvas, option); }
void ss(std::vector<std::string> files, std::string name, int iX, Option_t *option) { GamR::Spect::StackSpectra(files, name, iX, option); }
void ss(std::vector<std::string> files, std::string name, Option_t *option) { GamR::Spect::StackSpectra(files, name, option); }
void ss(TH2 *hist, int iStart, int iStop) { GamR::Spect::StackSpectra(hist, iStart, iStop); }
void ss(int i2D, int iStart, int iStop) { GamR::Spect::StackSpectra(i2D, iStart, iStop); }
void lin(TVirtualPad *canvas ) { GamR::Spect::LinAll(canvas); }
void log(TVirtualPad *canvas ) { GamR::Spect::LogAll(canvas); }
void zx(double low, double high, TVirtualPad *canvas ) { GamR::Spect::ZoomAllX(low, high, canvas); }
void zy(double low, double high, TVirtualPad *canvas ) { GamR::Spect::ZoomAllY(low, high, canvas); }
void uzx(TVirtualPad *canvas ) { GamR::Spect::UnZoomAllX(canvas); }
void uzy(TVirtualPad *canvas ) { GamR::Spect::UnZoomAllY(canvas); }
void uz(TVirtualPad *canvas ) { GamR::Spect::UnZoomAllX(canvas); GamR::Spect::UnZoomAllY(canvas); }
std::pair<double, double> ca(TVirtualPad *canvas , double sigma) { return GamR::Spect::TwoPointCalibrate(canvas, sigma); }
std::pair<double, double> ca(TH1 *hist, double lowEst, double highEst, double lowEn, double highEn, double sigma) { return GamR::Spect::TwoPointCalibrate(hist, lowEst, highEst, lowEn, highEn, sigma); }
TH1 *add(std::vector<TH1*> hists, const char *name ) { return GamR::Spect::Add(hists, name); }
TH1 *add(std::vector<int> hists, const char *name ) { return GamR::Spect::Add(hists, name); }
TH1 *add(int iStart, int iStop, const char *name ) { return GamR::Spect::Add(iStart, iStop, name); }
TH1 *rb(TH1 *hist, int rebin) { return GamR::Spect::Rebin(hist, rebin); }
void rb(TVirtualPad *canvas , int rebin) { GamR::Spect::Rebin(canvas, rebin); }
void ns(TVirtualPad *canvas, Option_t *option) { GamR::Spect::NormSpectra(canvas, option); }
void nsbs(TVirtualPad *canvas) { GamR::Spect::NormSpectraBackSub(canvas); }

//2-D
void ls2() { GamR::Spect::List2DSpectra(); }
void sp2(int i, Option_t *option ) { GamR::Spect::Draw2D(i, option); }
TH2 *add2(std::vector<TH2*> hists, const char *name ) { return GamR::Spect::Add(hists, name); }
TH2 *add2(std::vector<int> hists, const char *name ) { return GamR::Spect::Add2(hists, name); }
TH2 *add2(int iStart, int iStop, const char *name ) { return GamR::Spect::Add2(iStart, iStop, name); }
