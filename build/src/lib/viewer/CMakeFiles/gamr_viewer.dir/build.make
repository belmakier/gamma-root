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
include src/lib/viewer/CMakeFiles/gamr_viewer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/lib/viewer/CMakeFiles/gamr_viewer.dir/compiler_depend.make

# Include the progress variables for this target.
include src/lib/viewer/CMakeFiles/gamr_viewer.dir/progress.make

# Include the compile flags for this target's objects.
include src/lib/viewer/CMakeFiles/gamr_viewer.dir/flags.make

src/lib/viewer/CMakeFiles/gamr_viewer.dir/Viewer.cc.o: src/lib/viewer/CMakeFiles/gamr_viewer.dir/flags.make
src/lib/viewer/CMakeFiles/gamr_viewer.dir/Viewer.cc.o: ../src/lib/viewer/Viewer.cc
src/lib/viewer/CMakeFiles/gamr_viewer.dir/Viewer.cc.o: src/lib/viewer/CMakeFiles/gamr_viewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/99j/git/gamma-root/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/lib/viewer/CMakeFiles/gamr_viewer.dir/Viewer.cc.o"
	cd /Users/99j/git/gamma-root/build/src/lib/viewer && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/lib/viewer/CMakeFiles/gamr_viewer.dir/Viewer.cc.o -MF CMakeFiles/gamr_viewer.dir/Viewer.cc.o.d -o CMakeFiles/gamr_viewer.dir/Viewer.cc.o -c /Users/99j/git/gamma-root/src/lib/viewer/Viewer.cc

src/lib/viewer/CMakeFiles/gamr_viewer.dir/Viewer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gamr_viewer.dir/Viewer.cc.i"
	cd /Users/99j/git/gamma-root/build/src/lib/viewer && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/99j/git/gamma-root/src/lib/viewer/Viewer.cc > CMakeFiles/gamr_viewer.dir/Viewer.cc.i

src/lib/viewer/CMakeFiles/gamr_viewer.dir/Viewer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gamr_viewer.dir/Viewer.cc.s"
	cd /Users/99j/git/gamma-root/build/src/lib/viewer && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/99j/git/gamma-root/src/lib/viewer/Viewer.cc -o CMakeFiles/gamr_viewer.dir/Viewer.cc.s

# Object files for target gamr_viewer
gamr_viewer_OBJECTS = \
"CMakeFiles/gamr_viewer.dir/Viewer.cc.o"

# External object files for target gamr_viewer
gamr_viewer_EXTERNAL_OBJECTS =

src/lib/viewer/libgamr_viewer.dylib: src/lib/viewer/CMakeFiles/gamr_viewer.dir/Viewer.cc.o
src/lib/viewer/libgamr_viewer.dylib: src/lib/viewer/CMakeFiles/gamr_viewer.dir/build.make
src/lib/viewer/libgamr_viewer.dylib: src/lib/viewer/libgamr_viewer_rdict.dylib
src/lib/viewer/libgamr_viewer.dylib: src/lib/tree/libgamr_tree.dylib
src/lib/viewer/libgamr_viewer.dylib: src/lib/tree/libgamr_tree_rdict.dylib
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libCore.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libImt.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libRIO.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libNet.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libHist.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libGraf.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libGraf3d.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libGpad.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libROOTDataFrame.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libTree.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libTreePlayer.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libRint.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libPostscript.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libMatrix.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libPhysics.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libMathCore.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libThread.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libMultiProc.so
src/lib/viewer/libgamr_viewer.dylib: /Users/99j/root_build/lib/libROOTVecOps.so
src/lib/viewer/libgamr_viewer.dylib: src/lib/viewer/CMakeFiles/gamr_viewer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/99j/git/gamma-root/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libgamr_viewer.dylib"
	cd /Users/99j/git/gamma-root/build/src/lib/viewer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gamr_viewer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/lib/viewer/CMakeFiles/gamr_viewer.dir/build: src/lib/viewer/libgamr_viewer.dylib
.PHONY : src/lib/viewer/CMakeFiles/gamr_viewer.dir/build

src/lib/viewer/CMakeFiles/gamr_viewer.dir/clean:
	cd /Users/99j/git/gamma-root/build/src/lib/viewer && $(CMAKE_COMMAND) -P CMakeFiles/gamr_viewer.dir/cmake_clean.cmake
.PHONY : src/lib/viewer/CMakeFiles/gamr_viewer.dir/clean

src/lib/viewer/CMakeFiles/gamr_viewer.dir/depend:
	cd /Users/99j/git/gamma-root/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/99j/git/gamma-root /Users/99j/git/gamma-root/src/lib/viewer /Users/99j/git/gamma-root/build /Users/99j/git/gamma-root/build/src/lib/viewer /Users/99j/git/gamma-root/build/src/lib/viewer/CMakeFiles/gamr_viewer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lib/viewer/CMakeFiles/gamr_viewer.dir/depend

