#include <TLegend.h>

#include <spect/Cut.hh>

#include "AngCorr.hh"

namespace GamR {
  namespace AngDist {
    /**
       Calculates the appropriate Ak coefficient, using either Fk coefficients for pure transitions or Ak coefficients for mixed transitions (mixing the lowest two allowed multipolarities)

       @param k Order of coefficient
       @param delta1 Mixing ratio of first transition, ignored if transition is pure
       @param delta2 Mixing ratio of second transition, ignored if transition is pure
       @return Ak coefficient
    */
    double AngCorr::Ak(double k, double delta1, double delta2)
    {
      double first = 0;
      double second = 0;

      int mult1 = 0;
      int mult2 = 0;
      for (int i=abs(spin1-spin2); i<=abs(spin1+spin2); ++i)
        {
          if (mult1 == 0) {
            mult1 = i;
          }
          else {
            mult2 = i;
            break;
          }
        }    
      if (mult2 == 0)
        {
          first = GamR::AngDist::Fk(k, spin1, (double)mult1, (double)mult1, spin2);
        }
      else
        {
          first = GamR::AngDist::Ak(k, spin2, (double)mult1, (double)mult2, spin1, -delta1);
        }

      mult1 = 0;
      mult2 = 0;
      for (int i=abs(spin2-spin3); i<=abs(spin2+spin3); ++i)
        {
          if (mult1 == 0) {
            mult1 = i;
          }
          else {
            mult2 = i;
            break;
          }
        }
        
      if (mult2 == 0)
        {
          second = GamR::AngDist::Fk(k, spin3, (double)mult1, (double)mult1, spin2);
        }
      else
        {
          second = GamR::AngDist::Ak(k, spin2, (double)mult1, (double)mult2, spin3, delta2);
        }
          
      return first*second;
    }

    int AngCorr::Mixed(double s1, double s2)
    {
      int mult1 = 0;
      int mult2 = 0;
      for (int i=abs(s1-s2); i<=abs(s1+s2); ++i)
        {
          if (mult1 == 0) {
            mult1 = i;
          }
          else {
            mult2 = i;
            break;
          }
        }
      if (mult2==0 || mult2>2) return 0;
      else return 1;
    }

    int AngCorr::Mixed(int i)
    {
      if (i==1) return Mixed1();
      else if (i==2) return Mixed2();
      else {
        std::cout << "bad argument! " << i << std::endl;
        return -1;
      }
    }

    void AngCorrFit::SetData(std::vector<double> angs, std::vector<TH2D*> hists, GamR::Nucleus::Transition peak1, GamR::Nucleus::Transition peak2, TH1D *angNorm)
    {
      fColors = {kBlack, kBlue, kRed, kGreen, kMagenta};
      for (int i=0; i<hists.size(); ++i) {
        TH1D *hist = GamR::Spect::BackgroundSubtractY(hists[i], peak1, "temp");
        double peak = peak2.Apply(hist);
        if (peak < 0) { std::cout << angs[i] << "   " << peak << std::endl; }
        double error = peak2.ApplyError(hist);
        fAngles.push_back(angs[i]);
        double norm = angNorm->GetBinContent(angNorm->FindBin(angs[i]));
        fIntensities.push_back(peak/norm);
        fErrors.push_back(error/norm);
      }      
      fixDelta.push_back(0);
      fixDelta.push_back(0);
      fDel.push_back(0);
      fDel.push_back(0);
    }

    AngCorrFit::AngCorrFit(std::vector<double> angs, std::vector<TH2D*> hists, GamR::Nucleus::Transition peak1, GamR::Nucleus::Transition peak2, TH1D *angNorm)
    {
      SetData(angs, hists, peak1, peak2, angNorm);
      std::vector<double> Qks = {1.0, 1.0, 1.0, 1.0, 1.0};
      Qk = new GamR::AngDist::SolidAttenuation(Qks);
    }
    
    AngCorrFit::AngCorrFit(std::vector<double> angs, std::vector<TH2D*> hists, GamR::Nucleus::Transition peak1, GamR::Nucleus::Transition peak2, TH1D *angNorm, const char *name, const char *title) : TNamed(name, title)
    {
      SetData(angs, hists, peak1, peak2, angNorm);
      std::vector<double> Qks = {1.0, 1.0, 1.0, 1.0, 1.0};
      Qk = new GamR::AngDist::SolidAttenuation(Qks);
    }
    
