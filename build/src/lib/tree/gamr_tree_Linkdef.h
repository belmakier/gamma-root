#ifdef __ROOTCLING__

/* Turn off all */
#pragma link off all class;
#pragma link off all functions;
#pragma link off all global;
#pragma link off all typedef;

/* Enable this namespace */
#pragma link C++ namespace GamR;
#pragma link C++ namespace GamR::Tree;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

/* Reader -- no default constructor of TTreeReaderArray objects causes issues */
//#pragma link C++ defined_in "${CMAKE_CURRENT_SOURCE_DIR}/Reader.hh";


/* GammaROOT Tree -- Base measurement types
 * Double_t
 * ULong64_t
 * Long64_t
 * Float_t
 * UInt_t
 * Int_t
 * UShort_t
 * Short_t
 * UChar_t
 * Char_t
 */
#pragma link C++ class std::pair<Double_t, Double_t>+;
#pragma link C++ class std::pair<ULong64_t, Double_t>+;
#pragma link C++ class std::pair<Long64_t, Double_t>+;
#pragma link C++ class std::pair<Float_t, Double_t>+;
#pragma link C++ class std::pair<UInt_t, Double_t>+;
#pragma link C++ class std::pair<Int_t, Double_t>+;
#pragma link C++ class std::pair<UShort_t, Double_t>+;
#pragma link C++ class std::pair<Short_t, Double_t>+;
#pragma link C++ class std::pair<UChar_t, Double_t>+;
#pragma link C++ class std::pair<Char_t, Double_t>+;
#pragma link C++ class std::pair<Bool_t, Double_t>+;


