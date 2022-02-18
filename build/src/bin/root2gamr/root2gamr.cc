/* STD */
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/* GAMR */
#include <tree/Tree.hh>
#include <utils/RTTI.hh>

/* EXTERN */
#include <args/args.hxx>

template <typename ExpDefn, typename Event>
unsigned long long process(std::vector<std::string> infile, std::string conf, std::string outfile, unsigned long long offset=0, unsigned long long nevents = 0, Bool_t quiet = kFALSE, Int_t compression = 201, ULong64_t splitmb = 2000, Bool_t overwrite = kFALSE)
{
  auto expdefn = ExpDefn();
  int err = expdefn.Load(infile, conf, quiet);
  if (err) {
    throw std::runtime_error("Failed to define experiment for with config "+conf);
  }
  auto n = expdefn.template Convert<Event>(outfile, offset, nevents, quiet, compression, splitmb, overwrite);
  return n;
}

int main(int argc, char* argv[]) {
  args::ArgumentParser parser("GammaROOT Tree Convertor",
			      "Aqeel Akber <aqeel.akber@anu.edu.au>\n"
			      "Contribute! <i.believe.in.you@yourdesk.io>");
  
  args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

  args::Group files(parser, "File names", args::Group::Validators::All);
  args::ValueFlagList<std::string, std::vector> infiles(files, "raw.root", "Input ROOT file.", {'i', "input"});
  //ONLY ONE INI FILE TJG
  args::ValueFlag<std::string> inifile(files, "conf.ini", "Tree Definition.", {'c', "conf"});
  args::ValueFlag<std::string> outfilename(files, "out.root", "Output ROOT file.", {'o', "output"});

  args::Group tuning_parser(parser, "Tuning parameters");
  args::ValueFlag<ULong64_t> nevents(tuning_parser, "0", "Number of events to process, zero = all", {'n', "nevents"}, 0);
  args::ValueFlag<ULong64_t> offset(tuning_parser, "0", "Offset for event number", {'f', "offset"}, 0);
  args::ValueFlag<ULong64_t> splitmb(tuning_parser, "50000", "Split output file at MB", {'s', "split"}, 50000);
  args::ValueFlag<Int_t> compression(tuning_parser, "101", "Output file compression settings", {'z', "compression"}, 101);
  args::Flag quiet(tuning_parser, "quiet", "Suppress print statements", {'q', "quiet"});
  args::Flag overwrite(tuning_parser, "overwrite", "Overwrite without asking", {'y', "overwrite"});  

  args::Group treetype(parser, "Convert type", args::Group::Validators::Xor);
  
// Tree Definition Group: DCP
args::Group DCP(treetype, "Tree Group: DCP", args::Group::Validators::Xor);
args::Flag D1(DCP, "D1", "DCP D1", {"D1"});
args::Flag D2(DCP, "D2", "DCP D2", {"D2"});
args::Flag D3(DCP, "D3", "DCP D3", {"D3"});
args::Flag D21(DCP, "D21", "DCP D21", {"D21"});
args::Flag D22(DCP, "D22", "DCP D22", {"D22"});
args::Flag D33(DCP, "D33", "DCP D33", {"D33"});
args::Flag D221(DCP, "D221", "DCP D221", {"D221"});
args::Flag D321(DCP, "D321", "DCP D321", {"D321"});
args::Flag D322(DCP, "D322", "DCP D322", {"D322"});
args::Flag D2111(DCP, "D2111", "DCP D2111", {"D2111"});
args::Flag D3221(DCP, "D3221", "DCP D3221", {"D3221"});
args::Flag D3333(DCP, "D3333", "DCP D3333", {"D3333"});

// Tree Definition Group: PIXIE
args::Group PIXIE(treetype, "Tree Group: PIXIE", args::Group::Validators::Xor);
args::Flag P1(PIXIE, "P1", "PIXIE P1", {"P1"});
args::Flag P1T(PIXIE, "P1T", "PIXIE P1T", {"P1T"});
args::Flag P2T(PIXIE, "P2T", "PIXIE P2T", {"P2T"});
args::Flag PS(PIXIE, "PS", "PIXIE PS", {"PS"});

// Tree Definition Group: GRETINA_CHICO
args::Group GRETINA_CHICO(treetype, "Tree Group: GRETINA_CHICO", args::Group::Validators::Xor);
args::Flag GCPG(GRETINA_CHICO, "GCPG", "GRETINA_CHICO GCPG", {"GCPG"});

// Tree Definition Group: CLARION_HYBALL
args::Group CLARION_HYBALL(treetype, "Tree Group: CLARION_HYBALL", args::Group::Validators::Xor);
args::Flag CLHB(CLARION_HYBALL, "CLHB", "CLARION_HYBALL CLHB", {"CLHB"});

// Tree Definition Group: DIGITAL_GAMMASPHERE
args::Group DIGITAL_GAMMASPHERE(treetype, "Tree Group: DIGITAL_GAMMASPHERE", args::Group::Validators::Xor);
args::Flag DGS(DIGITAL_GAMMASPHERE, "DGS", "DIGITAL_GAMMASPHERE DGS", {"DGS"});

// Tree Definition Group: RIKEN
args::Group RIKEN(treetype, "Tree Group: RIKEN", args::Group::Validators::Xor);
args::Flag PAD2018(RIKEN, "PAD2018", "RIKEN PAD2018", {"PAD2018"});

// Tree Definition Group: OSCAR
args::Group OSCAR(treetype, "Tree Group: OSCAR", args::Group::Validators::Xor);
args::Flag OSC(OSCAR, "OSC", "OSCAR OSC", {"OSC"});

  
  try { parser.ParseCLI(argc, argv); }
  catch (args::Help) {
    std::cout << parser;
    return 0;
  }
  catch (args::ParseError e) {
    std::cerr << e.what() << std::endl;
    std::cerr << parser;
    return 1;
  }
  catch (args::ValidationError e) {
    std::cerr << e.what() << std::endl;
    std::cerr << parser;
    return 1;
  }

  if (false) {}
  
// Tree Definition Group: DCP
else if (D1) {
  process<D1_TExpDefn, D1_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (D2) {
  process<D2_TExpDefn, D2_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (D3) {
  process<D3_TExpDefn, D3_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (D21) {
  process<D21_TExpDefn, D21_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (D22) {
  process<D22_TExpDefn, D22_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (D33) {
  process<D33_TExpDefn, D33_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (D221) {
  process<D221_TExpDefn, D221_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (D321) {
  process<D321_TExpDefn, D321_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (D322) {
  process<D322_TExpDefn, D322_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (D2111) {
  process<D2111_TExpDefn, D2111_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (D3221) {
  process<D3221_TExpDefn, D3221_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (D3333) {
  process<D3333_TExpDefn, D3333_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}

// Tree Definition Group: PIXIE
else if (P1) {
  process<P1_TExpDefn, P1_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (P1T) {
  process<P1T_TExpDefn, P1T_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (P2T) {
  process<P2T_TExpDefn, P2T_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}
else if (PS) {
  process<PS_TExpDefn, PS_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}

// Tree Definition Group: GRETINA_CHICO
else if (GCPG) {
  process<GCPG_TExpDefn, GCPG_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}

// Tree Definition Group: CLARION_HYBALL
else if (CLHB) {
  process<CLHB_TExpDefn, CLHB_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}

// Tree Definition Group: DIGITAL_GAMMASPHERE
else if (DGS) {
  process<DGS_TExpDefn, DGS_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}

// Tree Definition Group: RIKEN
else if (PAD2018) {
  process<PAD2018_TExpDefn, PAD2018_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}

// Tree Definition Group: OSCAR
else if (OSC) {
  process<OSC_TExpDefn, OSC_TEvent>
  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());
}

  
  return 0;
}
