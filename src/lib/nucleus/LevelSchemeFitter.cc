#include <string>
#include <algorithm>
#include <iostream>

#include <TStyle.h>
#include <TH2F.h>
#include <TGaxis.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TText.h>
#include <TArrow.h>
#include <TMinuit.h>

#include "LevelSchemeFitter.hh"
#include <utils/Utilities.hh>

// ignoring npar, gin, iflag in GlobalChiSquare::doit
// TMinuit expects these extra variables that we don't use
#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace GamR {
  namespace Nucleus {
    namespace LevelSchemeFitter {      

      void State::Paint(Option_t *option) {
        TAttLine::Modify();
        
        double x[2];
        double y[2];
        x[0] = 0.1;
        x[1] = 0.9;
        y[0] = fDrawPos;
        y[1] = fDrawPos;
        gPad->PaintPolyLine(2, &x[0], &y[0], option);

        x[0] = 0.9;
        x[1] = 0.93;
        y[0] = fDrawPos;
        y[1] = fLabelPos;
        gPad->PaintPolyLine(2, &x[0], &y[0], option);

        x[0] = 0.93;
        x[1] = 0.97;
        y[0] = fLabelPos;
        y[1] = fLabelPos;
        gPad->PaintPolyLine(2, &x[0], &y[0], option);

        std::string energy_string = GamR::Utils::wrresult(fEnergy, fUncertainty);
        int py0 = gPad->YtoPixel(0);
        fLabel->SetText(0.93, gPad->PixeltoY((gPad->YtoPixel(fLabelPos)-2)) - gPad->PixeltoY(py0), energy_string.c_str());
        fLabel->SetTextFont(4);
        fLabel->SetTextSize(15);
        fLabel->SetTextColor(GetLineColor());
        fLabel->Paint();

      }

      Int_t State::DistancetoPrimitive(Int_t px, Int_t py) {
        //distance to main line
        double dx = 0;
        if (px > gPad->XtoAbsPixel(0.9)) { dx = px - gPad->XtoAbsPixel(0.9); }
        else if (px < gPad->XtoAbsPixel(0.1)) { dx = gPad->XtoAbsPixel(0.1) - px; }
        double dy = gPad->YtoAbsPixel(fDrawPos) - py;
        double main_dist = sqrt(dx*dx + dy*dy);

        //distance to label line
        if (px > gPad->XtoAbsPixel(0.97)) { dx = px - gPad->XtoAbsPixel(0.97); }
        else if (px < gPad->XtoAbsPixel(0.93)) { dx = gPad->XtoAbsPixel(0.93) - px; }
        dy = gPad->YtoAbsPixel(fLabelPos) - py;
        double label_dist = sqrt(dx*dx + dy*dy);

        //distance to connecting line
        double connecting_dist = DistancetoLine(px, py,
                                                gPad->XtoAbsPixel(0.93),
                                                gPad->YtoAbsPixel(fDrawPos),
                                                gPad->XtoAbsPixel(0.97),
                                                gPad->YtoAbsPixel(fLabelPos));
        
        return std::min(std::min(main_dist, label_dist), connecting_dist);
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
          if (DistancetoPrimitive(px, py) < kMaxDiff) {
            gPad->SetCursor(kPointer);
            return;
          }
          break;
        }
      }

      void Transition::Paint(Option_t *option) {
        TAttLine::Modify();
        TAttFill::Modify();

        PaintArrow(GetX1(), GetY1(), GetX2(), GetY2(), GetArrowSize(), TArrow::GetOption());

        //paint transition label
        std::string transition_string = GamR::Utils::wrresult(fEnergy, fUncertainty);
        fLabel->SetText(GetX1(), GetY1(), transition_string.c_str());        
        fLabel->SetTextFont(4);
        fLabel->SetTextAngle(45);
        fLabel->SetTextSize(15);
        fLabel->SetTextColor(GetLineColor());
        fLabel->Paint();
        
      }
      
      Int_t Transition::DistancetoPrimitive(Int_t px, Int_t py) {
        //assumes vertical
        
        int xp1 = gPad->XtoAbsPixel(GetX1());
        int yp1 = gPad->YtoAbsPixel(GetY1());
        int xp2 = gPad->XtoAbsPixel(GetX2());
        int yp2 = gPad->YtoAbsPixel(GetY2());

        int dx = abs(xp1 - px);
        int dy = 9999;

        double dist = 9999;
        
        if (py < yp1) { dy = abs(py - yp1); }
        else if (py > yp2) { dy = abs(py - yp2); }
        else { dy = 0; }
        
        dist = dx*dx + dy*dy;
        
        return sqrt(dist);
                       
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
          if (DistancetoPrimitive(px, py) < kMaxDiff) {
            gPad->SetCursor(kPointer);
            return;
          }
          break;
        }
      }
      
      void Scheme::SetIndices() {
        std::vector<State*> states;
        for (auto &state : fStates) {
          states.push_back(&state.second);
        }

        std::sort(states.begin(), states.end(),
                  [](const State *a, const State *b)
                  { 
                    return *a < *b;
                  });

        for (int i=0; i<(int)states.size(); ++i) {
          fStates[states[i]->GetName()].index = i;
        }        
      }

      State *Scheme::GetStateByIndex(int i) {
        for (auto &state : fStates) {
          if (state.second.index==i) {
            return &state.second;
          }
        }
        return NULL;
      }

      double Scheme::GetChiSquared() {
        double chi2 = 0;
        for (auto &transition : fTransitions) {
            //std::cout << "comparing " << transition.fEnergy << " with " << transition.fInitial->fEnergy - transition.fFinal->fEnergy << std::endl;
            chi2 += pow((transition.fEnergy - (transition.fInitial->fEnergy - transition.fFinal->fEnergy))/transition.fUncertainty, 2);
        }
        return chi2;
      }
      
      class Scheme::GlobalChiSquare {
      private:
        static Scheme *p;

      public:
        GlobalChiSquare(Scheme *parent) { p = parent; }

        static void minuit(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
        {
          //std::cout << "function call with " << npar << " parameters" << std::endl;
          f = 0;
          //loop through states to set energies
          for (auto &state : p->fStates) {
            if (state.second.index == 0) { continue; }
            state.second.fEnergy = par[state.second.index-1];
            //std::cout << "state " << state.second.index << "  " << state.second.fEnergy << std::endl;
          }
          f = p->GetChiSquared();
        }
        
      };

      Scheme *Scheme::GlobalChiSquare::p = nullptr;

      void Scheme::Fit() {       
        Int_t npars = (int)fStates.size() - 1;
        std::cout << npars << std::endl;
        auto gMinuit = new TMinuit(npars);

        GlobalChiSquare func(this);
        gMinuit->SetFCN(func.minuit);

        Double_t arglist[10];
        arglist[0] = 1;

        Int_t ierflg = 0; // some error flag ???

        gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
        arglist[0] = 2;
        gMinuit->mnexcm("SET STR", arglist, 1, ierflg);

        Int_t parnum = 0;

        for ( int i=1; i<=npars; ++i ) {
          std::cout << "Setting up level " << i << std::endl;
          double energy = GetStateByIndex(i)->fEnergy;
          gMinuit->mnparm(parnum, ("Level "+std::to_string(i)).c_str(), energy, GetStateByIndex(i)->fUncertainty, 0.8*energy, 1.2*energy, ierflg);
          ++parnum;
        }
                
        /* MINIMIZE */
        //std::cout << gMinuit->GetNumPars() << " parameters in total" << std::endl;
        arglist[0] = 100000; // Max Iterations
        arglist[1] = 1;      // Number of sigma max step
        gMinuit->mnexcm("MINIGRAD", arglist, 2, ierflg);
        //std::cout << gMinuit->GetNumPars() << " parameters in total" << std::endl;
        gMinuit->mnimpr(); // Improve fit by searching for other minima
        //std::cout << gMinuit->GetNumPars() << " parameters " << std::endl;
        gMinuit->mnexcm("HESSE", arglist, 2, ierflg);
        //std::cout << gMinuit->GetNumPars() << " parameters " << std::endl;

        //printf("Level %d :    %8.4f   %7.5f\n", 0, GetStateByIndex(0)->fEnergy, 0.0);          
        for (int i=1; i<=gMinuit->GetNumPars(); ++i) {
          double parVal, parErr;
          gMinuit->GetParameter(i-1, parVal, parErr);
          GetStateByIndex(i)->fEnergy = parVal;
          GetStateByIndex(i)->fUncertainty = parErr;
          //printf("Level %d :    %8.4f   %7.5f\n", i, parVal, parErr);          
        }
        
        delete gMinuit;

      }

      void Scheme::PrintStates() {
        std::vector<State*> states;
        for (auto &state : fStates) {
          states.push_back(&state.second);
        }

        std::sort(states.begin(), states.end(),
                  [](const State *a, const State *b)
                  { 
                    return *a < *b;
                  });


        printf("Printing state energies for %i states\n", (int)states.size());
        for (int i=0; i<(int)states.size(); ++i) {
          printf("Level %d : %10s :   %8.4f   %7.5f\n", states[i]->index, states[i]->GetName(), states[i]->fEnergy, states[i]->fUncertainty);
        }        
      }

      void Scheme::PrintTransitions() {
        printf("Printing %i transitions\n", (int)fTransitions.size());
        for (auto &transition : fTransitions) {
          printf("Transition : %10.4f(%5.3f) vs %8.4f :    %5.2f sigma difference\n", transition.fEnergy, transition.fUncertainty, transition.fInitial->fEnergy - transition.fFinal->fEnergy, (transition.fEnergy - (transition.fInitial->fEnergy - transition.fFinal->fEnergy))/transition.fUncertainty);
        }
      }

      void Scheme::Print() {
        PrintStates();
        printf("\n");
        PrintTransitions();
        double chi2 = GetChiSquared();
        int ndf = (int)fTransitions.size() - (int)fStates.size();
        printf("\n");
        printf("Total states      : %i\n", (int)fStates.size());
        printf("Total transitions : %i\n", (int)fTransitions.size());
        printf("Chi^2             : %10.5f\n", chi2);
        printf("ndf               : %i\n", ndf);
        printf("Chi^2/ndf         : %10.5f\n", chi2/(double)ndf);
      }

      void Scheme::PrintState(std::string name) {
        printf("========================================\n");
        printf("State %s, Index : %d, Energy : % 5.2f\n", name.c_str(), fStates[name].index, fStates[name].fEnergy);
        std::vector<Transition*> inTransitions;
        std::vector<Transition*> outTransitions;
        for (auto &transition : fTransitions) {
          if (*transition.fInitial == fStates[name]) { outTransitions.push_back(&transition); }
          if (*transition.fFinal == fStates[name]) { inTransitions.push_back(&transition); }
        }
        printf("Transitions in : \n");
        for (auto &transition : inTransitions) {
          printf("  % 5.2f\n", transition->fEnergy);
        }
        printf("Transitions out : \n");
        for (auto &transition : outTransitions) {
          printf("  % 5.2f\n", transition->fEnergy);
        }
      }
      
      void Scheme::Paint(Option_t *option) {       

        gPad->SetFrameLineColor(0);
        
        double eLow = drawLow;
        double eHigh = drawHigh;
        SetIndices();
        //get max energy
        std::map<int, State*> range_states;  //states in the energy range, indexed by (global) index
        std::map<int, State*> extra_states;  //extra states that still need to be drawn, indexed by (global) index
        std::vector<int> drawn_indexes;
        double max_energy = 0;
        for (auto &state : fStates) {
          if (state.second.fEnergy < eLow || state.second.fEnergy > eHigh) { continue; }
          else { range_states[state.second.index] = &state.second; drawn_indexes.push_back(state.second.index); }
          if (state.second.fEnergy > max_energy) {
            max_energy = state.second.fEnergy;
          }
        }

        //figure out extra states
        int nTransitions = 0;
        for (auto &state : range_states) {
          for (auto &transition : fTransitions) {
            if (transition.fInitial->index == state.second->index) {
              nTransitions++;
              if (range_states.find(transition.fFinal->index)==range_states.end() && extra_states.find(transition.fFinal->index)==extra_states.end()) {
                extra_states[transition.fFinal->index] = transition.fFinal;
                drawn_indexes.push_back(transition.fFinal->index);
              }              
            }
          }
        }
        
        std::sort(drawn_indexes.begin(), drawn_indexes.end());

        if (drawn_indexes[0] != 0) { drawn_indexes.insert(drawn_indexes.begin(), 0); }
        
        fDrawHist->SetBins(100, 0.0, 1.0, 100, 0.0, (int)((1.1*max_energy)/10)*10);        
        gStyle->SetOptStat(0);
        fDrawHist->Paint("A");

        if (!fAxis) {
          fAxis = new TGaxis(0, 0, 0, (int)((1.1*max_energy)/10)*10 , 0, (int)((1.1*max_energy)/10)*10, 510, "");
          fAxis->AppendPad();  
        }
        
        double transition_spacing = 0.8/(double)nTransitions;
        int count = 0;

        for (int i=0; i<(int)drawn_indexes.size(); ++i) {
          int index = drawn_indexes[i];
          State *state = GetStateByIndex(drawn_indexes[i]);
          state->fLabelPos = state->fEnergy;
          state->fDrawPos = state->fEnergy;
        }
        
        int conflicts = 1;
        TText *test = new TText();
        test->SetTextSize(15);
        int py0 = gPad->YtoPixel(0);
        double label_threshold = gPad->PixeltoY(py0-(test->GetTextSize()+3)) - gPad->PixeltoY(py0);
        delete test;
        label_threshold = fabs(label_threshold);
        double state_threshold = 40;
        while (conflicts) {
          conflicts = 0;
          //std::cout << "New attempt" << std::endl;
          for (int i = 0; i < (int)drawn_indexes.size()-1; ++i) {
            State *state1 = GetStateByIndex(drawn_indexes[i]);
            State *state2 = GetStateByIndex(drawn_indexes[i+1]);
            if ((state2->fLabelPos - state1->fLabelPos) < label_threshold) {
              //std::cout << "States " << drawn_states[drawn_indexes[i]]->fEnergy << " and " << drawn_states[drawn_indexes[i+1]]->fEnergy << " with positions " << drawn_states[drawn_indexes[i+1]]->fLabelPos << " and " << drawn_states[drawn_indexes[i]]->fLabelPos << std::endl;
              conflicts++;
              double av = (state2->fLabelPos + state1->fLabelPos)/2.0;
              state1->fLabelPos = av-1.001*label_threshold/2.0;
              state2->fLabelPos = av+1.001*label_threshold/2.0;
              //std::cout << "New positions " << drawn_states[drawn_indexes[i+1]]->fLabelPos << " and " << drawn_states[drawn_indexes[i]]->fLabelPos << std::endl;
            }
            if ((state2->fDrawPos - state1->fDrawPos) < state_threshold) {
              //std::cout << "States with positions " << state_pos[i+1] << " and " << state_pos[i] << std::endl;
              conflicts++;
              double av = (state2->fDrawPos + state1->fDrawPos)/2.0;
              state1->fDrawPos = av-1.001*state_threshold/2.0;
              state2->fDrawPos = av+1.001*state_threshold/2.0;
              //std::cout << "New positions " << state_pos[i+1] << " and " << state_pos[i] << std::endl;
            }
          }
        }

        std::vector<Transition*> draw_transitions;
        
        for (int i=0; i<(int)drawn_indexes.size(); ++i) {
          int index = drawn_indexes[i];
          State *state = GetStateByIndex(drawn_indexes[i]);

          //state->Paint(option);
          if (!gPad->GetListOfPrimitives()->Contains(state)) {
            state->AppendPad();
          }

          std::vector<Transition*> state_transitions;
          for (auto &transition : fTransitions) {
            if (transition.fInitial->index == state->index && range_states.find(state->index) != range_states.end()) {
              state_transitions.push_back(&transition);
              draw_transitions.push_back(&transition);
            }
          }

          std::sort(state_transitions.begin(), state_transitions.end(),
                    [](const Transition *a, const Transition *b)
                    { 
                      return *a < *b;
                    });

          for (auto &transition : state_transitions) {
            State* finalState = GetStateByIndex(transition->fFinal->index);

            transition->SetX1(0.9-(double)count*transition_spacing-0.5*transition_spacing);
            transition->SetY1(state->fDrawPos);
            transition->SetX2(0.9-(double)count*transition_spacing-0.5*transition_spacing);
            transition->SetY2(finalState->fDrawPos);                       
                
            ++count;
          }          

        }

        for (auto &transition : draw_transitions) {
          //transition->Paint();
          if (!gPad->GetListOfPrimitives()->Contains(transition)) {
            transition->AppendPad();
          }
        }

        //gPad->GetListOfPrimitives()->Remove(fDrawHist);

      }

      void Scheme::SaveTable(std::string filename) {
        std::ofstream outfile(filename);

        SetIndices();
        
        for (int i=0; i<fStates.size(); ++i) {
          auto state = GetStateByIndex(i);

          std::vector<Transition> transitions;
          for (auto transition : fTransitions) {
            if (state == transition.fInitial) {
              transitions.push_back(transition);
              std::cout << state->fEnergy << "   " << transition.fInitial->fEnergy << "   " << transition.fEnergy <<  std::endl;
            }
          }

          for (int j=0; j<transitions.size(); ++j) {
            if (j==0) {
              outfile << GamR::Utils::wrresult(state->fEnergy, state->fUncertainty) << " & ";
            }
            else {
              outfile << " & ";
            }
            outfile << GamR::Utils::wrresult(transitions[j].fEnergy, transitions[j].fUncertainty) << " & " << GamR::Utils::wrresult(transitions[j].fFinal->fEnergy, transitions[j].fFinal->fUncertainty) << "\\\\" << std::endl;
          }
        }
        outfile.close();
      }
        
    }
  }
}
