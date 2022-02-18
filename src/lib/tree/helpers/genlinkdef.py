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


def GamRTreeLinkdef(prefix: str, myevent: list, detectors=True, event=True):
    # begin mad foo, yeeee boiiii!
    ExpandTypes(myevent)
    template = lambda base, ts,also="": base.replace("<>", "<"+", ".join(ts)+"{}>".format(also))
    linkdef = lambda x: "#pragma link C++ class %s+;" % x
    cdoc = lambda comment: "/* "+comment.replace("\n", "\n * ")+ " */"
    
    # fMeasTuples is fMeasurements in TDetectors
    fMeasPairs = []
    for ts in myevent:
        fMeasPairs.append([])
        for t in ts:
            fMeasPairs[-1].append(template("std::pair<>", [t], ", Double_t"))
    fMeasTuples = [template("std::tuple<>", ts) for ts in fMeasPairs]
    TDetDefns = [template("GamR::Tree::TDetDefn<>", ts) for ts in myevent]
    TDetectors = [template("GamR::Tree::TDetector<>", ts) for ts in myevent]
    
    # fDetTuples is fDetectors in TEvent
    fDetTuples = template("std::tuple<>", [template("std::vector<>", [ts]) for ts in TDetectors])
    TExpDefn = template("GamR::Tree::TExpDefn<>", TDetDefns)
    TEvent = template("GamR::Tree::TEvent<>", TDetectors)
    
    # printing the linkdef
    print(cdoc("GammaROOT Tree "+prefix+"\n" + "\n".join([", ".join(t) for t in myevent])))
    
    if (detectors):
        print(cdoc("Detectors"))
        [print(linkdef(i)) for i in sorted(list(set(fMeasTuples)), key=lambda x: -len(x))]
        [print(linkdef(i)) for i in sorted(list(set(TDetDefns)), key=lambda x: -len(x))]
        [print(linkdef(i)) for i in sorted(list(set(TDetectors)), key=lambda x: -len(x))]

    if (event):
        print(cdoc("Event"))
        print(linkdef(fDetTuples))
        print(linkdef(TExpDefn))
        print(linkdef(TEvent))

if __name__=="__main__":
    if len(sys.argv) == 1:
        print("USAGE: {} [(e)vent, (d)ets, (b)oth] prefix g1t1,g1t2... g2t1,...".format(sys.argv[0].split("/")[-1]))
        sys.exit()
        
    mo = sys.argv[1].lower()
    if mo == "event" or mo == "e":
        event = True;  dets = False
    elif mo == "dets" or mo == "d":
        event = False; dets = True
    elif mo == "both" or mo == "b":
        event = True;  dets = True;
    else:
        print("USAGE: {} [(e)vent, (d)ets, (b)oth] <comment> prefix g1t1,g1t2... g2t1,...".format(sys.argv[0].split("/")[-1]))
        sys.exit()

    cmdevent = [t.split(",") for t in sys.argv[4:]]
    GamRTreeLinkdef(sys.argv[3], cmdevent, dets, event)
