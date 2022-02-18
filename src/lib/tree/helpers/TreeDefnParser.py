#!/usr/bin/python3

import copy
import re
import sys

def WeightType(T : str):
    if (T == "Bool_t" or T == "O"):
        return 11
    elif (T == "Char_t" or T == "B"):
        return 10    
    elif (T == "UChar_t" or T == "b"):
        return 9
    elif (T == "Short_t" or T == "S"):
        return 8
    elif (T == "UShort_t" or T == "s"):
        return 7
    elif (T == "Float_t" or T == "F"):
        return 6
    elif (T == "Int_t" or T == "i"):
        return 5
    elif (T == "UInt_t" or T == "I"):
        return 4
    elif (T == "Double_t" or T == "D"):
        return 3
    elif (T == "Long64_t" or T == "L"):
        return 2
    elif (T == "ULong64_t" or T == "l"):
        return 1
    else:
        return -1
    
class DetType(object):
    def __init__(self):
        self.measurements = [] # strings
        self.typename = "TDetector"

    def Clear(self):
        self.measurements.clear()
        self.typename = "TDetector"

    def SetAsDefn(self):
        self.typename = "TDetDefn"

    def SetAsDetector(self):
        self.typename = "TDetector"
        
    def AddMeasurement(self, T : str):
        if (WeightType(T) > 0):
            self.measurements.append(T)
            self.measurements.sort(key=WeightType, reverse=False)
            
    def GetMeasurements(self):
        return self.measurements

    def __len__(self):
        return len(self.measurements)
    
    def __lt__(self, other):
        return len(self.measurements) < len(other.measurements)

    def __str__(self):
        return "GamR::Tree::{}<{}>".format(self.typename, ", ".join(self.measurements))

    def __repr__(self):
        return "GamR::Tree::{}<{}>".format(self.typename, ", ".join(self.measurements))
    