    void AngCorrFit::ErasePoint(double ang)
    {
      for (int i=0; i<GetNPoints(); ++i) {
        if (fAngles[i]==ang) {
          fAngles.erase(fAngles.begin()+i);
          fIntensities.erase(fIntensities.begin()+i);
          fErrors.erase(fErrors.begin()+i);
        }
      }
    }

    double AngCorrFit::Average()
    {
      double av;
      for (int i=0; i<GetNPoints(); ++i) {
        av += fIntensities[i]/GetNPoints();
      }
      return av;
    }
    
    TGraphErrors* AngCorrFit::GetGraph()
    {
      TGraphErrors *graph = new TGraphErrors();
      for (int i=0; i<GetNPoints(); ++i) {
        graph->SetPoint(i, fAngles[i], fIntensities[i]);
        graph->SetPointError(i, 0, fErrors[i]);
      }
      graph->SetTitle(GetTitle());
      return graph;
    }

    TGraphErrors *AngCorrFit::GetDispGraph(double start, double interval)
    {
      int count = 0;
      std::vector<double> lowedges;
      while (start < 180) {
        lowedges.push_back(start);
        start += interval;
      }
      int nDispPoints = lowedges.size();
      std::vector<double> dispangs(lowedges.size());
      std::vector<double> dispints(lowedges.size());
      std::vector<double> invvars(lowedges.size());

      for (int i=0; i<GetNPoints(); ++i) {
        //find which 'bin' it belongs in
        for (int p=0; p<nDispPoints; ++p) {
          if (fAngles[i] < lowedges[p]) { continue; }
          if (p < nDispPoints - 1) {
            if (fAngles[i] >= lowedges[p+1] ) {
              continue;
            }
          }            
          double oldSumX = dispangs[p]*invvars[p];
          double oldSumY = dispints[p]*invvars[p];
          double newSumX = oldSumX + fAngles[i]/pow(fErrors[i], 2);
          double newSumY = oldSumY + fIntensities[i]/pow(fErrors[i], 2);
          double newVar = invvars[p] + pow(1.0/fErrors[i],2);
          dispangs[p] = newSumX/newVar;
          dispints[p] = newSumY/newVar;
          invvars[p] = newVar;
          
          break;
        }                
      }
      //now make the actual graph
      TGraphErrors *graph = new TGraphErrors();
      for (int p=0; p<nDispPoints; ++p) {
        //check there is actual data there
        if (invvars[p]>0) {
          graph->SetPoint(graph->GetN(), dispangs[p], dispints[p]);
          graph->SetPointError(graph->GetN()-1, 0, sqrt(1.0/invvars[p]));
        }
      }
      graph->SetTitle(GetTitle());
      return graph;        
    }
    
