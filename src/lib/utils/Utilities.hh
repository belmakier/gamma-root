/* General computational utility functions */
/* Tim Gray - timothy.gray@anu.edu.au */

#ifndef GAMR_UTILS_UTILITIES_HH
#define GAMR_UTILS_UTILITIES_HH

#include <string>
#include <fstream>
#include <complex>

#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>

namespace GamR {
  /*!
    \addtogroup Utils
    @{
  */

  //! Useful tools for general use. Here goes general utility functions,
  //! conversion libraries, and in anything generally useful but not particularly
  //! physics-y
  namespace Utils {
    double Fac10(int n);
    //void GetClick(TVirtualPad *canvas);

    class Clicker {
      public:
        void GetClick(Int_t,Int_t,Int_t,TObject*);
        int px, py;
        double cx, cy;
    };

    TH1D *GetHist1D(TVirtualPad *canvas);
    std::vector<TH1D*> GetHists1D(TVirtualPad *canvas);
    TH2D *GetHist2D(TVirtualPad *canvas);
    int wrresult(char *out, float value, float err, int minlen);
    std::string wrresult(double value, double err);
    // Routine to convert a C++ string into a fortran character array. Don't forget to delete memory after use.
		char *c_to_f_str(std::string strin);
    //This computes the Simpson's-rule integral cross an array of values
		double Simps(double *y, int n, double dx);
    //This computes the Simpson's-rule integral across an array of tensors
		std::complex<double> **Simps(std::complex<double> ***rho, int n, double dx);
    std::string getline(std::ifstream &f);
		int catcherr(std::string inp, double &val, bool require_positive = true);
    int catcherr(std::string inp, float &val, bool require_positive = true);
    int catcherr(std::string inp, int &val, bool require_positive = true);
    int GetInput(std::string prompt, double &val, bool require_positive = true);
    int GetInput(std::string prompt, float &val, bool require_positive = true);
    int GetInput(std::string prompt, int &val, bool require_positive = true);
    int GetNPads(TVirtualPad *pad);

  } // namespace Utils
  /*! @} */
} // namespace GamR

#endif
