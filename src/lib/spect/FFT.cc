#include <TF1.h>

#include "FFT.hh"
#include "Transform.hh"

namespace GamR {
  namespace Spect {
    TH1D* FFT(TH1 *hist, const char *name, double low, double high, FFTWindow wind/*=FFTWindow::BOX*/) {
      int binStart = hist->FindBin(low);
      int binStop = hist->FindBin(high);
      double start = hist->GetBinLowEdge(binStart);
      double stop = hist->GetBinLowEdge(binStop + 1);      

      //make and populate restricted histogram
      TH1D *cut_hist = new TH1D("", "", binStop - binStart + 1, start, stop);
      for (int i=binStart; i<=binStop; ++i) {
        cut_hist->SetBinContent(i-binStart+1, hist->GetBinContent(i));
        cut_hist->SetBinError(i-binStart+1, hist->GetBinError(i));        
      }

      TH1D *window_hist = (TH1D*)cut_hist->Clone("");
      int N = cut_hist->GetNbinsX();

      TF1 *window = new TF1("window", "([2] - [3]*cos(2*TMath::Pi()*(x-[0])/([1])))", cut_hist->GetBinLowEdge(1), 2*cut_hist->GetBinLowEdge(N)-cut_hist->GetBinLowEdge(N-1));

      window->SetParameter(4, N);
      window->SetParameter(0, cut_hist->GetBinLowEdge(1));
      window->SetParameter(1, (2*cut_hist->GetBinLowEdge(N)-cut_hist->GetBinLowEdge(N-1)-cut_hist->GetBinLowEdge(1)));

      if ( wind == FFTWindow::HANN ) {
        window->SetParameter(2, 0.5);
        window->SetParameter(3, 0.5);
        window_hist->Multiply(window);
      }
      else if ( wind == FFTWindow::HAMMING ) {
        window->SetParameter(2, 0.54);
        window->SetParameter(3, 0.46);
        window_hist->Multiply(window);
      }

      delete window;

      //transform to frequency
      TH1D *out_hist = NULL;
      out_hist = (TH1D*)window_hist->FFT(out_hist, "MAG");

      ScaleLabelsLinear(out_hist, 1.0/(window_hist->GetBinLowEdge(window_hist->GetNbinsX())+window_hist->GetBinWidth(window_hist->GetNbinsX())-window_hist->GetBinLowEdge(1)), 0);

      //renormalise
      out_hist->Scale(1.0/std::sqrt(window_hist->GetNbinsX()));
      out_hist->SetName(name);

      delete window_hist;
      
      return out_hist;
    }
  }
}
