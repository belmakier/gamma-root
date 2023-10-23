/* STD */
#include <fstream>
#include <iostream>
#include <sstream>

/* GAMR */
#include "IO.hh"

namespace GamR {
  namespace Spect {

    std::string ToText(const TH1 *h, std::string outfile, std::string delimiter)
    {
      std::stringstream ss;
      ss << "#ROOT TH1 in ASCII format" <<std::endl;
      ss << "#name : " << h->GetName() << "   title : " << h->GetTitle() << std::endl;
      ss << "#x-axis : " << h->GetXaxis()->GetTitle() << "   y-axis : " << h->GetYaxis()->GetTitle() << std::endl;
      ss << "#x" << delimiter << "count" << delimiter << "error\n";
      for (int i = 0; i < h->GetNbinsX(); ++i) {
        ss << h->GetBinCenter(i) << delimiter;
        ss << h->GetBinContent(i) << delimiter;
        ss << h->GetBinError(i) << "\n";
      }

      if (!outfile.empty()) {
        std::ofstream file(outfile);
        file << ss.str();
        file.close();
      }

      return ss.str();
    }

    std::string ToText(const TH2 *h, std::string outfile, std::string delimiter, int binx, int biny)
    {
      std::stringstream ss;
      ss << "#ROOT TH2 in ASCII format" <<std::endl;
      ss << "#name : " << h->GetName() << "   title : " << h->GetTitle() << std::endl;
      ss << "#x-axis : " << h->GetXaxis()->GetTitle() << "   y-axis : " << h->GetYaxis()->GetTitle() << std::endl;
      ss << "#x" << delimiter << "y" << delimiter << "count" << delimiter << "error\n";
      int maxx = h->GetNbinsX();
      int maxy = h->GetNbinsY();
      if (binx > 0) { maxx = binx; }
      if (biny > 0) { maxy = biny; }
      for (int i = 0; i < maxx; ++i) {
        for (int j = 0; j < maxy; ++j) {
          ss << h->GetXaxis()->GetBinCenter(i) << delimiter;
          ss << h->GetYaxis()->GetBinCenter(j) << delimiter;
          ss << h->GetBinContent(i,j) << delimiter;          
          ss << h->GetBinError(i,j) << "\n";
        }
        ss << "\n";
      }

      if (!outfile.empty()) {
        std::ofstream file(outfile);
        file << ss.str();
        file.close();
      }

      return ss.str();
    }

    std::string ToText(const TGraphErrors *g, std::string outfile, std::string delimiter)
    {
      std::stringstream ss;
      ss << "#ROOT TGraphErrors in ASCII format" <<std::endl;
      ss << "#name : " << g->GetName() << "   title : " << g->GetTitle() << std::endl;
      ss << "#x" << delimiter << "y" << delimiter << "yerror\n";
      for (int i = 0; i < g->GetN(); ++i) {
        double x;
        double y;
        g->GetPoint(i,x,y);
        ss << x << delimiter;
        ss << y << delimiter;
        ss << g->GetErrorY(i) << "\n";
      }

      if (!outfile.empty()) {
        std::ofstream file(outfile);
        file << ss.str();
        file.close();
      }

      return ss.str();
    }

    std::string ToText(const TGraph *g, std::string outfile, std::string delimiter)
    {
      std::stringstream ss;
      ss << "#ROOT TGraph in ASCII format" <<std::endl;
      ss << "#name : " << g->GetName() << "   title : " << g->GetTitle() << std::endl;
      ss << "#x" << delimiter << "y\n";
      for (int i = 0; i < g->GetN(); ++i) {
        double x;
        double y;
        g->GetPoint(i,x,y);
        ss << x << delimiter;
        ss << y << std::endl;
      }

      if (!outfile.empty()) {
        std::ofstream file(outfile);
        file << ss.str();
        file.close();
      }

      return ss.str();
    }

