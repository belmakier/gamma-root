/* General computational utility functions */
/* Tim Gray - timothy.gray@anu.edu.au */

#include <chrono>
#include <iostream>

#include <TMarker.h>

#include "Utilities.hh"

namespace GamR {
  namespace Utils {
    /**
       Function to calculate n!/10^n for up to n=79

       @return n!/10^n
    */
    double Fac10(int n)
    {
      /* implemented from DCOSUBS.f90
         calculates n!/10^n */
      double fac = 1.0;
      if (n == 0) {
        return 1;
      } else if (n > 79) {
        std::cout << "Can't calculate n! for n>79" << std::endl;
        return -1;
      } else if (n < 0) {
        std::cout << "Can't calculate n! for n<0" << std::endl;
        return -1;
      }
      for (int i = 1; i <= n; ++i) {
        fac = fac * (double)i / 10.0;
      }
      return fac;
    }

    /*
    void GetClick(TVirtualPad *canvas)
    {
      canvas->GetCanvas()->FeedbackMode(kTRUE);

      int event = canvas->GetEvent();

      if (event != 1) {
        return;
      }
      double x = canvas->AbsPixeltoX(canvas->GetEventX());
      double y = canvas->AbsPixeltoY(canvas->GetEventY());

      double xmin;
      double ymin;
      double xmax;
      double ymax;
      canvas->GetRangeAxis(xmin, ymin, xmax, ymax);

      if (x <= xmin || x >= xmax || y <= ymin || y >= ymax) {
        return;
      } else {
        TMarker *marker = new TMarker(x, y, 0);
        marker->Draw();
      }
    }
    */

    void Clicker::GetClick(int event, int x, int y, TObject *selected) {
      if (waiting==true) { return; }
      if ( event != 1 ) { return; }
      TCanvas *c = (TCanvas*)gTQSender;
      px = x;
      py = y;
      cx = c->AbsPixeltoX(x);
      cy = c->AbsPixeltoY(y);

      double xmin;
      double ymin;
      double xmax;
      double ymax;
      c->GetRangeAxis(xmin, ymin, xmax, ymax);

      if (cx <= xmin || cx >= xmax || cy <= ymin || cy >= ymax) {
        return;
      } else {
        waiting=true; //guarantee that only one marker is created per "WaitPrimitive" call
        TMarker *marker = new TMarker(cx, cy, 0);
        marker->Draw();
      }
    }

    void Clicker::GetDrawClick(int event, int x, int y, TObject *selected) {
      if (waiting==true) { return; }
      TCanvas *c = (TCanvas*)gTQSender;
      if ( event == 51 ) {
        int n = line->GetN();
        if (n > 0) {
          line->SetPoint(n-1, c->AbsPixeltoX(x), c->AbsPixeltoY(y));
          c->Modified(kTRUE);
          c->Update();
        }
      }
      if ( event != 1 ) { return; }
      px = x;
      py = y;
      cx = c->AbsPixeltoX(x);
      cy = c->AbsPixeltoY(y);
      line->AddPoint(cx,cy);
      c->Modified(kTRUE);
      c->Update();
      //this is the next point which will be modified
      line->AddPoint(cx,cy);

      double xmin;
      double ymin;
      double xmax;
      double ymax;
      c->GetRangeAxis(xmin, ymin, xmax, ymax);

      if (cx <= xmin || cx >= xmax || cy <= ymin || cy >= ymax) {
        return;
      } else {
        waiting=true; //guarantee that only one marker is created per "WaitPrimitive" call
        TMarker *marker = new TMarker(cx, cy, 0);
        marker->Draw();
      }
    }