// Tree Definition Group: DCP
/* ------------------------------------------------------------
 * DCP, D1
 * UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t>>+;

/* ------------------------------------------------------------
 * DCP, D2
 * UShort_t, UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t>>+;

/* ------------------------------------------------------------
 * DCP, D3
 * UShort_t, UShort_t, UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>+;

/* ------------------------------------------------------------
 * DCP, D21
 * UShort_t, UShort_t
 * UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t>>+;

/* ------------------------------------------------------------
 * DCP, D22
 * UShort_t, UShort_t
 * UShort_t, UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>>+;

/* ------------------------------------------------------------
 * DCP, D33
 * UShort_t, UShort_t, UShort_t
 * UShort_t, UShort_t, UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>+;

/* ------------------------------------------------------------
 * DCP, D221
 * UShort_t, UShort_t
 * UShort_t, UShort_t
 * UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t>>+;

/* ------------------------------------------------------------
 * DCP, D321
 * UShort_t, UShort_t, UShort_t
 * UShort_t, UShort_t
 * UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t>>+;

/* ------------------------------------------------------------
 * DCP, D322
 * UShort_t, UShort_t, UShort_t
 * UShort_t, UShort_t
 * UShort_t, UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>>+;

/* ------------------------------------------------------------
 * DCP, D2111
 * UShort_t, UShort_t
 * UShort_t
 * UShort_t
 * UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t>, GamR::Tree::TDetDefn<UShort_t>, GamR::Tree::TDetDefn<UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t>, GamR::Tree::TDetector<UShort_t>, GamR::Tree::TDetector<UShort_t>>+;

/* ------------------------------------------------------------
 * DCP, D3221
 * UShort_t, UShort_t, UShort_t
 * UShort_t, UShort_t
 * UShort_t, UShort_t
 * UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t>>+;

/* ------------------------------------------------------------
 * DCP, D3333
 * UShort_t, UShort_t, UShort_t
 * UShort_t, UShort_t, UShort_t
 * UShort_t, UShort_t, UShort_t
 * UShort_t, UShort_t, UShort_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>, std::pair<UShort_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>+;
#pragma link C++ class GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>, std::vector<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetDefn<UShort_t, UShort_t, UShort_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>, GamR::Tree::TDetector<UShort_t, UShort_t, UShort_t>>+;


// Tree Definition Group: PIXIE
/* ------------------------------------------------------------
 * PIXIE, P1
 * ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<ULong64_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>>+;

/* ------------------------------------------------------------
 * PIXIE, P1T
 * ULong64_t, UInt_t, UInt_t, UInt_t
 * ULong64_t, UInt_t, UInt_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<ULong64_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<ULong64_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t>>+;

/* ------------------------------------------------------------
 * PIXIE, P2T
 * ULong64_t, UInt_t, UInt_t, UInt_t
 * ULong64_t, UInt_t, UInt_t, UInt_t
 * ULong64_t, UInt_t, UInt_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<ULong64_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<ULong64_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t>>+;

/* ------------------------------------------------------------
 * PIXIE, PS
 * ULong64_t, UInt_t, UInt_t, UInt_t
 * ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t
 * ULong64_t, UInt_t, UInt_t, UInt_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<ULong64_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<ULong64_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t>>+;


// Tree Definition Group: GRETINA_CHICO
/* ------------------------------------------------------------
 * GRETINA_CHICO, GCPG
 * Double_t, Double_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t
 * Double_t, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Bool_t, Bool_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<Double_t, Double_t>, std::pair<Double_t, Double_t>, std::pair<Int_t, Double_t>, std::pair<Int_t, Double_t>, std::pair<Int_t, Double_t>, std::pair<Int_t, Double_t>, std::pair<Int_t, Double_t>, std::pair<Int_t, Double_t>, std::pair<Int_t, Double_t>, std::pair<Int_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Bool_t, Double_t>, std::pair<Bool_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<Double_t, Double_t>, std::pair<Double_t, Double_t>, std::pair<Int_t, Double_t>, std::pair<Int_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>, std::pair<Float_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<Double_t, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Bool_t, Bool_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<Double_t, Double_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t>+;
#pragma link C++ class GamR::Tree::TDetector<Double_t, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Bool_t, Bool_t>+;
#pragma link C++ class GamR::Tree::TDetector<Double_t, Double_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<Double_t, Double_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t>>, std::vector<GamR::Tree::TDetector<Double_t, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Bool_t, Bool_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<Double_t, Double_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t>, GamR::Tree::TDetDefn<Double_t, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Bool_t, Bool_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<Double_t, Double_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t>, GamR::Tree::TDetector<Double_t, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Float_t, Bool_t, Bool_t>>+;


// Tree Definition Group: CLARION_HYBALL
/* ------------------------------------------------------------
 * CLARION_HYBALL, CLHB
 * UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t
 * UInt_t, UInt_t
 * UInt_t, UInt_t, UInt_t
 * UInt_t
 * UInt_t, UInt_t
 * UInt_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UInt_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<UInt_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<UInt_t>>, std::vector<GamR::Tree::TDetector<UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<UInt_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t>, GamR::Tree::TDetDefn<UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t>, GamR::Tree::TDetector<UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t>>+;


// Tree Definition Group: DIGITAL_GAMMASPHERE
/* ------------------------------------------------------------
 * DIGITAL_GAMMASPHERE, DGS
 * ULong64_t, Double_t, UInt_t
 * ULong64_t, Double_t, UInt_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<ULong64_t, Double_t>, std::pair<Double_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<ULong64_t, Double_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<ULong64_t, Double_t, UInt_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<ULong64_t, Double_t, UInt_t>>, std::vector<GamR::Tree::TDetector<ULong64_t, Double_t, UInt_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, Double_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, Double_t, UInt_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, Double_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, Double_t, UInt_t>>+;


// Tree Definition Group: RIKEN
/* ------------------------------------------------------------
 * RIKEN, PAD2018
 * UInt_t, UInt_t, UInt_t, UInt_t
 * UInt_t, UInt_t, UInt_t, UInt_t
 * UInt_t, UInt_t, UInt_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class std::tuple<std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<UInt_t, UInt_t, UInt_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<UInt_t, UInt_t, UInt_t>>+;


// Tree Definition Group: OSCAR
/* ------------------------------------------------------------
 * OSCAR, OSC
 * ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t
 * ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t
 * ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t */
/* ------------------------------------------------------------ */
/*                          Detectors                           */
#pragma link C++ class std::tuple<std::pair<ULong64_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>, std::pair<UInt_t, Double_t>>+;
#pragma link C++ class GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>+;
#pragma link C++ class GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>+;
/* ------------------------------------------------------------ */
/*                            Event                             */
#pragma link C++ class std::tuple<std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>>, std::vector<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>>>+;
#pragma link C++ class GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetDefn<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>>+;
#pragma link C++ class GamR::Tree::TEvent<GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>, GamR::Tree::TDetector<ULong64_t, UInt_t, UInt_t, UInt_t, UInt_t>>+;



#endif
