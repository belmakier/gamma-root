#include <tree/DetDefn.hh>
#include <tree/ExpDefn.hh>
#include <tree/Detector.hh>
#include <tree/Event.hh>


// Tree Definition Group: DCP
/* ------------------------------------------------------------ */
/*                           DCP, D1                            */
/* ------------------------------------------------------------ */
// DetDefns
using D1_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t>;
// ExpDefns
using D1_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t>>;
// Detectors
using D1_TDetector0 = GamR::Tree::TDetector<UShort_t>;
// Event
using D1_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t>>;

/* ------------------------------------------------------------ */
/*                           DCP, D2                            */
/* ------------------------------------------------------------ */
// DetDefns
using D2_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
// ExpDefns
using D2_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t>>;
// Detectors
using D2_TDetector0 = GamR::Tree::TDetector<UShort_t, UShort_t>;
// Event
using D2_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t>>;

/* ------------------------------------------------------------ */
/*                           DCP, D3                            */
/* ------------------------------------------------------------ */
// DetDefns
using D3_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>;
// ExpDefns
using D3_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>>;
// Detectors
using D3_TDetector0 = GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>;
// Event
using D3_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>;

/* ------------------------------------------------------------ */
/*                           DCP, D21                           */
/* ------------------------------------------------------------ */
// DetDefns
using D21_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
using D21_TDetDefn1 = GamR::Tree::TDetDefn<UShort_t>;
// ExpDefns
using D21_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t>>;
// Detectors
using D21_TDetector0 = GamR::Tree::TDetector<UShort_t, UShort_t>;
using D21_TDetector1 = GamR::Tree::TDetector<UShort_t>;
// Event
using D21_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t>>;

/* ------------------------------------------------------------ */
/*                           DCP, D22                           */
/* ------------------------------------------------------------ */
// DetDefns
using D22_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
using D22_TDetDefn1 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
// ExpDefns
using D22_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>>;
// Detectors
using D22_TDetector0 = GamR::Tree::TDetector<UShort_t, UShort_t>;
using D22_TDetector1 = GamR::Tree::TDetector<UShort_t, UShort_t>;
// Event
using D22_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>>;

/* ------------------------------------------------------------ */
/*                           DCP, D33                           */
/* ------------------------------------------------------------ */
// DetDefns
using D33_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>;
using D33_TDetDefn1 = GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>;
// ExpDefns
using D33_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>>;
// Detectors
using D33_TDetector0 = GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>;
using D33_TDetector1 = GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>;
// Event
using D33_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>;

/* ------------------------------------------------------------ */
/*                          DCP, D221                           */
/* ------------------------------------------------------------ */
// DetDefns
using D221_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
using D221_TDetDefn1 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
using D221_TDetDefn2 = GamR::Tree::TDetDefn<UShort_t>;
// ExpDefns
using D221_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t>>;
// Detectors
using D221_TDetector0 = GamR::Tree::TDetector<UShort_t, UShort_t>;
using D221_TDetector1 = GamR::Tree::TDetector<UShort_t, UShort_t>;
using D221_TDetector2 = GamR::Tree::TDetector<UShort_t>;
// Event
using D221_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t>>;

/* ------------------------------------------------------------ */
/*                          DCP, D321                           */
/* ------------------------------------------------------------ */
// DetDefns
using D321_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>;
using D321_TDetDefn1 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
using D321_TDetDefn2 = GamR::Tree::TDetDefn<UShort_t>;
// ExpDefns
using D321_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t>>;
// Detectors
using D321_TDetector0 = GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>;
using D321_TDetector1 = GamR::Tree::TDetector<UShort_t, UShort_t>;
using D321_TDetector2 = GamR::Tree::TDetector<UShort_t>;
// Event
using D321_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t>>;

/* ------------------------------------------------------------ */
/*                          DCP, D322                           */
/* ------------------------------------------------------------ */
// DetDefns
using D322_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>;
using D322_TDetDefn1 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
using D322_TDetDefn2 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
// ExpDefns
using D322_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>>;
// Detectors
using D322_TDetector0 = GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>;
using D322_TDetector1 = GamR::Tree::TDetector<UShort_t, UShort_t>;
using D322_TDetector2 = GamR::Tree::TDetector<UShort_t, UShort_t>;
// Event
using D322_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>>;

