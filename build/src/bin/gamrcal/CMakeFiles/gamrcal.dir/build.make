# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/99j/git/gamma-root

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/99j/git/gamma-root/build

# Include any dependencies generated for this target.
include src/bin/gamrcal/CMakeFiles/gamrcal.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/bin/gamrcal/CMakeFiles/gamrcal.dir/compiler_depend.make

# Include the progress variables for this target.
include src/bin/gamrcal/CMakeFiles/gamrcal.dir/progress.make

# Include the compile flags for this target's objects.
include src/bin/gamrcal/CMakeFiles/gamrcal.dir/flags.make

src/bin/gamrcal/CMakeFiles/gamrcal.dir/gamrcal.cc.o: src/bin/gamrcal/CMakeFiles/gamrcal.dir/flags.make
src/bin/gamrcal/CMakeFiles/gamrcal.dir/gamrcal.cc.o: ../src/bin/gamrcal/gamrcal.cc
src/bin/gamrcal/CMakeFiles/gamrcal.dir/gamrcal.cc.o: src/bin/gamrcal/CMakeFiles/gamrcal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/99j/git/gamma-root/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/bin/gamrcal/CMakeFiles/gamrcal.dir/gamrcal.cc.o"
	cd /Users/99j/git/gamma-root/build/src/bin/gamrcal && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/bin/gamrcal/CMakeFiles/gamrcal.dir/gamrcal.cc.o -MF CMakeFiles/gamrcal.dir/gamrcal.cc.o.d -o CMakeFiles/gamrcal.dir/gamrcal.cc.o -c /Users/99j/git/gamma-root/src/bin/gamrcal/gamrcal.cc

src/bin/gamrcal/CMakeFiles/gamrcal.dir/gamrcal.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gamrcal.dir/gamrcal.cc.i"
	cd /Users/99j/git/gamma-root/build/src/bin/gamrcal && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/99j/git/gamma-root/src/bin/gamrcal/gamrcal.cc > CMakeFiles/gamrcal.dir/gamrcal.cc.i

src/bin/gamrcal/CMakeFiles/gamrcal.dir/gamrcal.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gamrcal.dir/gamrcal.cc.s"
	cd /Users/99j/git/gamma-root/build/src/bin/gamrcal && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/99j/git/gamma-root/src/bin/gamrcal/gamrcal.cc -o CMakeFiles/gamrcal.dir/gamrcal.cc.s

src/bin/gamrcal/CMakeFiles/gamrcal.dir/Gain.cc.o: src/bin/gamrcal/CMakeFiles/gamrcal.dir/flags.make
src/bin/gamrcal/CMakeFiles/gamrcal.dir/Gain.cc.o: ../src/bin/gamrcal/Gain.cc
src/bin/gamrcal/CMakeFiles/gamrcal.dir/Gain.cc.o: src/bin/gamrcal/CMakeFiles/gamrcal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/99j/git/gamma-root/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/bin/gamrcal/CMakeFiles/gamrcal.dir/Gain.cc.o"
	cd /Users/99j/git/gamma-root/build/src/bin/gamrcal && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/bin/gamrcal/CMakeFiles/gamrcal.dir/Gain.cc.o -MF CMakeFiles/gamrcal.dir/Gain.cc.o.d -o CMakeFiles/gamrcal.dir/Gain.cc.o -c /Users/99j/git/gamma-root/src/bin/gamrcal/Gain.cc

src/bin/gamrcal/CMakeFiles/gamrcal.dir/Gain.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gamrcal.dir/Gain.cc.i"
	cd /Users/99j/git/gamma-root/build/src/bin/gamrcal && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/99j/git/gamma-root/src/bin/gamrcal/Gain.cc > CMakeFiles/gamrcal.dir/Gain.cc.i

src/bin/gamrcal/CMakeFiles/gamrcal.dir/Gain.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gamrcal.dir/Gain.cc.s"
	cd /Users/99j/git/gamma-root/build/src/bin/gamrcal && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/99j/git/gamma-root/src/bin/gamrcal/Gain.cc -o CMakeFiles/gamrcal.dir/Gain.cc.s

# Object files for target gamrcal
gamrcal_OBJECTS = \
"CMakeFiles/gamrcal.dir/gamrcal.cc.o" \
"CMakeFiles/gamrcal.dir/Gain.cc.o"

# External object files for target gamrcal
gamrcal_EXTERNAL_OBJECTS =

src/bin/gamrcal/gamrcal: src/bin/gamrcal/CMakeFiles/gamrcal.dir/gamrcal.cc.o
src/bin/gamrcal/gamrcal: src/bin/gamrcal/CMakeFiles/gamrcal.dir/Gain.cc.o
src/bin/gamrcal/gamrcal: src/bin/gamrcal/CMakeFiles/gamrcal.dir/build.make
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libCore.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libImt.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libRIO.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libNet.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libHist.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libGraf.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libGraf3d.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libGpad.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libROOTDataFrame.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libTree.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libTreePlayer.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libRint.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libPostscript.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libMatrix.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libPhysics.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libMathCore.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libThread.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libMultiProc.so
src/bin/gamrcal/gamrcal: /Users/99j/root_build/lib/libROOTVecOps.so
src/bin/gamrcal/gamrcal: src/bin/gamrcal/CMakeFiles/gamrcal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/99j/git/gamma-root/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable gamrcal"
	cd /Users/99j/git/gamma-root/build/src/bin/gamrcal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gamrcal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/bin/gamrcal/CMakeFiles/gamrcal.dir/build: src/bin/gamrcal/gamrcal
.PHONY : src/bin/gamrcal/CMakeFiles/gamrcal.dir/build

src/bin/gamrcal/CMakeFiles/gamrcal.dir/clean:
	cd /Users/99j/git/gamma-root/build/src/bin/gamrcal && $(CMAKE_COMMAND) -P CMakeFiles/gamrcal.dir/cmake_clean.cmake
.PHONY : src/bin/gamrcal/CMakeFiles/gamrcal.dir/clean

src/bin/gamrcal/CMakeFiles/gamrcal.dir/depend:
	cd /Users/99j/git/gamma-root/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/99j/git/gamma-root /Users/99j/git/gamma-root/src/bin/gamrcal /Users/99j/git/gamma-root/build /Users/99j/git/gamma-root/build/src/bin/gamrcal /Users/99j/git/gamma-root/build/src/bin/gamrcal/CMakeFiles/gamrcal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/bin/gamrcal/CMakeFiles/gamrcal.dir/depend