    void AngCorrFit::Fit()
    {
      fCorrs.clear();
      fCorrFuncs.clear();
      fChiGraphs.clear();
      fDelta1.clear();
      fDelta2.clear();
      fChiSquared.clear();
      for (int i = 0; i<spin1s.size(); ++i) {
        for (int j = 0; j<spin2s.size(); ++j) {
          for (int k = 0; k<spin3s.size(); ++k) {
            std::string name((std::string)"AngCorr"+std::to_string(spin1s[i])+"_"+std::to_string(spin2s[j])+"_"+std::to_string(spin3s[k]));
            AngCorr *corr = new AngCorr(spin1s[i], spin2s[j], spin3s[k], Qk);
            TF1 *corrFunc = new TF1(name.c_str(), corr, 0, 181, 3, "GamR::AngDist::AngCorr");            
            TGraph *chiGraph = new TGraph();
            chiGraph->SetLineColor(fColors[fCorrs.size()%fColors.size()]);
            corrFunc->SetLineColor(fColors[fCorrs.size()%fColors.size()]);
            TGraphErrors *graph = GetGraph();
            corrFunc->SetParameter(0, Average());
            int varpar = 0;  //parameter to vary
            int fixpar = 0;  //parameter to fix

            if ( fDel[0] == 1 ) {
              varpar = 2;
              fixpar = 1;
            }
            else if ( fDel[1] == 1 ) {
              varpar = 1;
              fixpar = 2;
            }
            else if (corr->Mixed1() + corr->Mixed2() == 2) {
              if ( fDel[0] == 0 && fDel[1] == 0 ) {
                //neither have been fixed,
                //probably shouldn't do that (yet)
                std::cout << "Two mixed transitions with no fixed delta?" << std::endl;
                return;
              }
            }
            else if (corr->Mixed1() + corr->Mixed2() == 0 ){
              //two pure transitions, doesn't matter which way around we are
              varpar = 1;
              fixpar = 2;
            }
            else if (corr->Mixed1()) {
              //first transition is mixed
              varpar = 1;
              fixpar = 2;              
            }
            else if (corr->Mixed2()) {
              fixpar = 1;
              varpar = 2;
            }
                        
            //both have been fixed
            if (fDel[varpar-1] == 1) {
                //delta has been fixed
                //note that this is not really a situation I anticipate happening
                corrFunc->SetParameter(1, fixDelta[varpar-1]);
                corrFunc->FixParameter(1, fixDelta[varpar-1]);
                graph->Fit(corrFunc, "Q");                
                chiGraph->SetPoint(0, fixDelta[varpar-1], corrFunc->GetChisquare());
                varpar = 0;
              }

            if (corr->Mixed(varpar) == 0) {
              //"varying" transition is actually pure
              corrFunc->SetParameter(1, fixDelta[0]);
              corrFunc->SetParameter(2, fixDelta[1]);
              corrFunc->FixParameter(1, fixDelta[0]);
              corrFunc->FixParameter(2, fixDelta[1]);
              graph->Fit(corrFunc, "Q");
              chiGraph->SetPoint(0, -TMath::Pi()/2.0+0.01, corrFunc->GetChisquare());
              chiGraph->SetPoint(1, TMath::Pi()/2.0-0.01, corrFunc->GetChisquare());
              varpar = 0;
            }

            //loop over delta
            if (varpar != 0) {
              int count = 0;            
              for (double d=-TMath::Pi()/2.0+0.01; d<TMath::Pi()/2-0.01; d+=0.3333333*0.01*(TMath::Pi()-0.02))
                {      
                  double delta = TMath::Tan(d);
                  corrFunc->SetParameter(varpar, delta);
                  corrFunc->FixParameter(varpar, delta);
                  //std::cout << "Fixing delta " << fixpar << " = " << fixDelta[fixpar-1] << std::endl;
                  corrFunc->SetParameter(fixpar, fixDelta[fixpar-1]);
                  corrFunc->FixParameter(fixpar, fixDelta[fixpar-1]);

                  graph->Fit(corrFunc, "Q");
                  chiGraph->SetPoint(count, d, corrFunc->GetChisquare());
                  ++count;
                }
            }
            //best delta
            double d;
            double chi; 
            chiGraph->GetPoint(TMath::LocMin(chiGraph->GetN(), chiGraph->GetY()), d, chi);            
            double delta = TMath::Tan(d);
            fChiSquared.push_back(chi);

            double thresh = chi+1;

            double low = -1e9;
            double high = 1e9;
            double tand_last;
            double chi2_last;
            chiGraph->GetPoint(0, tand_last, chi2_last);
            for (int ig=1; ig<chiGraph->GetN(); ++ig) {
              double tand;
              double chi2;
              chiGraph->GetPoint(ig, tand, chi2);

              if (chi2_last > thresh && chi2 < thresh) {
                low = TMath::Tan(tand);
              }
              if (chi2_last < thresh && chi2 > thresh) {
                high = TMath::Tan(tand);
              }

              tand_last = tand;
              chi2_last = chi2;
            }

            if (varpar != 0) {
              corrFunc->SetParameter(varpar, delta);
              corrFunc->FixParameter(varpar, delta);
              corrFunc->SetParameter(fixpar, fixDelta[fixpar-1]);
              corrFunc->FixParameter(fixpar, fixDelta[fixpar-1]);
            }

            graph->Fit(corrFunc, "Q");                        
            if (varpar == 1) {
              fDelta1.push_back(delta);
              fDelta1Err.push_back({low - delta, high - delta});
              fDelta2.push_back(fixDelta[1]);
            }
            else if (varpar == 2) {
              fDelta1.push_back(fixDelta[0]);
              fDelta2Err.push_back({low - delta, high - delta});
              fDelta2.push_back(delta);
            }
            else {
              fDelta1.push_back(fixDelta[0]);
              fDelta2.push_back(fixDelta[1]);
            }
            fCorrs.push_back(corr);
            fCorrFuncs.push_back(corrFunc);
            fChiGraphs.push_back(chiGraph);
          }
        }
      }
    }

