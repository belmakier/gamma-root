#include <doctest/doctest.h>
/* STD */
#include <string>

/* ROOT */
#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TROOT.h>

/* GAMR */
#include <tree/DetDefn.hh>
#include <tree/ExpDefn.hh>
#include <tree/Detector.hh>
#include <tree/Event.hh>

SCENARIO("A RawTree from a Pixie Digitizer can be converted to a GamR EventTree") {
 // weird root segault thing with files and stuff
  // it doesn't matter what line you process, just do it
  gROOT->ProcessLine("#include <array>");

  std::string workdir("/Users/99j/git/gamma-root/src/tests/tree/pxi/");

  using PXI_TDetector0 = GamR::Tree::TDetector<ULong64_t,UInt_t,UInt_t,UInt_t>;
  using PXI_TDetector1 = GamR::Tree::TDetector<ULong64_t,UInt_t,UInt_t>;
  
  using PXI_TEvent = GamR::Tree::TEvent<PXI_TDetector0, PXI_TDetector1>;
  using PXI_TExpDefn = GamR::Tree::TExpDefn<GamR::Tree::TDetDefn<ULong64_t,UInt_t,UInt_t,UInt_t>,GamR::Tree::TDetDefn<ULong64_t,UInt_t,UInt_t>>;

  GIVEN("We have loaded our experiment definition") {
    auto expdefn =  PXI_TExpDefn();
    std::vector<std::string> infiles = {workdir+"fe56_1217.root"};
    Int_t err_load = expdefn.Load(infiles, workdir+"fe56_1217.ini");
    REQUIRE(err_load == 0);

    WHEN("We convert the tree") {
      Int_t events_converted = expdefn.Convert<PXI_TEvent>(workdir+"fe56_converted.root", 0, true); // zero offset
      REQUIRE(events_converted == 1000);
      expdefn.CloseFiles();
      
      THEN("The RawTree should datums should equal the EventTree uncalibrated ones") {
	auto rawfile = new TFile((workdir+"fe56_1217.root").c_str());
	auto convfile = new TFile((workdir+"fe56_converted.root").c_str());

	TTreeReader rawreader("RawTree", rawfile);
	TTreeReader convreader("EventTree", convfile);

	REQUIRE(rawreader.GetEntries(true) == convreader.GetEntries(true));

	// The RawTree
	TTreeReaderValue<ULong64_t> g0d0m0(rawreader, "0.2.0.eventTime");
	TTreeReaderValue<ULong64_t> g0d1m0(rawreader, "0.2.1.eventTime");
	TTreeReaderValue<ULong64_t> g0d2m0(rawreader, "0.2.2.eventTime");
	TTreeReaderValue<ULong64_t> g0d3m0(rawreader, "0.2.3.eventTime");
	// and
	TTreeReaderValue<UInt_t> g0d0m1(rawreader, "0.2.0.eventEnergy");
	TTreeReaderValue<UInt_t> g0d1m1(rawreader, "0.2.1.eventEnergy");
	TTreeReaderValue<UInt_t> g0d2m1(rawreader, "0.2.2.eventEnergy");
	TTreeReaderValue<UInt_t> g0d3m1(rawreader, "0.2.3.eventEnergy");
	// this
	TTreeReaderValue<UInt_t> g0d0m2(rawreader, "0.2.0.finishCode");
	TTreeReaderValue<UInt_t> g0d1m2(rawreader, "0.2.1.finishCode");
	TTreeReaderValue<UInt_t> g0d2m2(rawreader, "0.2.2.finishCode");
	TTreeReaderValue<UInt_t> g0d3m2(rawreader, "0.2.3.finishCode");
	// is
	TTreeReaderValue<UInt_t> g0d0m3(rawreader, "0.2.0.CFDForce");
	TTreeReaderValue<UInt_t> g0d1m3(rawreader, "0.2.1.CFDForce");
	TTreeReaderValue<UInt_t> g0d2m3(rawreader, "0.2.2.CFDForce");
	TTreeReaderValue<UInt_t> g0d3m3(rawreader, "0.2.3.CFDForce");
	// why
	TTreeReaderValue<ULong64_t> g1d4m0(rawreader, "0.2.4.taggerTime");
	// we
	TTreeReaderValue<UInt_t> g1d4m1(rawreader, "0.2.4.taggerValue");
	// convert
	TTreeReaderValue<UInt_t> g1d4m2(rawreader, "0.2.4.taggerNew");
	
	// to a GamR EventTree
	TTreeReaderValue<std::vector<PXI_TDetector0>> group0(convreader, "DetGroup._0");
	TTreeReaderValue<std::vector<PXI_TDetector1>> group1(convreader, "DetGroup._1");

	Long64_t eventfailed = 0;
	Long64_t good = 0;
	while (rawreader.Next() && convreader.Next() && !eventfailed) {
	  auto group0vec = *group0; auto group1vec = *group1;

	  // iterate through group 0
	  for (auto& det : group0vec) {
	    if (det.ID == 0) {
	      if (det.Get<0>() != *g0d0m0 || det.Get<1>() != *g0d0m1 || det.Get<2>() != *g0d0m2 || det.Get<3>() != *g0d0m3) {
		eventfailed = rawreader.GetCurrentEntry(); break;
	      } else { ++good; }
	    }
	    else if (det.ID == 1) {
	      if (det.Get<0>() != *g0d1m0 || det.Get<1>() != *g0d1m1 || det.Get<2>() != *g0d1m2 || det.Get<3>() != *g0d1m3) {
		eventfailed = rawreader.GetCurrentEntry(); break;
	      } else { ++good; } 
	    }
	    else if (det.ID == 2) {
	      if (det.Get<0>() != *g0d2m0 || det.Get<1>() != *g0d2m1 || det.Get<2>() != *g0d2m2 || det.Get<3>() != *g0d2m3) {
		eventfailed = rawreader.GetCurrentEntry(); break;
	      } else { ++good; }
	    }
	    else if (det.ID == 3) {
	      if (det.Get<0>() != *g0d3m0 || det.Get<1>() != *g0d3m1 || det.Get<2>() != *g0d3m2 || det.Get<3>() != *g0d3m3) {
		eventfailed = rawreader.GetCurrentEntry(); break;
	      } else { ++good; }
	    }
	  } // done

	  // iterate through group 1
	  for (auto& det : group1vec) {
	    if (det.Get<0>() != *g1d4m0 || det.Get<1>() != *g1d4m1 || det.Get<2>() != *g1d4m2) {
	      eventfailed = rawreader.GetCurrentEntry(); break;
	    } else { ++good; }
	  } // done

	} // end while through tree
	  
	REQUIRE(eventfailed == 0);
	REQUIRE(good > 0);

      } // THEN: None of the data should be corrupted
	
    } // WHEN: We convert the tree
    
  } // GIVEN: An experiment definition


} // SCENARIO: Pixie -> GamR