    std::string ToText(const TGraph *g, int ID, std::string outfile, std::string delimiter)
    {
      std::stringstream ss;
      //ss << "#x" << delimiter << "y\n";
      ss << "#ROOT TGraph in ASCII format" <<std::endl;
      ss << "#name : " << g->GetName() << "   title : " << g->GetTitle() << std::endl;
      ss << ID << delimiter << g->GetN() << std::endl;
      for (int i = 0; i < g->GetN(); ++i) {
        double x;
        double y;
        g->GetPoint(i,x,y);
        ss << x << delimiter;
        ss << y << std::endl;
      }

      if (!outfile.empty()) {
        std::ofstream file(outfile, std::ios_base::app);
        file << ss.str();
        file.close();
      }

      return ss.str();
    }

    std::string ToText(const TF1* f, std::string outfile, std::string delimiter)
    {
      std::stringstream ss;
      ss << "#ROOT TF1 in ASCII format" <<std::endl;
      ss << "#name : " << f->GetName() << "   title : " << f->GetTitle() << std::endl;;
      ss << "#x" << delimiter << "y\n";

      double xlow, xhigh;
      f->GetRange(xlow,xhigh);
      for (int i = 0; i < f->GetNpx(); ++i) {
	double x = xlow + i*(xhigh-xlow)/(f->GetNpx()-1.0);
	ss << x << delimiter << f->Eval(x) << std::endl;
      }

      if (!outfile.empty()) {
	std::ofstream file(outfile);
	file << ss.str();
	file.close();
      }

      return ss.str();
    }

    void ToBin(const TH2 *h, std::string outfile, int padx, int pady)
    {
      FILE *file = fopen(outfile.c_str(), "wb");
      for (int i=1; i<=std::max(h->GetNbinsX(), padx); ++i) {
        for (int j=1; j<=std::max(h->GetNbinsY(), pady); ++j) {
          short int conts = 0;
          if (i <=h->GetNbinsX() && j <= h->GetNbinsY()) {
            conts = (short int)h->GetBinContent(i,j);
          }
          fwrite(&conts, sizeof(short int), 1, file);
        }
      }
      fclose(file);      
    }

    void ToBin(const TH1 *h, std::string outfile)
    {
      FILE *file = fopen(outfile.c_str(), "wb");
      for (int i=0; i<h->GetNbinsX(); ++i) {
        int conts = (int)h->GetBinContent(i);
        fwrite(&conts, sizeof(int), 1, file);
      }    
      fclose(file);      
    }

    void ToSPE(const TH1 *h, std::string outfile) 
    {
      /* write spectra in gf3 format */

      char buf[32];
      int  c1 = 1, rl = 0;
      char namesp[8];

      int j=outfile.size();
      FILE *file = fopen(outfile.c_str(), "wb");
      strncpy(namesp, outfile.c_str(), 8);
      if (j < 8) memset(&namesp[j], ' ', 8-j);

      int idim = h->GetNbinsX();

#define W(a,b) { memcpy(buf + rl, a, b); rl += b; }
      W(namesp,8); W(&idim,4); W(&c1,4); W(&c1,4); W(&c1,4);
#undef W

      fwrite(&rl, 4, 1, file);
      fwrite(buf, rl, 1, file);
      fwrite(&rl, 4, 1, file);

      fwrite(&idim, 4, 1, file);
      for (int i=0; i<h->GetNbinsX(); ++i) {
        int conts = (int)h->GetBinContent(i);
        fwrite(&conts, sizeof(int), 1, file);
      }
      fwrite(&idim, 4, 1, file);
  
      fclose(file);
    }

    TH1D FromText(std::string s, std::string name) {
      FILE *file = fopen(s.c_str(), "ra");
      std::stringstream ss;
      char cline[2048];

      std::vector<double> x_data;
      std::vector<double> y_data;
      std::vector<double> y_err;
      
      while(std::fgets(cline, sizeof cline, file)!=NULL) {
        std::string line(cline);
        if (line.size() == 0) { continue; }
        if (line[0] == '#') { continue; }
        if (line[0] == ';') { continue; }
        if (line[0] == '!') { continue; }

        ss.clear();
        ss.str(line);

        double x,y,err;

        ss >> x;
        ss >> y;
        ss >> err;

        x_data.push_back(x);
        y_data.push_back(y);
        y_err.push_back(err);
      }

      int n = x_data.size();
      //assuming constant bin width;
      double bin_width = x_data[1]-x_data[0];
      std::cout << bin_width << std::endl;
      std::cout << x_data[0] << "   " << x_data[1] << std::endl;
      double start = x_data[0]-bin_width/2.0;
      double stop = x_data[x_data.size()-1]+bin_width/2.0;
      
      TH1D hist(name.c_str(), name.c_str(), n, start, stop);
      for (int i=0; i<n; ++i) {
        hist.SetBinContent(i+1, y_data[i]);
        hist.SetBinError(i+1, y_err[i]);
      }
      return hist;      
    }