    TMultiGraph* AngCorrFit::GetChiGraph()
    {
      TMultiGraph *multgraph = new TMultiGraph();
      for (int i=0; i<GetNCombs(); ++i) {
        multgraph->Add(fChiGraphs[i]);
      }
      multgraph->SetTitle(GetTitle());
      return multgraph;
    }

    void AngCorrFit::DrawChiGraph(TCanvas *c1, double ylow, double yhigh)
    {
      TMultiGraph *multgraph = GetChiGraph();
      c1->cd();

      //shading for confidence level
      double fillareaX[4]={-TMath::Pi()/2.0, -TMath::Pi()/2.0, TMath::Pi()/2.0, TMath::Pi()/2.0};
      double fillareaY[4]={0, 66.35, 66.35, 0};
      TGraph *fillgraph = new TGraph(4, &fillareaX[0], &fillareaY[0]);
      fillgraph->SetFillColor(kYellow);
      fillgraph->SetFillStyle(3001);
      
      multgraph->GetXaxis()->SetTitle("arctan(delta)");
      multgraph->GetYaxis()->SetTitle("chi^2");  
      multgraph->Draw("AC");

      //draw a legend
      TLegend *legend = new TLegend(0.75, 0.75, 0.95, 0.95);
      for (int i=0; i<GetNCombs(); ++i) {        
        TString entry;
        entry.Form("%2.1f->%2.1f->%2.1f", fCorrs[i]->spin1, fCorrs[i]->spin2, fCorrs[i]->spin3);
        legend->AddEntry(fChiGraphs[i], entry.Data());
      }
      legend->Draw();
      multgraph->GetYaxis()->SetRangeUser(ylow, yhigh);
      fillgraph->Draw("F");
    }

    void AngCorrFit::DrawAngCorr(TCanvas *c1, double start, double interval)
    {
      TGraph *graph = GetDispGraph(start, interval);
      c1->cd();
      graph->Draw("A*");
      graph->GetXaxis()->SetLimits(0, 185);
      TLegend *legend = new TLegend(0.9, 0.7, 1.0, 0.9);
      for (int i=0; i<GetNCombs(); ++i) {
        fCorrFuncs[i]->Draw("same");
        TString entry;
        entry.Form("%2.1f->%2.1f->%2.1f", fCorrs[i]->spin1, fCorrs[i]->spin2, fCorrs[i]->spin3);
        legend->AddEntry(fCorrFuncs[i], entry.Data());
      }
      legend->Draw();
    }

    void AngCorrFit::Save(std::string filename, double start, double interval) {
      std::ofstream ofile(filename);
      TGraph *graph = GetDispGraph(start, interval);
      for (int i = 0; i<graph->GetN(); ++i) {
        double x, y, xerr, yerr;
        graph->GetPoint(i, x, y);
        xerr = graph->GetErrorX(i);
        yerr = graph->GetErrorY(i);
        ofile << x << "   " << y << "   " << xerr << "   " << yerr << std::endl;
      }
      ofile << std::endl << std::endl;
      for (int i=0; i<=180; ++i) {
        ofile << i << "   ";
        for (int j=0; j<GetNCombs(); ++j) {
          ofile << fCorrFuncs[j]->Eval(i) << "   ";
        }
        ofile << std::endl;
      }
      ofile.close();
    }

    void AngCorrFit::SaveChiGraph(std::string filename)
    {
      std::ofstream ofile(filename);

      for (int i=-90; i<=90; ++i) {
        ofile << i << "   ";
        for (int j=0; j<fChiGraphs.size(); ++j) {        
          TGraph *g = fChiGraphs[j];
          if (!g) { ofile.close(); return; }
          ofile << g->Eval(i*TMath::Pi()/180.0) << "   ";
        }
        ofile << std::endl;
      }
      ofile.close();
    }

  }
}
