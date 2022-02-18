# Converting data into an Event Tree {#root_to_gamr}

The program root2gamr is used to create a TTree containing events as described in \ref tree.

The first step to creating a GamR tree is defining the tree type.  For this see \ref treetypes to check if the type required exists already, and, if necessary edit treetypes.md and recompile to add your own. Once this has been completed, a configuration file will need to be created to handle the configuration for your specific conversion.

# Raw tree file

The input for a GamR tree is known as a "Raw tree". This is a very simple structure that contains a TTree called "RawTree".  The raw tree should contain a branch for each measurement that could be made in a particular event.  For example, the energy recorded by a particular detector, the time at which a detection occurred, or any other flag or piece of information associated with the event.  root2gamr is a program that takes this raw tree and converts it into the GamR event tree.

# Configuration file

The configuration file handles all the information needed to create the GamR tree. This file is an [.INI file] (http://en.wikipedia.org/wiki/INI_file), and is processed by the library [inih](https://github.com/benhoyt/inih).

The first section necessary is the [array] section, which contains the name [groups], which is a list of an arbitrary name for each of the detector groups for the desired tree type.  After this, a list of detector names for each detector group should be given.  For example:

```
[array]
groups = HPGE LABR
HPGE = HPGE1 HGPE2 HPGE3 HGPE4
LABR = LABR1 LABR2
```

This defines two groups (HPGE and LABR), corresponding to Germanium and Lanthanum Bromide detectors.  There are four Germanium detectors (HPGE1 - HPGE4) and two Lanthanum Bromide detectors (LABR1 and LABR2).

After this section follows a section for each individual detector.  The section names should be the detector names previously listed, and in each section a number of detector properties can be set.

## Detectors

The properties and a brief description of their function is given in the following table

| Property | Description |
|---------:|------------:|
| id | Unique (integer) identifier of the detector, stored in TDetector::ID |
| efficiency | Detector efficiency, stored in TDetector::Eff |
| branches | List of strings giving the branches in the input tree to assign to each measurement | 
| calibration | List of calibration strings | 
| pollgate |  |
| pollfreq |  |

### Calibration

Each raw datum (from the source tree) will be written to the event tree, as well as a calibrated value.  The calibration is defined by a string which is changed into a TFormula.  The values of the each of the n branches are assigned to the first n parameters of the TFormula.  The values x, y, z, and t, have special values as defined below.  Additionally, the event number can be accessed by the n+1 parameter.

| Value | Description |
|---------:|------------:|
| x | Random sample from the uniform [0,1) distribution  |
| y | Random sample from a Gaussian distribution |
| z | Standard deviation from the poll histogram |
| t | Mean of the poll histogram |

For example, a line in the configuration file for a detector with two measurements might be

```
calibration = [0]?(([2]>10000)?(([0]+x)*0.534-1.435):(([0]+x)*0.498-2.346)):[0]          [1]?(([1]+x)*0.1023):[1]
```

Note that:
+ The symbol x is used to dither raw integer values 
+ [0] represents the first datum, [1] the second datum, and [2] the event number
+ The ternary operator is used to both ensure that
  + Calibrations are only applied to non-zero raw datums
  + For the first measurement, a different calibration is applied for events before number 10000 and after (i.e. in the case of a gain drift)

Other branch values can also be used in each string, so for example this is a valid statement

```
calibration = [0]*1.0324+[1]            [1]*0.4358-[0]
```

Where the calibration string for each branch references the data from the other branches.  Note however, that the data used are raw if the calibration for that branch has not been processed yet, or calibrated if it has.  So in the previous example, the first [1] is the raw data from the second branch, whilst the second [0] (in the [1] calibration string) is the calibrated value, just previously calculated.

### Example detector section

```
[HPGE1]
id = 1
efficiency = 1
require = 2
calibration = [0]?(([0]+x)*0.50576713+0.65660738):[0] [1]?([1]+x)*0.10226634:[1]
branches = m1.1_HPGe_OBI_1 m1.6_GeTAC
```

In this case, the detector HPGE1 is assigned the ID 1, branches corresponding to a branch for the energy (m1.1_HPGe_OBI_1) and time (m1.6_GeTAC). Both energy and time are required for the detector to have fired (require = 2), and appropriate calibration strings are assigned to each measurement.

# Running root2gamr

After the [.INI file] has been created, the program root2gamr can be run.  Running root2gamr with no arguments will print a help message that gives the options for correct usage.  Basic options are given below.

| Flag | Description |
|---------:|------------:|
| -h | Display help menu |
| -i | Input file name |
| -c | Configuration file name |
| -o | Output file containing the event tree |

Additionally, a flag specifying the type of event is necessary.  This corresponds to the type added in treetypes.md.  For example

```
root2gamr -i input_file.root -c my_conf.ini -o output.gamr.root --D321 
```

will take the raw file input_file.root and process it using the configuration specified in my_conf.ini, writing the output to output.gamr.root (which will be created).  This is using the event type D321, which contains three groups of detectors: the first with three UInt_t measurements, the second with two UInt_t measurements, and the third with a single UInt_t. 

@addtogroup Tree