    TH1D *FromBin(std::string s, std::string name, std::string title, int nx, double low, double high, int size) {
      TH1D *hist = new TH1D(name.c_str(), title.c_str(), nx, low, high);
      FILE *fp = fopen(s.c_str(), "r");
      if (fp == NULL) { std::cerr << "Error, cannot open file " << s << std::endl; return NULL; }

      fseek(fp, 0L, SEEK_END);
      int ydim = (ftell(fp) / size ) / nx;
      if (ydim != 1) { std::cerr << "Error, wrong file size " << s << std::endl; fclose(fp); return NULL; }

      int data[nx];
      rewind(fp);
      if (fread(data, nx*size, 1, fp) != 1) { std::cerr << "Error reading file" << std::endl; fclose(fp); return NULL; }
      for (int i=1; i<=nx; ++i) {
        hist->SetBinContent(i,data[i-1]);
        hist->SetBinError(i,std::sqrt(data[i-1]));
      }
      fclose(fp);
      return hist;
    }

    TH2D *FromBin(std::string s, std::string name, std::string title,
                  int nx, double xlow, double xhigh,
                  int ny, double ylow, double yhigh,
                  int size) {
      
      FILE *fp = fopen(s.c_str(), "r");
      if (fp == NULL) { std::cerr << "Error, cannot open file " << s << std::endl; return NULL; }

      fseek(fp, 0L, SEEK_END);
      int ydim = (ftell(fp) / size ) / nx;
      if (ny > 0) {
        if (ydim != ny) { std::cerr << "Error, wrong file size " << s << std::endl; fclose(fp); return NULL; }
      }
      else {
        //check if integer
        if (ydim * size * nx != ftell(fp)) {
          std::cerr << "Error, wrong file size, not evenly divisible " << s << std::endl; fclose(fp); return NULL;
        }
        std::cout << "Detected " << ydim << " rows" << std::endl;
        ny = ydim;
      }
      if (ylow == yhigh) {
        ylow = 0;
        yhigh = ny;
      }
      TH2D *hist = new TH2D(name.c_str(), title.c_str(), nx, xlow, xhigh, ny, ylow, yhigh);

      int data[nx];
      rewind(fp);

      for (int j=1; j<=ny; ++j) {
        if (fread(data, nx*size, 1, fp) != 1) { std::cerr << "Error reading file" << std::endl; fclose(fp); return NULL; }
        for (int i=1; i<=nx; ++i) {
          hist->SetBinContent(i,j,data[i-1]);
          hist->SetBinError(i,j,std::sqrt(data[i-1]));
        }
      }
      fclose(fp);
      return hist;
    }
    
    TCutG* CutFromText(std::string s, std::string name) {
      FILE *file = fopen(s.c_str(), "ra");
      std::stringstream ss;
      char cline[2048];

      std::vector<double> x_data;
      std::vector<double> y_data;
      
      while(std::fgets(cline, sizeof cline, file)!=NULL) {
        std::string line(cline);
        if (line.size() == 0) { continue; }
        if (line[0] == '#') { continue; }
        if (line[0] == ';') { continue; }

        ss.clear();
        ss.str(line);

        double x,y,err;

        ss >> x;
        ss >> y;

        x_data.push_back(x);
        y_data.push_back(y);
      }

      int n = x_data.size();
      //assuming constant bin width;

      TCutG *cut = new TCutG();
      cut->SetName(name.c_str());

      for (int i=0; i<n; ++i) {
        cut->SetPoint(i, x_data[i], y_data[i]);
      }
      return cut;      
    }

  } // namespace Spect
} // namespace GamR