/* ------------------------------------------------------------ */
/*                          DCP, D2111                          */
/* ------------------------------------------------------------ */
// DetDefns
using D2111_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
using D2111_TDetDefn1 = GamR::Tree::TDetDefn<UShort_t>;
using D2111_TDetDefn2 = GamR::Tree::TDetDefn<UShort_t>;
using D2111_TDetDefn3 = GamR::Tree::TDetDefn<UShort_t>;
// ExpDefns
using D2111_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t>, GamR::Tree::TDetDefn<UShort_t>, GamR::Tree::TDetDefn<UShort_t>>;
// Detectors
using D2111_TDetector0 = GamR::Tree::TDetector<UShort_t, UShort_t>;
using D2111_TDetector1 = GamR::Tree::TDetector<UShort_t>;
using D2111_TDetector2 = GamR::Tree::TDetector<UShort_t>;
using D2111_TDetector3 = GamR::Tree::TDetector<UShort_t>;
// Event
using D2111_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t>, GamR::Tree::TDetector<UShort_t>, GamR::Tree::TDetector<UShort_t>>;

/* ------------------------------------------------------------ */
/*                          DCP, D3221                          */
/* ------------------------------------------------------------ */
// DetDefns
using D3221_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>;
using D3221_TDetDefn1 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
using D3221_TDetDefn2 = GamR::Tree::TDetDefn<UShort_t, UShort_t>;
using D3221_TDetDefn3 = GamR::Tree::TDetDefn<UShort_t>;
// ExpDefns
using D3221_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t>>;
// Detectors
using D3221_TDetector0 = GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>;
using D3221_TDetector1 = GamR::Tree::TDetector<UShort_t, UShort_t>;
using D3221_TDetector2 = GamR::Tree::TDetector<UShort_t, UShort_t>;
using D3221_TDetector3 = GamR::Tree::TDetector<UShort_t>;
// Event
using D3221_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t>>;

/* ------------------------------------------------------------ */
/*                          DCP, D3333                          */
/* ------------------------------------------------------------ */
// DetDefns
using D3333_TDetDefn0 = GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>;
using D3333_TDetDefn1 = GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>;
using D3333_TDetDefn2 = GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>;
using D3333_TDetDefn3 = GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>;
// ExpDefns
using D3333_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>>;
// Detectors
using D3333_TDetector0 = GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>;
using D3333_TDetector1 = GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>;
using D3333_TDetector2 = GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>;
using D3333_TDetector3 = GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>;
// Event
using D3333_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>;


// Tree Definition Group: PIXIE
/* ------------------------------------------------------------ */
/*                          PIXIE, P1                           */
/* ------------------------------------------------------------ */
// DetDefns
using P1_TDetDefn0 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>;
// ExpDefns
using P1_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>>;
// Detectors
using P1_TDetector0 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>;
// Event
using P1_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>>;

/* ------------------------------------------------------------ */
/*                          PIXIE, P1T                          */
/* ------------------------------------------------------------ */
// DetDefns
using P1T_TDetDefn0 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>;
using P1T_TDetDefn1 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t>;
// ExpDefns
using P1T_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t>>;
// Detectors
using P1T_TDetector0 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>;
using P1T_TDetector1 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t>;
// Event
using P1T_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t>>;

/* ------------------------------------------------------------ */
/*                          PIXIE, P2T                          */
/* ------------------------------------------------------------ */
// DetDefns
using P2T_TDetDefn0 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>;
using P2T_TDetDefn1 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>;
using P2T_TDetDefn2 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t>;
// ExpDefns
using P2T_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t>>;
// Detectors
using P2T_TDetector0 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>;
using P2T_TDetector1 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>;
using P2T_TDetector2 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t>;
// Event
using P2T_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t>>;

/* ------------------------------------------------------------ */
/*                          PIXIE, PS                           */
/* ------------------------------------------------------------ */
// DetDefns
using PS_TDetDefn0 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>;
using PS_TDetDefn1 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>;
using PS_TDetDefn2 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>;
// ExpDefns
using PS_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>>;
// Detectors
using PS_TDetector0 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>;
using PS_TDetector1 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>;
using PS_TDetector2 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>;
// Event
using PS_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>>;


