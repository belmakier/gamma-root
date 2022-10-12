#include <string>
#include <algorithm>
#include <iostream>

#include <TStyle.h>
#include <TH2F.h>
#include <TGaxis.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TText.h>
#include <TLatex.h>
#include <TString.h>
#include <TArrow.h>
#include <TMinuit.h>

#include "LevelSchemeDraw.hh"
#include <utils/Utilities.hh>

// ignoring npar, gin, iflag in GlobalChiSquare::doit
// TMinuit expects these extra variables that we don't use
#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace GamR {
  namespace Nucleus {
    namespace LevelSchemeDraw {      

      void State::Paint(Option_t *option) {
        if (extension) {
          extline->SetX1(fExtLeft);
          extline->SetX2(fExtRight);
          extline->SetY1(fDrawPos);
          extline->SetY2(fDrawPos);
          extline->SetLineColor(kGray+1);
          extline->SetLineWidth(3);
          extline->SetLineStyle(2);
          extline->Paint();
        }

        TAttLine::Modify();
        
        double x[2];
        double y[2];
        x[0] = fLeft;
        x[1] = fRight;
        y[0] = fDrawPos;
        y[1] = fDrawPos;
        gPad->PaintPolyLine(2, &x[0], &y[0], option);

        int py0 = gPad->YtoPixel(0);
        fLeftLabel->SetText(fLeft, gPad->AbsPixeltoY((gPad->YtoAbsPixel(fLabelPos))-5), fLeftLab.c_str());
        fLeftLabel->SetTextFont(42);
        fLeftLabel->SetTextSize(textsize);
        fLeftLabel->SetTextColor(GetLineColor());
        fLeftLabel->Paint();

        fRightLabel->SetText(fRight, gPad->AbsPixeltoY((gPad->YtoAbsPixel(fLabelPos))-5), fRightLab.c_str());
        fRightLabel->SetTextFont(42);
        fRightLabel->SetTextAlign(31);
        fRightLabel->SetTextSize(textsize);
        fRightLabel->SetTextColor(GetLineColor());
        fRightLabel->Paint();        
      }

      Int_t State::DistancetoPrimitive(Int_t px, Int_t py) {
        //distance to main line
        double dx = 0;
        if (px > gPad->XtoAbsPixel(fRight)) { dx = px - gPad->XtoAbsPixel(fRight); }
        else if (px < gPad->XtoAbsPixel(fLeft)) { dx = gPad->XtoAbsPixel(fLeft) - px; }
        double dy = gPad->YtoAbsPixel(fDrawPos) - py;
        double main_dist = sqrt(dx*dx + dy*dy);

        return main_dist;
      }

      void State::ExecuteEvent(Int_t event, Int_t px, Int_t py)
      {
        if (!gPad)
          return;
        int kMaxDiff = 20;

        if (!gPad->IsEditable())
          return;

        switch (event) {
        case kMouseMotion:
          p1 = false;                    
          if (DistancetoPrimitive(px, py) < kMaxDiff) {
            gPad->SetCursor(kPointer);
            px1 = gPad->XtoAbsPixel(fLeft);
            px2 = gPad->XtoAbsPixel(fRight);
            pxold = px;
            p1 = true;            
            return;
          }          
          break;
        case kButton1Motion:
          if (p1) {
            fLeft = gPad->AbsPixeltoX(px)-gPad->AbsPixeltoX(pxold) + gPad->AbsPixeltoX(px1);
            fRight = gPad->AbsPixeltoX(px)-gPad->AbsPixeltoX(pxold) + gPad->AbsPixeltoX(px2);
          }
          gPad->Modified(kTRUE);
          gPad->Update();
          break;
        }
      }

      double Transition::XtoAbsPixel(double x) {
        double xscale = (gPad->XtoAbsPixel(gPad->GetUxmax()) - gPad->XtoAbsPixel(gPad->GetUxmin()) + 1.0)/
          (gPad->GetUxmax() - gPad->GetUxmin());
        return gPad->XtoAbsPixel(gPad->GetUxmin())-0.5 + xscale * x;
      }

      double Transition::YtoAbsPixel(double y) {
        double yscale = (gPad->YtoAbsPixel(gPad->GetUymax()) - gPad->YtoAbsPixel(gPad->GetUymin()) + 1.0)/
          (gPad->GetUymax() - gPad->GetUymin());
        return gPad->YtoAbsPixel(gPad->GetUymin())+0.5 + yscale * y;
      }     

      double Transition::AbsPixeltoX(double xpix) {
        double xscale = (gPad->XtoAbsPixel(gPad->GetUxmax()) - gPad->XtoAbsPixel(gPad->GetUxmin()) + 1.0)/
          (gPad->GetUxmax() - gPad->GetUxmin());
        return (xpix - gPad->XtoAbsPixel(gPad->GetUxmin())-0.5)/xscale;
      }

      double Transition::AbsPixeltoY(double ypix) {
        double yscale = (gPad->YtoAbsPixel(gPad->GetUymax()) - gPad->YtoAbsPixel(gPad->GetUymin()) + 1.0)/
          (gPad->GetUymax() - gPad->GetUymin());
        return (ypix - gPad->YtoAbsPixel(gPad->GetUymin())+0.5)/yscale;
      }     
      
      double Transition::GetLength() {
        double xscale = (gPad->XtoAbsPixel(gPad->GetUxmax()) - gPad->XtoAbsPixel(gPad->GetUxmin()) + 1.0)/
          (gPad->GetUxmax() - gPad->GetUxmin());
        double yscale = (gPad->YtoAbsPixel(gPad->GetUymax()) - gPad->YtoAbsPixel(gPad->GetUymin()) + 1.0)/
          (gPad->GetUymax() - gPad->GetUymin());
        double pixdx = xscale * (GetX2() - GetX1());
        double pixdy = yscale * (GetY2() - GetY1());
        
        /*
        double pixx1 = gPad->XtoAbsPixel(GetX1());
        double pixx2 = gPad->XtoAbsPixel(GetX2());
        double pixy1 = gPad->YtoAbsPixel(GetY1());
        double pixy2 = gPad->YtoAbsPixel(GetY2());
        */

        //double pixdx = pixx2 - pixx1; //gPad->XtoAbsPixel(dx);
        //double pixdy = pixy2 - pixy1; //gPad->YtoAbsPixel(dy);

        
        double pixlen = std::sqrt(pixdx*pixdx + pixdy*pixdy);
        return pixlen;
      }

      double Transition::GetPerpTheta() {
        /*
        double pixx1 = gPad->XtoAbsPixel(GetX1());
        double pixx2 = gPad->XtoAbsPixel(GetX2());
        double pixy1 = gPad->YtoAbsPixel(GetY1());
        double pixy2 = gPad->YtoAbsPixel(GetY2());
        
        double pixdx = pixx2 - pixx1; //gPad->XtoAbsPixel(dx);
        double pixdy = pixy2 - pixy1; //gPad->YtoAbsPixel(dy);
        */

        double xscale = (gPad->XtoAbsPixel(gPad->GetUxmax()) - gPad->XtoAbsPixel(gPad->GetUxmin()) + 1.0)/
          (gPad->GetUxmax() - gPad->GetUxmin());
        double yscale = (gPad->YtoAbsPixel(gPad->GetUymax()) - gPad->YtoAbsPixel(gPad->GetUymin()) + 1.0)/
          (gPad->GetUymax() - gPad->GetUymin());
        double pixdx = xscale * (GetX2() - GetX1());
        double pixdy = yscale * (GetY2() - GetY1());
        
        double pixlen = std::sqrt(pixdx*pixdx + pixdy*pixdy);
        pixdx /= pixlen;
        pixdy /= pixlen;

        double perpthet = std::atan2(pixdx,-pixdy);
        return perpthet;
      }
      
      double Transition::GetWidth() {
        double perpthet = GetPerpTheta();

        return std::max(std::sqrt(std::pow((gPad->YtoAbsPixel(std::sin(perpthet))-gPad->YtoAbsPixel(0.0))*fWidth, 2)
                        + std::pow((gPad->XtoAbsPixel(std::cos(perpthet)) - gPad->XtoAbsPixel(0.0))*fWidth, 2))*fScheme->fWidthScale, 3.0);
      }

      double Transition::GetWidthX() {
        double perpthet = GetPerpTheta();
        double pixwidth = GetWidth();
        return std::cos(perpthet)*pixwidth;
      }

      double Transition::GetWidthY() {
        double perpthet = GetPerpTheta();
        double pixwidth = GetWidth();
        return std::sin(perpthet)*pixwidth;
      }      
      
      double Transition::GetHeadWidth() { return std::max(1.7*GetWidth(), 8.0); }

      double Transition::GetHeadWidthX() {
        double perpthet = GetPerpTheta();
        double pixwidth = GetHeadWidth();
        return std::cos(perpthet)*pixwidth;
      }

      double Transition::GetHeadWidthY() {
        double perpthet = GetPerpTheta();
        double pixwidth = GetHeadWidth();
        return std::sin(perpthet)*pixwidth;
      }

      double Transition::GetHeadLength() { return std::min(0.66*GetHeadWidth(), 0.5*GetLength()); }

      double Transition::GetX1() { return fInitial->fLeft + (fInitial->fRight - fInitial->fLeft) * fStart; }

      double Transition::GetX2() { return fFinal->fLeft + (fFinal->fRight - fFinal->fLeft) * fStop; }

      double Transition::GetY1() { return fInitial->fDrawPos; }

      double Transition::GetY2() { return fFinal->fDrawPos; }
      
      void Transition::PaintArrow() {  //here some maths happens to draw a nice arrow
        //first work out start and end points in world coordinates
        double x1 = fInitial->fLeft + (fInitial->fRight - fInitial->fLeft) * fStart;
        double x2 = fFinal->fLeft + (fFinal->fRight - fFinal->fLeft) * fStop;

        double y1 = fInitial->fDrawPos;
        double y2 = fFinal->fDrawPos;

        double dx = x2 - x1;
        double dy = y2 - y1;

        double length = std::sqrt(dx*dx + dy*dy);
        dx /= length;
        dy /= length;
        
        double pixx1 = XtoAbsPixel(x1);
        double pixx2 = XtoAbsPixel(x2);
        double pixy1 = YtoAbsPixel(y1);
        double pixy2 = YtoAbsPixel(y2);

        //pixy1 = gPad->GetWh() - pixy1;
        //pixy2 = gPad->GetWh() - pixy2;
        
        double pixdx = pixx2 - pixx1; //gPad->XtoAbsPixel(dx);
        double pixdy = pixy2 - pixy1; //gPad->YtoAbsPixel(dy);
       
        
        double pixlen = std::sqrt(pixdx*pixdx + pixdy*pixdy);
        pixdx /= pixlen;
        pixdy /= pixlen;

        double perpthet = std::atan2(pixdx,-pixdy);
        double topwidth = GetWidth()/2.0/std::cos(perpthet);

        //SetPoint(0, gPad->AbsPixeltoX(pixx1 - topwidth), gPad->AbsPixeltoY(pixy1));
        //SetPoint(1, gPad->AbsPixeltoX(pixx1 + topwidth), gPad->AbsPixeltoY(pixy1));
        SetPoint(0, AbsPixeltoX(pixx1 - topwidth), AbsPixeltoY(pixy1));
        SetPoint(1, AbsPixeltoX(pixx1 + topwidth), AbsPixeltoY(pixy1));

        double headposx = x1 + dx*(length);//-GetHeadLength());
        double headposy = y1 + dy*(length);//-GetHeadLength());

        double pixheadposx = XtoAbsPixel(headposx) - pixdx*GetHeadLength();
        double pixheadposy = YtoAbsPixel(headposy) - pixdy*GetHeadLength();

        SetPoint(2, AbsPixeltoX(pixheadposx + GetWidthX()/2.0),
                 AbsPixeltoY(pixheadposy + GetWidthY()/2.0));
        SetPoint(3, AbsPixeltoX(pixheadposx + GetHeadWidthX()/2.0),
                 AbsPixeltoY(pixheadposy + GetHeadWidthY()/2.0));
        SetPoint(4, x2, y2);
        SetPoint(5, AbsPixeltoX(pixheadposx - GetHeadWidthX()/2.0),
                 AbsPixeltoY(pixheadposy - GetHeadWidthY()/2.0));
        SetPoint(6, AbsPixeltoX(pixheadposx - GetWidthX()/2.0),
                 AbsPixeltoY(pixheadposy - GetWidthY()/2.0));
        
        PaintPolyLine(7, GetX(), GetY(), "F");
      }
      
      void Transition::Paint(Option_t *option) {
        TAttLine::Modify();
        TAttFill::Modify();
        
        PaintArrow();

        //paint transition label
        
        TString transition_string;
        transition_string.Form("%3.2g", fWidth);
        fLabel->SetText((GetX1() + GetX2())/2.0, (GetY1() + GetY2())/2.0, transition_string.Data());        
        fLabel->SetTextFont(42);
        //fLabel->SetTextAngle(45);
        fLabel->SetTextSize(textsize);
        fLabel->SetTextAlign(22);
        fLabel->SetTextColor(kBlack);
        UInt_t w, h;
        fLabel->GetBoundingBox(w,h);
        fLabelBox->SetX1(gPad->PixeltoX(gPad->XtoPixel((GetX1() + GetX2())/2.0) - w/2 - 5));
        fLabelBox->SetX2(gPad->PixeltoX(gPad->XtoPixel((GetX1() + GetX2())/2.0) + w/2 + 5));
        fLabelBox->SetY1(gPad->AbsPixeltoY(gPad->YtoAbsPixel((GetY1() + GetY2())/2.0) + h/2 + 5));
        fLabelBox->SetY2(gPad->AbsPixeltoY(gPad->YtoAbsPixel((GetY1() + GetY2())/2.0) - h/2 - 5));

        fLabelBox->SetFillColorAlpha(kWhite, 0.7);
        fLabelBox->Paint();
        
        fLabel->Paint();
        
      }
      
      Int_t Transition::DistancetoPrimitive(Int_t px, Int_t py) {
        //some maths to work out the closest distance to the transition

        double midx = (GetX1() + GetX2())/2.0;
        double midy = (GetY1() + GetY2())/2.0;
        double dx = gPad->XtoAbsPixel(midx) - px;
        double dy = gPad->YtoAbsPixel(midy) - py;
        double main_dist = sqrt(dx*dx + dy*dy);

        double tpx = gPad->XtoAbsPixel(GetX1());
        double bpx = gPad->XtoAbsPixel(GetX2());
        double tpy = gPad->YtoAbsPixel(GetY1());
        double bpy = gPad->YtoAbsPixel(GetY2());

        double d1 = abs(tpx-px) + abs(tpy-py);
        double d2 = abs(bpx-px) + abs(bpy-py);
        
        return std::min(main_dist, std::min(d1, d2));
      }

      void Transition::ExecuteEvent(Int_t event, Int_t px, Int_t py)
      {
        if (!gPad)
          return;
        int kMaxDiff = 20;

        if (!gPad->IsEditable())
          return;

        switch (event) {
        case kMouseMotion:
          {
            
          if (DistancetoPrimitive(px, py) < kMaxDiff) {
            gPad->SetCursor(kPointer);
            //return;
          }

          p1 = false;
          p2 = false;
          px1 = gPad->XtoAbsPixel(GetX1());
          px2 = gPad->XtoAbsPixel(GetX2());
          py1 = gPad->YtoAbsPixel(GetY1());
          py2 = gPad->YtoAbsPixel(GetY2());

          double d1 = abs(px1-px) + abs(py1-py);
          if (d1 < kMaxDiff) {
            px1old = px1;
            p1 = true;
            gPad->SetCursor(kPointer);
            return;
          }

          double d2 = abs(px2-px) + abs(py2-py);
          if (d2 < kMaxDiff) {
            px2old = px2;
            p2 = true;
            gPad->SetCursor(kPointer);
            return;
          }            
          break;
          }
        case kButton1Motion:
          {
          if (p1) {
            double abspos = (gPad->AbsPixeltoX(px)-gPad->AbsPixeltoX(px1old) + gPad->AbsPixeltoX(px1));
            double relpos = (abspos - fInitial->fLeft)/(fInitial->fRight - fInitial->fLeft);
            fStart = relpos;
          }
          if (p2) {
            double abspos = (gPad->AbsPixeltoX(px)-gPad->AbsPixeltoX(px2old) + gPad->AbsPixeltoX(px2));
            double relpos = (abspos - fFinal->fLeft)/(fFinal->fRight - fFinal->fLeft);
            fStop = relpos;
          }
          gPad->Modified(kTRUE);
          gPad->Update();
          break;
          }
        }
      }
            
      void Scheme::Paint(Option_t *option) {       

        //gPad->SetFrameLineColor(0);

        //
        gStyle->SetOptStat(0);
        if (!gPad->GetListOfPrimitives()->Contains(fDrawHist)) {
          fDrawHist->AppendPad();
        }

        /*
        if (!fAxis) {
          fAxis = new TGaxis(0, 0, drawLow, drawHigh , drawLow, drawHigh, 510, "");
          fAxis->AppendPad();  
        
        }
        */


        for (auto &state : fStates) {
          if (!gPad->GetListOfPrimitives()->Contains(&state.second)) {
            state.second.AppendPad();
          }
        }

        for (auto &transition : fTransitions) {
          if (!gPad->GetListOfPrimitives()->Contains(&transition)) {
            transition.AppendPad();
          }
        }
      }


      void Scheme::ReadScheme(std::string filename) {
        std::ifstream infile(filename);

        std::string line;
        while (std::getline(infile, line)) {
          if (line.size() == 0) { continue; }
          if (line[0] == '#') { continue; }
          if (line[0] == ';') { continue; }

          std::stringstream ss(line);

          std::string label;
          ss >> label;

          if (label == "L") {
            //level
            std::string name;
            double energy;
            double left;
            double right;
            std::string leftlab;
            std::string rightlab;

            ss >> name >> energy >> left >> right >> leftlab >> rightlab;

            AddState(name, energy, left, right, leftlab, rightlab);

          }
          else if (label == "E") {
            double extleft, extright;
            std::string name;
            if (ss >> name >> extleft >> extright) {
              fStates[name].SetExtension(extleft, extright);
            }
          }
          else if (label == "T") {
            std::string name_init;
            std::string name_fin;
            double width;
            double start;
            double stop;
            UInt_t color;            

            ss >> name_init >> name_fin >> width >> start >> stop >> color;

            EColor col = static_cast<EColor>(color);

            AddTransition(name_init, name_fin, width, start, stop, col);            
          }
        }
      }

      void Scheme::WriteScheme(std::string filename) {
        std::ofstream outfile(filename);
        for (auto &state : fStates) {
          outfile << std::setw(5) << std::left << "L"
                  << std::setw(10) << std::left << state.second.GetName()
                  << std::setw(10) << std::left << state.second.fEnergy
                  << std::setw(10) << std::left << std::setprecision(5) << state.second.fLeft
                  << std::setw(10) << std::left << std::setprecision(5) << state.second.fRight
                  << std::setw(10) << std::left << state.second.fLeftLab
                  << std::setw(10) << std::left << state.second.fRightLab;
          outfile << std::endl;
        }
        for (auto &state : fStates) {
          if (state.second.extension) {
            outfile << std::setw(5) << std::left << "E"
                    << std::setw(10) << std::left << state.second.GetName()
                    << std::setw(10) << std::left << std::setprecision(5) << state.second.fExtLeft
                    << std::setw(10) << std::left << std::setprecision(5) << state.second.fExtRight << std::endl;
          }
        }

        for (auto &transition : fTransitions) {
          outfile << std::setw(5) << std::left << "T"
                  << std::setw(10) << std::left << transition.fInitial->GetName()
                  << std::setw(10) << std::left << transition.fFinal->GetName()
                  << std::setw(10) << std::left << transition.fWidth
                  << std::setw(10) << std::left << std::setprecision(5) << transition.fStart
                  << std::setw(10) << std::left << std::setprecision(5) << transition.fStop 
                  << std::setw(10) << std::left << transition.GetFillColor() << std::endl;
          
        }
      }

      void State::AddTransition(const char *name_fin, double width, double start, double stop, EColor color) {
        std::string nf(name_fin);
        fScheme->AddTransition(GetName(), nf, width, start, stop, color);
      }
    }
  }
}
