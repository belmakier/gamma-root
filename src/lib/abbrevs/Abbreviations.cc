#include "Abbreviations.hh"

//////////
// HELP //
//////////
void help(std::string topic) {
  if (topic.size() == 0) {
    std::cout << "GamR help: " << std::endl;
    std::cout << "help(<topic>)                       - help on specific topic" << std::endl;
    std::cout << "topics include: " << std::endl;
    std::cout << "    abbrevs                         - quick abbreviations for common functions" << std::endl;
    std::cout << "    spect                           - spectroscopy tools" << std::endl;
    std::cout << "    angdist                         - gamma-ray angular distribution and correlations" << std::endl;
    std::cout << "    bateman                         - Bateman equation fitting" << std::endl;
    std::cout << "    efficiency                      - fit efficienties for HPGe detectors and arrays" << std::endl;
    std::cout << "    nucleus                         - fit and draw level schemes" << std::endl;
  }
  else if (topic == "abbrevs") {
    std::cout << "GamR Abbreviations help: " << std::endl;
    std::cout << "Abbreviations are commonly used functions designed to be used from the ROOT command line. They " << std::endl;
    std::cout << "will typically call a more verbosely named GamR function in the appropriate namespace. Look at " << std::endl;
    std::cout << "src/abbrevs/Abbreviations.hh and src/abbrevs/Abbreviations.cc to see the specific functions " << std::endl;
    std::cout << "they are calling." << std::endl << std::endl;
    std::cout << "    px(), py()                      - projections into X- or Y- axes, operates on current Canvas" << std::endl;
    std::cout << "    gx(), gy()                      - interactive gating on X- or Y-axes" << std::endl;
    std::cout << "    bsx(), bsy()                    - interactive background subtraction" << std::endl;
    std::cout << std::endl;
    std::cout << "    pf()                            - fit (Gaussian) peaks" << std::endl;
    std::cout << "    pfconf()                        - configure fit parameters" << std::endl;
    std::cout << "    pfprint()                       - print parameters" << std::endl;
    std::cout << "    pfsave()                        - save parameters" << std::endl;
    std::cout << std::endl;
    std::cout << "    bp()                            - \"basic peak\". This sums the counts over a background, " << std::endl;
    std::cout << "                                      which is usually fitted" << std::endl;
    std::cout << "    cbp()                           - \"click basic peak\". As above, but background is a straight" << std::endl;
    std::cout << "                                      line between two clicks on the canvas" << std::endl;
    std::cout << "    ig()                            - integrate between two bounds" << std::endl;
    std::cout << "    igbs()                          - integrate with background subtraction" << std::endl;
    std::cout << "    ct()                            - counts between two bounds" << std::endl;
    std::cout << "    ctbs()                          - counts with background subtraction" << std::endl;
    std::cout << "    fp()                            - \"find peaks\", implementation of ROOTs TSpectrum search" << std::endl;
    std::cout << std::endl;
    std::cout << "    ls()                            - list 1D histograms in current directory" << std::endl;
    std::cout << "    sp(i)                           - draw histogram i" << std::endl;
    std::cout << "    os()                            - overlay 1D histograms. This takes a {list} of indices, histogram" << std::endl;
    std::cout << "                                      pointers, or start and stop indices for sequential lists. Also can" << std::endl;
    std::cout << "                                      do x-slices of a 2D histogram, or a {list} of file names followed by" << std::endl;
    std::cout << "                                      a histogram name (the same in each file)" << std::endl;
    std::cout << "    ss()                            - stack spectra, same arguments as above" << std::endl;
    std::cout << std::endl;
    std::cout << "    lin()                           - linear (y) scale" << std::endl;
    std::cout << "    log()                           - log (y) scale" << std::endl;
    std::cout << "    zx(), zy()                      - zoom to limits on x/y" << std::endl;
    std::cout << "    uzx(), uzy(), uz()              - unzoom" << std::endl;
    std::cout << std::endl;
    std::cout << "    ca()                            - calibrate, returns pair of gain/offset for linear calibration" << std::endl;
    std::cout << std::endl;
    std::cout << "    add()                           - sum lists of spectra together" << std::endl;
    std::cout << "    rb()                            - rebin" << std::endl;
    std::cout << "    ns()                            - \"norm spectra\", normalize to region indicated by clicks" << std::endl;
    std::cout << "    nsbs()                          - as above but with background subtraction" << std::endl;
    std::cout << "    rn()                            - rename currently plotted histogram" << std::endl;
    std::cout << std::endl;
    std::cout << "    ls2()                           - list 2D spectra" << std::endl;
    std::cout << "    sp2(i)                          - plot 2D spectrum by index" << std::endl;
    std::cout << "    add2()                          - add 2D spectra" << std::endl;
    std::cout << std::endl;
  }
  else if ( topic == "spect" ) {
    std::cout << "GamR Spectroscopy help: " << std::endl;
    std::cout << "Spectroscopy tools - calibrations, cuts, display utilities, peak fitting, and I/O to ASCII text formats." << std::endl;
    std::cout << "See also help(\"spect/fitting\")" << std::endl;
    std::cout << "Look in src/lib/spect/ for more details" << std::endl;
  }
  else if ( topic == "spect/fitting" ) {
    std::cout << "Peak fitting is done through the 'pf()' [GamR::Spect::FitPeaks()] or 'bp()' [GamR::TK::FitBPeak()] functions" << std::endl;
    std::cout << std::endl;
    std::cout << "GamR::TK::FitBPeak()" << std::endl << std::endl;
    
    std::cout << "BPeak stands for \'Basic' Peak -- the idea being to extract information about a peak while making no assumption" << std::endl;
    std::cout << "about its shape. This proceeds by defining a peak region and then several background regions: usually at least " << std::endl;
    std::cout << "one on either side of the peak. The background regions are then fit with some function(s), and the extrapolation/" << std::endl;
    std::cout << "interpolation of these into the peak area is used to get the peak area and centroid after subtracting the background" << std::endl << std::endl;
    
    std::cout << "The call signature is" << std::endl << std::endl;

    std::cout << "   bp(canvas, ROOT fitting options, BPeak options)," << std::endl << std::endl;
    
    std::cout << "where the canvas is a ROOT canvas on which the histogram is plotted, and the second two arguments are optional" << std::endl;
    std::cout << "strings. The first is passed to the ROOT TF1::Fit() function (see appropriate ROOT documentation). The second defines" << std::endl;
    std::cout << "what kind of background to fit, and usually contains two characters. The first represents the functional form of the" << std::endl;
    std::cout << "background: " << std::endl;
    std::cout << "   \"c\" : constant" << std::endl;
    std::cout << "   \"l\" : linear" << std::endl;
    std::cout << "   \"q\" : quadratic" << std::endl;
    std::cout << "The second letter represents how the interpolation is conducted:" << std::endl;
    std::cout << "   \"s\" : smooth -- a single function is fitted to the union of all background regions." << std::endl;
    std::cout << "   \"p\" : point -- two background functions are fitted, one above and one below the peak region. These are extrapolated" << std::endl;
    std::cout << "         to the edges of the peak region, and then a straight line between the two intersections is used beneath the peak" << std::endl;
    std::cout << "   \"x\" : step -- two background functions are fitted, and then a smooth interpolation between them using the error " << std::endl;
    std::cout << "         function (erf) connects the two regions" << std::endl <<std::endl;
    std::cout << "The default BPeak option is \"ls\" -- a linear smooth background" << std::endl;
    std::cout << std::endl;
    std::cout << "GamR::Spect::FitPeaks()" << std::endl << std::endl;
    
    std::cout << "This actually fits a functional form to the peak(s). The most basic peak shape is a Gaussian, but this can be modified" << std::endl;
    std::cout << "in several ways -- by adding one or two skewed components, and/or a step underneath the peak. The call signature is:" << std::endl << std::endl;
    
    std::cout << "   pf(canvas, ROOT fitting options, FitPeaks options)," << std::endl << std::endl;
    
    std::cout << "in a similar fashion to bp(). The FitPeak options are:" << std::endl;
    std::cout << "   \"z\"  : quiet mode" << std::endl;
    std::cout << "   \"f\"  : fix widths -- all peaks are fitted with common width/skew/step parameters" << std::endl;
    std::cout << "   \"ff\" : fix widths from file --- the width/skew/step parameters are not fitted but read from a file (see below)" << std::endl;
    std::cout << "   \"q\"  : quadratic background" << std::endl;
    std::cout << "   \"c\"  : constant background" << std::endl;
    std::cout << "   \"q\"  : quadratic background" << std::endl;
    std::cout << "   \"t\"  : one tail (skewed component)" << std::endl;
    std::cout << "   \"g\"  : two tails (two skewed components)" << std::endl;
    std::cout << "   \"s\"  : step" << std::endl;
    std::cout << "   \"e\"  : fix energy of one or more peaks" << std::endl;
    std::cout << "   \"n\"  : no fit --- just create the template function with starting guesses but do not fit" << std::endl << std::endl;
    
    std::cout << "The option \"ff\" requires an additional file named \"FitWidths.dat\" in the current directory. It should contain several" << std::endl;
    std::cout << "rows, each with 7 numbers corresponding to:" << std::endl;
    std::cout << std::endl;
    std::cout << "Energy    Width    Step    Skew    SkewAmp    Skew2    SkewAmp2" << std::endl << std::endl;
    std::cout << "With several rows at different energies, the shapes of the detector response across the whole energy range can be specified." << std::endl;
    std::cout << "The fitting function will read this file and interpolate (linearly) between the energies defining the appropriate shape" << std::endl;
    std::cout << "for the correct region of the spectrum. Thus, the only fitted parameters for each peak are its location (centroid) and " << std::endl;
    std::cout << "its amplitude. An example \"FitWidths.dat\" file can be found in the share folder inside the install directory." << std::endl;      
  }
  else if (topic == "angdist" ) {
    std::cout << "GamR Angdist help: " << std::endl;
    std::cout << "Angular distribution/correlation tools. Formalism for statistical tensors, population parameters, Fk and" << std::endl;
    std::cout << "Ak coefficients, gamma-ray angular distributions and correlations. Fitting angular correlations is here," << std::endl;
    std::cout << "as well as Time-Dependent Perturbed Angular Distributions." << std::endl;
  }
  else if (topic == "bateman" ) {
    std::cout << "GamR Bateman help: " << std::endl;
    std::cout << "For fitting the Bateman equations numerically for an arbitrary feeding/decay scheme" << std::endl;
  }
  else if (topic == "efficiency" ) {
    std::cout << "GamR Efficiency help: " << std::endl;
    std::cout << "Classes for fitting HPGe efficiency curves. Uses the Radware 7-parameter function, can stitch together " << std::endl;
    std::cout << "multiple data sets, do several detectors simultaneously, and optionally anchor to absolute efficiency points" << std::endl;
  }
  else if (topic == "nucleus") {
    std::cout << "GamR Nucleus help: " << std::endl;
    std::cout << "Classes for fitting and drawing level schemes" << std::endl;
  }
  else {
    std::cout << "Unknown topic" << std::endl;
  }
}   
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
void os(TH2 *hist, std::vector<int> indices) { GamR::Spect::OverlaySpectra(hist, indices); }
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
void rn(TVirtualPad *canvas) { GamR::Spect::Rename(canvas); }

//2-D
void ls2() { GamR::Spect::List2DSpectra(); }
void sp2(int i, Option_t *option ) { GamR::Spect::Draw2D(i, option); }
TH2 *add2(std::vector<TH2*> hists, const char *name ) { return GamR::Spect::Add(hists, name); }
TH2 *add2(std::vector<int> hists, const char *name ) { return GamR::Spect::Add2(hists, name); }
TH2 *add2(int iStart, int iStop, const char *name ) { return GamR::Spect::Add2(iStart, iStop, name); }