class EventType(object):
    def __init__(self):
        self.detectors = [] # DetType objects
        self.typename = "TEvent"
        self.prefix = ""
        self.group = ""
        self.description = ""
        
    def Clear(self):
        self.detectors.clear()
        self.typename = "TEvent"
        self.prefix = ""
        self.group = ""
        self.description = ""

    def SetPrefix(self, prefix : str):
        self.prefix = prefix

    def SetGroup(self, group : str):
        self.group = group

    def SetDescription(self, description : str):
        self.description = ""
        
    def SetAsDefn(self, detectors = True):
        self.typename = "TExpDefn"
        if (detectors):
            [d.SetAsDefn() for d in self.detectors]

    def SetAsEvent(self, detectors = True):
        self.typename = "TEvent"
        if (detectors): 
            [d.SetAsDetector() for d in self.detectors]
        
    def AddDetector(self, det):
        if (len(det) > 0):
            copied = copy.deepcopy(det)
            self.detectors.append(copied)
            #self.detectors.sort(key=None, reverse=True)

    def GetDetectors(self):
        return self.detectors

    def __str__(self):
        #return "GamR::Tree::{}<{}>".format(self.typename, ", ".join(["{}_TDetector{}".format(self.prefix, i) for i in range(len(self.detectors))]))
        return "GamR::Tree::{}<{}>".format(self.typename, ", ".join(map(str,self.detectors)))

    def __repr__(self):
          return __str__(self)                                 

        #return "GamR::Tree::{}<{}>".format(self.typename, ", ".join(map(str,self.detectors)))
    
    def TypeDefs(self):

        title = "{}, {}".format(self.group, self.prefix).center(60)

        cdoc = lambda comment: "/* "+comment.replace("\n", "\n * ")+ " */"        
        typedef = lambda name, t: "using {} = {};".format(name, t)

        self.SetAsDefn()
        expdefn = typedef("{}_TExpDefn".format(self.prefix), self)

        detdefns = []
        for i, detdefn in enumerate(self.GetDetectors()):
            detdefns.append(typedef("{}_TDetDefn{}".format(self.prefix, i), detdefn))
        detdefns = "\n".join(detdefns)
            
        self.SetAsEvent()
        event = typedef("{}_TEvent".format(self.prefix), self)
        
        detectors = []
        for i, det in enumerate(self.GetDetectors()):
            detectors.append(typedef("{}_TDetector{}".format(self.prefix, i), det))
        detectors = "\n".join(detectors)
            
        return "\n".join([cdoc("-"*60), cdoc(title), cdoc("-"*60),
                          "// DetDefns",
                          detdefns,
                          "// ExpDefns",
                          expdefn, 
                          "// Detectors",
                          detectors,
                          "// Event", 
                          event])

    def LinkDefs(self):
        title = 60*"-"+"\n{}, {}".format(self.group, self.prefix)

        template = lambda base, ts,also="": base.replace("<>", "<"+", ".join(ts)+"{}>".format(also))
        linkdef = lambda x: "#pragma link C++ class {}+;".format(x)
        cdoc = lambda comment: "/* "+comment.replace("\n", "\n * ")+ " */"

        linkdefout = {"detdefn": [], "det": [], "meas": [], "expdefn": "", "event": "", "detvec": [], "detvectuple": ""}
        
        # Detectors need std::tuple<std::pair<Ts,Double_t>...>>
        # Events need a std::tuple<std::vector<Detectors>...>
        titlemeas = []
        for i, detector in enumerate(self.GetDetectors()):
            titlemeas.append( ", ".join(detector.GetMeasurements()) )
            pairs = [template("std::pair<>", [t], ", Double_t") for t in detector.GetMeasurements()]
            linkdefout["meas"].append( template("std::tuple<>", pairs) )

            detector.SetAsDetector()            
            linkdefout["detvec"].append( template("std::vector<>", [str(detector)]) )
            linkdefout["det"].append( str(detector) )
            detector.SetAsDefn()
            linkdefout["detdefn"].append( str(detector) )

        title += "\n"+"\n".join(titlemeas)
        # remove duplicate and resort
        linkdefout["detdefn"] = sorted(list(set(linkdefout["detdefn"])), key=lambda x: -len(x))
        linkdefout["det"] = sorted(list(set(linkdefout["det"])), key=lambda x: -len(x))
        linkdefout["meas"] = sorted(list(set(linkdefout["meas"])), key=lambda x: -len(x))

        # now lets do the event object
        # first fill the event / expdefn
        self.SetAsDefn()
        linkdefout["expdefn"] = str(self)
        self.SetAsEvent()
        linkdefout["event"] = str(self)
        # join the detvecs into a tuple
        linkdefout["detvectuple"] = template("std::tuple<>", linkdefout["detvec"])

        # finally, we construct/print the Linkdef
        out = [cdoc(title), cdoc("-"*60),
               cdoc("Detectors".center(60))]
        out += [linkdef(i) for i in linkdefout["meas"]]
        out += [linkdef(i) for i in linkdefout["detdefn"]]
        out += [linkdef(i) for i in linkdefout["det"]]
        out += [cdoc("-"*60)]
        out += [cdoc("Event".center(60))]
        out += [linkdef(linkdefout["detvectuple"]), linkdef(linkdefout["expdefn"]), linkdef(linkdefout["event"])]

        return "\n".join(out)


    def root2gamr(self):
        flag = "args::Flag %s(%s, \"%s\", \"%s\", {\"%s\"});\n" % (self.prefix, self.group, self.prefix, (self.group+" "+self.prefix), self.prefix)
        statement =  "else if (%s) {\n" % self.prefix
        statement += "  process<{}_TExpDefn, {}_TEvent>\n".format(self.prefix, self.prefix)
        statement += "  (infiles.Get(), inifile.Get(), outfilename.Get(), offset.Get(),nevents.Get(), quiet.Get(), compression.Get(), splitmb.Get(), overwrite.Get());\n"
        statement += "}\n"

        return flag, statement