    int Clicker::GetClicks(TVirtualPad *canvas, int n, std::vector<std::string> &messages, int draw/*=0*/) {  
      if (draw==1) {
        line = new TGraph();
        line->SetLineColor(kRed);
        line->SetMarkerStyle(kFullCircle);
        line->SetMarkerColor(kRed);
        line->Draw("same LP");
      }
      xs.clear();
      ys.clear();
      if (draw) {
        canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "GamR::Utils::Clicker", this, "GetDrawClick(Int_t,Int_t,Int_t,TObject*)");
      }
      else {
        canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "GamR::Utils::Clicker", this, "GetClick(Int_t,Int_t,Int_t,TObject*)");
      }
      TObject *obj = NULL;
      int exit = 0;
      int i=-1;
      while (true) {
        ++i;
        if (n>0 && i>=n) { break; }
        if (exit == 1 ) { break; }
        if (i<messages.size()) {
          std::cout << messages[i] << std::endl;
        }
        else if (n<0 && messages.size()>0 ) {
          std::cout << messages[0] << std::endl;
        }
        while (true) {
          waiting=false;
          obj = canvas->WaitPrimitive();
          if (!obj) { exit = 1; break; }
          if (strncmp(obj->ClassName(),"TMarker",7)==0) {
            delete obj;
            xs.push_back(cx);
            ys.push_back(cy);
            break;
          }
        }
      }
      if (draw) {
        line->RemovePoint(line->GetN());
        canvas->Update();
        canvas->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", this, "GetDrawClick(Int_t,Int_t,Int_t,TObject*)");
      }
      else {
        canvas->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", this, "GetClick(Int_t,Int_t,Int_t,TObject*)");
      }
      return exit;
    }

    TH1D *GetHist1D(TVirtualPad *canvas) {
      int nHists = 0;
      TH1D *hist = NULL;
      TList *list = canvas->GetListOfPrimitives();
      for (int i = 0; i < list->GetEntries(); i++) {
        if (strncmp(list->At(i)->ClassName(), "TH1", 3) == 0) {
          if (nHists == 0) {
            hist = (TH1D *)list->At(i);
          }
          nHists = nHists + 1;
        }
      }
      if (!hist) {
        //std::cout << "no histogram found in Canvas!" << std::endl;
        return NULL;
      }
      // if (nHists > 1) {        
      //   std::cout << "Warning: Canvas has more than one histogram!" << std::endl;
      // }
      return hist;
    }

    std::vector<TH1D*> GetHists1D(TVirtualPad *canvas) {
      int nHists = 0;
      std::vector<TH1D*> hists;
      TList *list = canvas->GetListOfPrimitives();
      for (int i = 0; i < list->GetEntries(); i++) {
        if (strncmp(list->At(i)->ClassName(), "TH1", 3) == 0) {
          hists.push_back((TH1D *)list->At(i));
          nHists = nHists + 1;
        }
      }
      if (hists.size() == 0) {
        //std::cout << "no histogram found in Canvas!" << std::endl;
        return hists;
      }
      return hists;
    }
    
    TH2D *GetHist2D(TVirtualPad *canvas) {
      int nHists = 0;
      TH2D *hist = NULL;
      TList *list = canvas->GetListOfPrimitives();
      for (int i = 0; i < list->GetEntries(); i++) {
        if (strncmp(list->At(i)->ClassName(), "TH2", 3) == 0) {
          hist = (TH2D *)list->At(i);
          nHists = nHists + 1;
        }
      }
      if (!hist) {
        //std::cout << "no histogram found in Canvas!" << std::endl;
        return NULL;
      }
      if (nHists > 1) {
        //std::cout << "Warning: Canvas has more than one histogram!" << std::endl;
      }
      return hist;
    }

    int wrresult(char *out, float value, float err, int minlen)
    {
      int n;
      char *c;

      /* append nicely-formatted " value(error)" to string out
         minlen = requested minimum length of out at completion
         returns new length of out string */
      /* from radware */

      c = out + strlen(out);
      if (err < 0.00005f) {
        sprintf(c, " %.4f", value);
        c = out + strlen(out);
        while (*(c - 1) == '0' && *(c - 2) == '0')
          c--;
        strcpy(c, "(0)");
      } else if (err < 0.0025f) {
        sprintf(c, " %.4f(%.0f)", value, err * 10000.0f);
      } else if (err < 0.025f) {
        sprintf(c, " %.3f(%.0f)", value, err * 1000.0f);
      } else if (err < 0.25f) {
        sprintf(c, " %.2f(%.0f)", value, err * 100.0f);
      } else if (err < 2.5f) {
        sprintf(c, " %.1f(%.0f)", value, err * 10.0f);
      } else {
        sprintf(c, " %.0f(%.0f)", value, err);
      }
      for (n = strlen(out); n < minlen; n++) {
        strcat(out, " ");
      }
      return n;
    } /* wrresult */

    std::string wrresult(double value, double error) {
      char out_char[2048];
      *out_char = '\0';      
      wrresult(out_char, value, error, 0);
      std::string out(out_char);
      return out;
    }

    // Routine to convert a C++ string into a fortran character array. Don't forget to delete memory after use.
		char *c_to_f_str(std::string strin)
		{
			char *inp = new char[80];
			for(int x=0;x<80;x++) inp[x] = ' ';
			if(strin.size()<80)
        {
          for(int x=0;x<strin.size();x++) inp[x] = strin[x];
        }
			else
        {
          for(int x=0;x<80;x++) inp[x] = strin[x];
        }
			
			return inp;
		}

    //This computes the Simpson's-rule integral cross an array of values
		double Simps(double *y, int n, double dx)
		{
			double yint = 0;
			yint = y[0] + y[n];
			for(int i=1; i<n; i++) yint += y[i] * double(i%2 + 1) * 2.;
			yint *= dx/3.;
			
			return yint;
		}
    std::complex<double> **Simps(std::complex<double> ***rho, int n, double dx)
		{
			std::complex<double> **rhoint = new std::complex<double>*[3];
			for(int k=0; k<3; k++) rhoint[k] = new std::complex<double>[5];
			for(int k=0; k<3; k++)
        {
          for(int q=0; q<=k*2; q++) {
            rhoint[k][q] = std::complex<double>(0,0);
            rhoint[k][q] = rho[0][k][q] + rho[n][k][q];
            for(int i=1; i<n; i++) {
              rho[i][k][q] *= double(i%2 + 1) * 2.;
              rhoint[k][q] += rho[i][k][q];
            }
            rhoint[k][q] *= dx/3.;
          }
        }
			
			return rhoint;
		}

    std::string getline(std::ifstream &f)
		{
			if(f.fail()) return "";
			else {
				std::string ans;
				f >> ans;
				return ans;
			}
    }

		int catcherr(std::string inp, double &val, bool require_positive /* = true */) {
      try { val = std::stod(inp); }
			catch(const std::invalid_argument& ia) {
				std::cout << "\tInvalid entry. Must be numerical." << std::endl;
				return 1;
			}
			if(val<0 && require_positive) {
				std::cout << "\tInvalid entry. Must be >0." << std::endl;
				return 2;
			}
			return 0;
    }

    int catcherr(std::string inp, float &val, bool require_positive /* = true */) {
      try { val = std::stof(inp); }
			catch(const std::invalid_argument& ia) {
				std::cout << "\tInvalid entry. Must be numerical." << std::endl;
				return 1;
			}
			if(val<0 && require_positive) {
				std::cout << "\tInvalid entry. Must be >0." << std::endl;
				return 2;
			}
			return 0;
    }

    int catcherr(std::string inp, int &val, bool require_positive /* = true */) {
      try { val = std::stoi(inp); }
			catch(const std::invalid_argument& ia) {
				std::cout << "\tInvalid entry. Must be numerical." << std::endl;
				return 1;
			}
			if(val<0 && require_positive) {
				std::cout << "\tInvalid entry. Must be >0." << std::endl;
				return 2;
			}
			return 0;
    }

    int GetInput(std::string prompt, double &val, bool require_positive /* = true */) {
      std::string inp;
      while (true) {
        std::cout << prompt << " [" << val << "]: ";
        std::getline(std::cin, inp);
        if(inp.empty()) { break; }
        if(!catcherr(inp, val, require_positive)) { break; }
      }
      return 0;
    }

    int GetInput(std::string prompt, float &val, bool require_positive /* = true */) {
      std::string inp;
      while (true) {
        std::cout << prompt << " [" << val << "]: ";
        std::getline(std::cin, inp);      
        if(inp.empty()) { break; }        
        if(!catcherr(inp, val, require_positive)) { break; }
      }
      return 0;
    }
    int GetInput(std::string prompt, int &val, bool require_positive /* = true */) {
      std::string inp;
      while (true) {
        std::cout << prompt << " [" << val << "]: ";
        std::getline(std::cin, inp);
        if(inp.empty()) { break; }
        if(!catcherr(inp, val, require_positive)) { break; }
      }
      return 0;
    }

    int GetNPads(TVirtualPad *pad) {
      //count the number of pads in pad
      if (!pad) return 0;
      Int_t npads = 0;
      TObject *obj;
      TIter next(pad->GetListOfPrimitives());
      while ((obj = next())) {
        if (obj->InheritsFrom(TVirtualPad::Class())) npads++;
      }
      
      return npads;
    }

  } // namespace Utils
} // namespace GamR
