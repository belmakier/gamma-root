# Welcome to GammaROOT! {#mainpage}

@tableofcontents

GammaROOT was developed at the Australian National University,
Department of Nuclear Physics by nuclear structure Ph.D candidates.

CERN ROOT is a very powerful library predominately geared towards
particle physics. GammaROOT is intended to be used along side ROOT. It
provides interactive functions to be used at the ROOT interpreter and
*UNIX philosophy tools for tasks common to the nuclear physicist.

Care is taken to make sure GammaROOT is maintainable, extendable, and
robust. Modern C++ is encouraged as is unit testing.

## ROOT6 and C++14 and beyond

Unfortunately the default compile flags for ROOT6 are to compile with
C++11 rather even though it's perfectly compatable with C++14 and is
only a matter of setting a CMake option. Though, not everyone can (or
are willing) to compile ROOT from source.

Open source libraries are best when more people are using them. For
this reason, GammaROOT does not use C++14 (or higher) extensions. This
will change immediately when the ROOT project changes their defaults.

# Building and installing {#installing}

Tested on Ubuntu 16.04 LTS. Requirements: Doxygen, ROOT v6.10+, GCC,
C++ STL.

Clone the git repository and run the following to pull the external
dependencies.
``` {.sh}
make getreqs 
```

Now to build GammaROOT
```{.sh}
make build prefix="~/.local" # optional, default: "./built"
cd build
make
make install # recommended
```

Or, do all the above in one sweep for `prefix=~/.local`
```{.sh}
make lazy
```

To make and install the documentation and get here:
```{.sh}
make lazydoc
make opendoc
```
## Build options

GamR is comprised of several modules, not all of which are necessary
and some of which have extra dependencies. By default, a selection of
the most commonly used are enabled in `gamma-root/CMakeLists.txt`:

```
GAMRSORT "GamR sort program" OFF
GAMRNUCLEUS "GamR level scheme drawing and fitting tools " ON
GAMRANGDIST "GamR angular distributions and correlations" ON
GAMRSPECT "GamR spectroscopy tools" ON
GAMRORNL "GamR interface to old ORNL file formats" OFF
GAMRTREE "GamR tree processing" OFF
GAMRVIEWER "GamR tree processing - experimental" OFF
GAMRPROC "GamR fast-timing processor" OFF
GAMREFF "GamR HPGe efficiency fitting" ON
GAMRCOULEX "GamR implementation of Winther-deBoer Coulex codes" OFF
GAMRABBREVS "GamR abbreviations for command-line use" ON
GAMRBATEMAN "GamR Bateman equation solver - requires BOOST" OFF
```

These can be adjusted for your requirements in `gamma-root/CMakeLists.txt`.

## Using GamR everywhere {#environment}

The following example assumes you have built and installed with
`prefix=~/.local`. If not, adjust accordingly.

Set your environment variables by putting the following in your
`~/.profile`, `~/.bashrc`, or something similar:

```{.cc}
export LD_LIBRARY_PATH=~/.local/lib:$LD_LIBRARY_PATH
export PATH=~/.local/bin:$PATH
```
<span style="color: darkgreen;">
[✔] You can run the script `gamrdoc` from anywhere to open this documentation.
</span>

In your `~/.rootrc` add the following lines:
```{.cc}
Unix.*.Root.MacroPath: .:~/.local:
Rint.Logon: ~/.rootlogon.cc
```

In `~/.rootlogon.cc` add the following to intialize GammaROOT

```{.cxx}
{
  // GammaROOT
  gROOT->ProcessLine(".x $HOME/.local/share/gamr-0.0.0/gamrlogon.cc");
}
```

# Original developers {#authors}
+ Timothy Gray <graytj@ornl.gov>
+ Aqeel Akber <aqeel.akber@anu.edu.au>

## Contributors
+ Ben Coombes <ben.coombes@anu.edu.au>
+ Jackson Dowie <jackson.dowie@anu.edu.au>
+ Brendan McCormick