class TreeDefinitions(object):
    def __init__(self, filename : str):
        #self.thefile = open(filename)
        self.filename = filename
        self.header = {0: "Group Number",
                       1: "ULong64_t",
                       2: "Long64_t",
                       3: "Double_t",
                       4: "UInt_t",
                       5: "Int_t",
                       6: "Float_t",
                       7: "UShort_t",
                       8: "Short_t",
                       9: "UChar_t",
                       10: "Char_t",
                       11: "Bool_t"}

        self.current_tree_group = ""
        self.current_event_type = ""
        self.current_line = ""
        self.line_number = 0;
        self.detector = DetType()
        self.event = EventType()

        self.definitions = {}

        headerstr = "| "+" | ".join(self.header.values())+" |"
        rulestr = re.sub("[^\|]+", lambda m: (len(m.group())-1)*"-"+":", headerstr)
        
        with open(filename) as f:
            line = f.readline()
            while (line != ''): # not eof
                line = f.readline() 
                # check if we've hit a new section
                foundgroup = re.search("^#\s*{#([A-Z0-9_]+)}\s*$", line)
                foundevent = re.search("^##\s*{#([A-Z0-9_]+)}$", line)
                foundheader = (line.strip() == headerstr)

                # if it's a new group section, create it in the dictionary
                if   (foundgroup):
                    self.current_tree_group = foundgroup.groups()[0]
                    self.definitions[self.current_tree_group] = {}

                # if it's an event, assume we're still in the last found section
                # setup the appropriate sub dictionary
                elif (foundevent):
                    self.current_event_type = foundevent.groups()[0]
                    self.definitions[self.current_tree_group][self.current_event_type] = {
                        "description": self.current_tree_group + " " + self.current_event_type,
                        "detectors"  : [],
                        "sorts"      : []} # the table

                # alternatively, if it looks like a measurements data table, assume it's for the
                # previously found event and lets read it!
                elif (foundheader):
                    line = f.readline()
                    # make sure this table is somehow half decent. We matched the header, make sure the
                    # rule underneath is well formed. This means you can't be lazy.
                    if (line.strip() != rulestr):
                        print("WARNING: Ill formed table in Tree Group: {}\nEvent: {}\n -- SKIPPING".format(self.current_tree_group,
                                                                                                          self.current_event_type))
                        continue

                    # read the measurements from the table
                    rownum = 0
                    while (True):
                        linepos = f.tell()
                        line = f.readline()
                        # get rid of anything that's not a number between the |
                        # and throwaway the bookends
                        data = re.sub("[^0-9\|]", "",line).split("|")[1:-1]
                        # check this "row" if it's not part of the table, throw it away
                        if (len(data) != 12):
                            # go backwards
                            f.seek(linepos)
                            break
                        else:
                            rownum += 1
                        # okay so convert the row into a list of data type strings for DetType.AddMeasurement
                        measurements = []
                        for idx, num in enumerate(data[1:]):
                            # self.header starts from 1 rather than zero
                            measurements += int(num)*[self.header[idx+1]]
                        self.definitions[self.current_tree_group][self.current_event_type]["detectors"].append(measurements)
                        

    def __PopulateEvent(self, group : str, event : str):
        self.event.Clear()
        self.event.SetGroup(group)
        self.event.SetPrefix(event)
        self.event.SetDescription(self.definitions[group][event]["description"])
        # each detector 
        for meastypes in self.definitions[group][event]["detectors"]:
            self.detector.Clear()
            # fill the detector definition
            [self.detector.AddMeasurement(T) for T in meastypes]
            # deep copy into the event
            self.event.AddDetector(self.detector)        

    def Definitions(self):
        for group in self.definitions:
            yield (group, self.definitions[group].keys())

    def LinkDefs(self, group : str, event : str):
        self.__PopulateEvent(group, event)
        return self.event.LinkDefs()

    def TypeDefs(self, group : str, event : str):
        self.__PopulateEvent(group, event)
        return self.event.TypeDefs()

    def root2gamr(self, group : str, event : str):
        self.__PopulateEvent(group, event)
        return self.event.root2gamr()
        
    def __repr__(self):
        string = "GammaROOT Tree Definition parser.\nInput: {}\n".format(self.filename)
        for group, event in self.Definitions():
            string += "{:>20} :: ".format(group)
            for e in event:
                string += "{} ".format(e)
            string += "\n"
        return string


if __name__=="__main__":
    if len(sys.argv) == 1:
        print("USAGE: {} treetypes.md [linkdef,typedef,root2gamr_args,root2gamr_process]".format(sys.argv[0].split("/")[-1]))
        sys.exit()
    elif len(sys.argv) == 2:
        print("")
        print(TreeDefinitions(sys.argv[1]))
    elif (len(sys.argv) == 3):
        defns = TreeDefinitions(sys.argv[1])
        thetype = sys.argv[2]
        for group, groupevents in defns.Definitions():
            print("\n// Tree Definition Group: {}".format(group))
            if (thetype == "root2gamr_args"):
                print("args::Group {}(treetype, \"Tree Group: {}\", args::Group::Validators::Xor);".format(group, group))


            for event in groupevents:
                if (thetype == "linkdef"):
                    print(defns.LinkDefs(group, event), end="\n\n")
                elif (thetype == "typedef"):
                    print(defns.TypeDefs(group, event), end="\n\n")
                elif (thetype == "root2gamr_args"):
                    print(defns.root2gamr(group, event)[0], end="")
                elif (thetype == "root2gamr_process"):
                    print(defns.root2gamr(group, event)[1], end="")
