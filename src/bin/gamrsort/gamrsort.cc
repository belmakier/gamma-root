#include <atomic>
#include <string>
#include <thread>
#include <vector>

#include <args/args.hxx>

#include <tree/Tree.hh>

#include <sort/CoincidenceCubeDiff.hh>
#include <sort/CoincidenceMatrix.hh>
#include <sort/CoincidenceMatrixPair.hh>
#include <sort/GatedTimeDifference.hh>
#include <sort/Matrix.hh>
#include <sort/Sorter.hh>
#include <sort/TimeDifference.hh>
#include <sort/TimeDifferencePairs.hh>
#include <sort/TimeWalkCal.hh>

#include <utils/REPL.hh>

/* TYPEDEFS */
using DCPDet1 = D3221_TDetector3; // from Tree.hh
using DCPDet2 = D3221_TDetector2;
using DCPDet3 = D3221_TDetector0;

int main(const int argc, const char *argv[])
{
   args::ArgumentParser parser("GammaROOT Tree Sorter. ANU Edition.", "Aqeel Akber <aqeel.akber@anu.edu.au>\n"
                                                                      "Contribute! <i.believe.in.you@yourdesk.io>");

   args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
   args::PositionalList<std::string> options(parser, "options", "Options passed to sorts (if applicable)");

   args::Group parser_io(parser, "IO:");
   args::ValueFlagList<std::string, std::vector> infiles(parser_io, "input.root", "Input ROOT file.", {"input"});
   args::ValueFlag<std::string> outfilename(parser_io, "output.root", "Output ROOT file.", {"output"});
   args::ValueFlag<Int_t> compress(parser_io, "101", "Output compression settings", {"compress"}, 101);

   args::Group parser_hist(parser, "Histogram:");
   args::ValueFlag<std::string> nameprefix(parser_hist, "junk", "Histogram name prefix", {"name"});

   args::ValueFlag<ULong64_t> xbins(parser_hist, "4096", "Number of bins on X axis", {"nx"}, 4096);
   args::ValueFlag<Long64_t> xlow(parser_hist, "0", "Low value on X axis", {"xmin"}, 0);
   args::ValueFlag<Long64_t> xhigh(parser_hist, "4096", "High value on X axis", {"xmax"}, 4096);

   args::ValueFlag<ULong64_t> ybins(parser_hist, "4096", "Number of bins on Y ayis", {"ny"}, 4096);
   args::ValueFlag<Long64_t> ylow(parser_hist, "0", "Low value on Y ayis", {"ymin"}, 0);
   args::ValueFlag<Long64_t> yhigh(parser_hist, "4096", "High value on Y ayis", {"ymax"}, 4096);

   args::ValueFlag<ULong64_t> zbins(parser_hist, "512", "Number of bins on Z azis", {"nz"}, 512);
   args::ValueFlag<Long64_t> zlow(parser_hist, "0", "Low value on Z azis", {"zmin"}, 0);
   args::ValueFlag<Long64_t> zhigh(parser_hist, "512", "High value on Z azis", {"zmax"}, 512);

   args::Group parser_gates(parser, "Gates:");
   args::ValueFlagList<std::string, std::vector> gates(parser_gates, "g.m.id lo hi | g.m.id lo hi", "Gate", {"gate"});

   // Sorts
   args::Group parser_sorts(parser, "Type:", args::Group::Validators::AtLeastOne);

   // Matrix
   args::Group parser_matrix(parser_sorts, "Matrix", args::Group::Validators::All);
   args::Flag mat(parser_matrix, "matrix", "2D Histogram", {"matrix"});
   args::ValueFlag<size_t> matgI(parser_matrix, "0", "First detector group", {"gI"}, 0);
   args::ValueFlag<size_t> matgJ(parser_matrix, "0", "Second detector group", {"gJ"}, 0);
   args::ValueFlag<size_t> matmX(parser_matrix, "0", "Measurement X", {"mX"}, 0);
   args::ValueFlag<size_t> matmY(parser_matrix, "0", "Measurement Y", {"mY"}, 0);
   args::Group parser_matrixaxisX(parser_matrix, "X Axis", args::Group::Validators::Xor);
   args::Flag matXcoinc(parser_matrixaxisX, "X", "gI.mX", {"x-coinc"});
   args::Flag matXsum(parser_matrixaxisX, "X+Y", "gI.mX + gJ.mX", {"x-sum"});
   args::Flag matXdiff(parser_matrixaxisX, "X-Y", "gI.mX - gJ.mX", {"x-diff"});
   args::Flag matXprod(parser_matrixaxisX, "X*Y", "gI.mX * gJ.mX", {"x-prod"});
   args::Flag matXratio(parser_matrixaxisX, "X", "gI.mX / gJ.mX", {"x-ratio"});
   args::Group parser_matrixaxisY(parser_matrix, "Y Axis", args::Group::Validators::Xor);
   args::Flag matYcoinc(parser_matrixaxisY, "Y", "gJ.mY", {"y-coinc"});
   args::Flag matYsum(parser_matrixaxisY, "Y+Y", "gJ.mY + gI.mY", {"y-sum"});
   args::Flag matYdiff(parser_matrixaxisY, "Y-Y", "gJ.mY - gI.mY", {"y-diff"});
   args::Flag matYprod(parser_matrixaxisY, "Y*Y", "gJ.mY * gI.mY", {"y-prod"});
   args::Flag matYratio(parser_matrixaxisY, "Y", "gJ.mY / gI.mY", {"y-ratio"});

   // DCP
   // args::Group dcp(parser_sorts, "DCP", args::Group::Validators::Xor);

   // args::Flag d1mat0(dcp, "d1mat0", "x.0 : y.0 \n opts: prefix groupX groupY",
   // {"d1mat0"}); args::Flag d2mat0(dcp, "d2mat0", "x.0 : y.0 \n opts: prefix
   // groupX groupY", {"d2mat0"}); args::Flag d3mat0(dcp, "d3mat0", "x.0 : y.0 \n
   // opts: prefix groupX groupY", {"d3mat0"}); args::Flag d3mat0p(dcp,
   // "d3mat0p", "x.0 : y.0 \n opts: prefix groupX groupY idX idY", {"d3mat0p"});
   // args::Flag d3d2mat0(dcp, "d3d2mat0", "x.0 : y.0 \n opts: prefix groupX
   // groupY", {"d3d2mat0"}); args::Flag d3cube0d1(dcp, "d3cube0d1", "x.0 : y.0 :
   // y.1 - x.1 \n opts: prefix groupX groupY", {"d3cube0d1"}); args::Flag
   // d3tcal(dcp, "d3tcal", "Time Walk E.0 : T.1 \n opts: group ref_E ref_p ref_P
   // ref_b ref_B id1 id2 ... idn", {"d3tcal"}); args::Flag d3tdiff(dcp,
   // "d3tdiff", "Time Difference E.0 : T.1 \n opts: prefix group ref_E ref_p
   // ref_P ref_b ref_B", {"d3tdiff"}); args::Flag d2gated3tdiff(dcp,
   // "d2gated3tdiff", "Gated(d2 S.0) Time Difference(d3 E.0 : T.1) \n opts:
   // prefix group_gate gate_s gate_S group ref_E ref_p ref_P ref_b ref_B",
   // {"d2gated3tdiff"}); args::Flag d3tdiffp(dcp, "d3tdiffp", "Time Difference
   // pairs E.0 : T.1 \n opts: group ref_E ref_p ref_P ref_b ref_B id1 id2 ...
   // idn", {"d3tdiffp"});

   // // Pixie
   // args::Group pixie(parser_sorts, "PIXIE", args::Group::Validators::Xor);
   // args::Flag p1mat1(pixie, "p1mat1", "x.1 : y.1 \n opts: prefix groupX
   // groupY", {"p1mat1"}); args::Flag p1tcal(pixie, "p1tcal", "Time Walk E.1 :
   // T.0 \n opts: group ref_E ref_p ref_P ref_b ref_B id1 id2 ... idn",
   // {"p1tcal"}); args::Flag p1tdiffp(pixie, "p1tdiffp", "Time Difference pairs
   // E.1 : T.0 \n opts: group ref_E ref_p ref_P ref_b ref_B id1 id2 ... idn",
   // {"p1tdiffp"});

   try {
      parser.ParseCLI(argc, argv);
   } catch (args::Help) {
      std::cout << parser;
      return 0;
   } catch (args::ParseError e) {
      std::cerr << e.what() << std::endl;
      std::cerr << parser;
      return 1;
   } catch (args::ValidationError e) {
      std::cerr << e.what() << std::endl;
      std::cerr << parser;
      return 1;
   }

   using namespace GamR::Sort;
   Sorter sorter(infiles.Get(), outfilename.Get(), compress.Get());
   sorter.SetXsize(xbins.Get(), xlow.Get(), xhigh.Get());
   sorter.SetYsize(ybins.Get(), ylow.Get(), yhigh.Get());
   sorter.SetZsize(zbins.Get(), zlow.Get(), zhigh.Get());

   // GamR::Tree::TDetector<UShort_t>(); // hack makes linking to rdict work
   std::thread process([&]() {
      if (false) {
      }

      else if (mat) {
         // work out the axis
         auto xaxis = Type::Matrix::Axis::kCoincidence;
         if (matXcoinc) {
            xaxis = Type::Matrix::Axis::kCoincidence;
         } else if (matXsum) {
            xaxis = Type::Matrix::Axis::kSum;
         } else if (matXdiff) {
            xaxis = Type::Matrix::Axis::kDiff;
         } else if (matXprod) {
            xaxis = Type::Matrix::Axis::kProduct;
         } else if (matXratio) {
            xaxis = Type::Matrix::Axis::kRatio;
         }

         auto yaxis = Type::Matrix::Axis::kCoincidence;
         if (matYcoinc) {
            yaxis = Type::Matrix::Axis::kCoincidence;
         } else if (matYsum) {
            yaxis = Type::Matrix::Axis::kSum;
         } else if (matYdiff) {
            yaxis = Type::Matrix::Axis::kDiff;
         } else if (matYprod) {
            yaxis = Type::Matrix::Axis::kProduct;
         } else if (matYratio) {
            yaxis = Type::Matrix::Axis::kRatio;
         }

         // make the sort
         auto sort = Type::Matrix(&sorter, nameprefix.Get(), matgI.Get(), matgJ.Get(), matmX.Get(), matmY.Get(),
                                  gates.Get(), xaxis, yaxis);

         // process it
         sorter.Process(sort);
      }
      // else if (d1mat0) { sorter.Process<Type::CoincidenceMatrix<DCPDet1,
      // DCPDet1, 0, 0>>(options.Get()); } else if (d2mat0) {
      // sorter.Process<Type::CoincidenceMatrix<DCPDet2, DCPDet2, 0,
      // 0>>(options.Get()); } else if (d3mat0) {
      // sorter.Process<Type::CoincidenceMatrix<DCPDet3, DCPDet3, 0,
      // 0>>(options.Get()); } else if (d3d2mat0) {
      // sorter.Process<Type::CoincidenceMatrix<DCPDet3, DCPDet2, 0,
      // 0>>(options.Get()); } else if (d3mat0p) {
      // sorter.Process<Type::CoincidenceMatrixPair<DCPDet3, DCPDet3, 0,
      // 0>>(options.Get()); } else if (d3cube0d1) {
      // sorter.Process<Type::CoincidenceCubeDiff<DCPDet3,DCPDet3,0,0,1>>(options.Get());
      // } else if (d3tcal) {
      // sorter.Process<Type::TimeWalkCal<DCPDet3,0,1>>(options.Get()); } else if
      // (d3tdiff) {
      // sorter.Process<Type::TimeDifference<DCPDet3,0,1>>(options.Get()); } else
      // if (d2gated3tdiff) { sorter.Process<Type::GatedTimeDifference<DCPDet2, 0,
      // DCPDet3,0,1>>(options.Get()); } else if (d3tdiffp) {
      // sorter.Process<Type::TimeDifferencePairs<DCPDet3,0,1>>(options.Get()); }

      // // PIXIE
      // else if (p1mat1) { sorter.Process<Type::CoincidenceMatrix<P1_TDetector0,
      // P1_TDetector0, 1, 1>>(options.Get()); } else if (p1tcal) {
      // sorter.Process<Type::TimeWalkCal<P1_TDetector0,1,0>>(options.Get()); }
      // else if (p1tdiffp) {
      // sorter.Process<Type::TimeDifferencePairs<P1_TDetector0,1,0>>(options.Get());
      // }
   });

   GamR::Utils::REPL repl("gamrsort > ");
   std::string input;
   while (repl.Loop()) {
      repl.ReadLine(input);
      if (input == "help") {
         std::cout << std::endl << "help | status | save and exit | exit" << std::endl;
      }
      if (input == "status") {
         sorter.PrintStatus();
         std::cout << std::endl;
      }
      if (input == "save and exit") {
         sorter.Halt();
         sorter.Write();
         break;
      }
      if (input == "exit") {
         sorter.Halt();
         break;
      }
      if (sorter.Done()) {
         sorter.Write();
         break;
      }
      if (!input.empty()) {
         repl.Prompt();
      }
   }
   repl.Halt();

   process.join();
}