// Tree Definition Group: GRETINA_CHICO
/* ------------------------------------------------------------ */
/*                     GRETINA_CHICO, GCPG                      */
/* ------------------------------------------------------------ */
// DetDefns
using GCPG_TDetDefn0 = GamR::Tree::TDetDefn<Double_t, Double_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t>;
using GCPG_TDetDefn1 = GamR::Tree::TDetDefn<Double_t, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Bool_t, Bool_t>;
// ExpDefns
using GCPG_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<Double_t, Double_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t>, GamR::Tree::TDetDefn<Double_t, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Bool_t, Bool_t>>;
// Detectors
using GCPG_TDetector0 = GamR::Tree::TDetector<Double_t, Double_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t>;
using GCPG_TDetector1 = GamR::Tree::TDetector<Double_t, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Bool_t, Bool_t>;
// Event
using GCPG_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<Double_t, Double_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t>, GamR::Tree::TDetector<Double_t, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Bool_t, Bool_t>>;


// Tree Definition Group: CLARION_HYBALL
/* ------------------------------------------------------------ */
/*                     CLARION_HYBALL, CLHB                     */
/* ------------------------------------------------------------ */
// DetDefns
using CLHB_TDetDefn0 = GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>;
using CLHB_TDetDefn1 = GamR::Tree::TDetDefn<UInt_t, UInt_t>;
using CLHB_TDetDefn2 = GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t>;
using CLHB_TDetDefn3 = GamR::Tree::TDetDefn<UInt_t>;
using CLHB_TDetDefn4 = GamR::Tree::TDetDefn<UInt_t, UInt_t>;
using CLHB_TDetDefn5 = GamR::Tree::TDetDefn<UInt_t>;
// ExpDefns
using CLHB_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t>, GamR::Tree::TDetDefn<UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t>>;
// Detectors
using CLHB_TDetector0 = GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>;
using CLHB_TDetector1 = GamR::Tree::TDetector<UInt_t, UInt_t>;
using CLHB_TDetector2 = GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t>;
using CLHB_TDetector3 = GamR::Tree::TDetector<UInt_t>;
using CLHB_TDetector4 = GamR::Tree::TDetector<UInt_t, UInt_t>;
using CLHB_TDetector5 = GamR::Tree::TDetector<UInt_t>;
// Event
using CLHB_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t>, GamR::Tree::TDetector<UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t>>;


// Tree Definition Group: DIGITAL_GAMMASPHERE
/* ------------------------------------------------------------ */
/*                   DIGITAL_GAMMASPHERE, DGS                   */
/* ------------------------------------------------------------ */
// DetDefns
using DGS_TDetDefn0 = GamR::Tree::TDetDefn<ULong64_t, Double_t, UInt_t>;
using DGS_TDetDefn1 = GamR::Tree::TDetDefn<ULong64_t, Double_t, UInt_t>;
// ExpDefns
using DGS_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, Double_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, Double_t, UInt_t>>;
// Detectors
using DGS_TDetector0 = GamR::Tree::TDetector<ULong64_t, Double_t, UInt_t>;
using DGS_TDetector1 = GamR::Tree::TDetector<ULong64_t, Double_t, UInt_t>;
// Event
using DGS_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, Double_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, Double_t, UInt_t>>;


// Tree Definition Group: RIKEN
/* ------------------------------------------------------------ */
/*                        RIKEN, PAD2018                        */
/* ------------------------------------------------------------ */
// DetDefns
using PAD2018_TDetDefn0 = GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t, UInt_t>;
using PAD2018_TDetDefn1 = GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t, UInt_t>;
using PAD2018_TDetDefn2 = GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t>;
// ExpDefns
using PAD2018_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t>>;
// Detectors
using PAD2018_TDetector0 = GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t>;
using PAD2018_TDetector1 = GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t>;
using PAD2018_TDetector2 = GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t>;
// Event
using PAD2018_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t>>;


// Tree Definition Group: OSCAR
/* ------------------------------------------------------------ */
/*                          OSCAR, OSC                          */
/* ------------------------------------------------------------ */
// DetDefns
using OSC_TDetDefn0 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>;
using OSC_TDetDefn1 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>;
using OSC_TDetDefn2 = GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>;
// ExpDefns
using OSC_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>>;
// Detectors
using OSC_TDetector0 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>;
using OSC_TDetector1 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>;
using OSC_TDetector2 = GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>;
// Event
using OSC_TEvent = GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>>;


