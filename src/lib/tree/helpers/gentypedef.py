#!/usr/bin/python3
import sys

def ExpandTypes(groups: list):
    for types in groups:
        for idx, t in enumerate(types):
            if (t == "B"):
                types[idx] = "Char_t"
            elif (t == "b"):
                types[idx] = "UChar_t"
            elif (t == "S"):
                types[idx] = "Short_t"
            elif (t == "s"):
                types[idx] = "UShort_t"
            elif (t == "I"):
                types[idx] = "Int_t"
            elif (t == "i"):
                types[idx] = "UInt_t"
            elif (t == "F"):
                types[idx] = "Float_t"
            elif (t == "D"):
                types[idx] = "Double_t"
            elif (t == "L"):
                types[idx] = "Long64_t"
            elif (t == "l"):
                types[idx] = "ULong64_t"
            elif (t == "O"):
                types[idx] = "Bool_t"

                
def GamRTreeTypedef(myevent: list, prefix: str):
    # stolen from genlinkdef.py
    ExpandTypes(myevent)
    template = lambda base, ts: base.replace("<>", "<"+", ".join(ts)+">")
    typedef = lambda name, t: "using {} = {};".format(name,t)
    
    TDetDefns = [template("GamR::Tree::TDetDefn<>", ts) for ts in myevent]
    TDetectors = [template("GamR::Tree::TDetector<>", ts) for ts in myevent]

    myTDetDefns = []
    print("// DetDefns")
    for i,detdefn in enumerate(TDetDefns):
        myTDetDefns.append("{}_TDetDefn{}".format(prefix, i))        
        print(typedef("{}_TDetDefn{}".format(prefix, i), detdefn))

    print("// ExpDefn")
    TExpDefn = template("GamR::Tree::TExpDefn<>", myTDetDefns)
    print(typedef("{}_TExpDefn".format(prefix), TExpDefn))

    print("// Detectors")
    myTDetectors = []
    for i,detector in enumerate(TDetectors):
        myTDetectors.append("{}_TDetector{}".format(prefix, i))
        print(typedef(myTDetectors[-1], detector))

    print("// Event")
    TEvent = template("GamR::Tree::TEvent<>", myTDetectors)
    print(typedef("{}_TEvent".format(prefix), TEvent))




if __name__=="__main__":
    if len(sys.argv) == 1:
        print("USAGE: {} <comment> prefix g1t1,g1t2... g2t1,...".format(sys.argv[0].split("/")[-1]))
        sys.exit()
        
    cmdevent = [t.split(",") for t in sys.argv[3:]]
    GamRTreeTypedef(cmdevent, sys.argv[2])

