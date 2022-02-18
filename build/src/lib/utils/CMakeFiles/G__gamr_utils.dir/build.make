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

# Utility rule file for G__gamr_utils.

# Include any custom commands dependencies for this target.
include src/lib/utils/CMakeFiles/G__gamr_utils.dir/compiler_depend.make

# Include the progress variables for this target.
include src/lib/utils/CMakeFiles/G__gamr_utils.dir/progress.make

src/lib/utils/CMakeFiles/G__gamr_utils: src/lib/utils/G__gamr_utils.cxx
src/lib/utils/CMakeFiles/G__gamr_utils: src/lib/utils/libgamr_utils_rdict.pcm
src/lib/utils/CMakeFiles/G__gamr_utils: src/lib/utils/libgamr_utils.rootmap

src/lib/utils/G__gamr_utils.cxx: src/lib/utils/gamr_utils_Linkdef.h
src/lib/utils/G__gamr_utils.cxx: ../src/lib/utils/REPL.hh
src/lib/utils/G__gamr_utils.cxx: ../src/lib/utils/Utilities.hh
src/lib/utils/G__gamr_utils.cxx: ../src/lib/utils/Tuples.hh
src/lib/utils/G__gamr_utils.cxx: ../src/lib/utils/RTTI.hh
src/lib/utils/G__gamr_utils.cxx: ../src/lib/utils/REPL.hh
src/lib/utils/G__gamr_utils.cxx: ../src/lib/utils/Utilities.hh
src/lib/utils/G__gamr_utils.cxx: ../src/lib/utils/Tuples.hh
src/lib/utils/G__gamr_utils.cxx: ../src/lib/utils/RTTI.hh
src/lib/utils/G__gamr_utils.cxx: src/lib/utils/gamr_utils_Linkdef.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/99j/git/gamma-root/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating G__gamr_utils.cxx, libgamr_utils_rdict.pcm, libgamr_utils.rootmap"
	cd /Users/99j/git/gamma-root/build/src/lib/utils && /Applications/CMake.app/Contents/bin/cmake -E env LD_LIBRARY_PATH=/Users/99j/root_build/lib: /Users/99j/root_build/bin/rootcling -v2 -f G__gamr_utils.cxx -s /Users/99j/git/gamma-root/build/src/lib/utils/libgamr_utils.dylib -rml libgamr_utils.dylib -rmf /Users/99j/git/gamma-root/build/src/lib/utils/libgamr_utils.rootmap -I/Users/99j/git/gamma-root/src/lib/utils -compilerI/usr/X11/include -compilerI/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.0.sdk/usr/include/c++/v1 -compilerI/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/13.0.0/include -compilerI/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.0.sdk/usr/include -compilerI/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include -compilerI/usr/X11/include -compilerI/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/13.0.0/include -compilerI/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.0.sdk/usr/include -compilerI/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include -I/Users/99j/root_build/include -I/Users/99j/git/gamma-root/src/lib/utils REPL.hh Utilities.hh Tuples.hh RTTI.hh /Users/99j/git/gamma-root/build/src/lib/utils/gamr_utils_Linkdef.h

src/lib/utils/libgamr_utils_rdict.pcm: src/lib/utils/G__gamr_utils.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate src/lib/utils/libgamr_utils_rdict.pcm

src/lib/utils/libgamr_utils.rootmap: src/lib/utils/G__gamr_utils.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate src/lib/utils/libgamr_utils.rootmap

G__gamr_utils: src/lib/utils/CMakeFiles/G__gamr_utils
G__gamr_utils: src/lib/utils/G__gamr_utils.cxx
G__gamr_utils: src/lib/utils/libgamr_utils.rootmap
G__gamr_utils: src/lib/utils/libgamr_utils_rdict.pcm
G__gamr_utils: src/lib/utils/CMakeFiles/G__gamr_utils.dir/build.make
.PHONY : G__gamr_utils

# Rule to build all files generated by this target.
src/lib/utils/CMakeFiles/G__gamr_utils.dir/build: G__gamr_utils
.PHONY : src/lib/utils/CMakeFiles/G__gamr_utils.dir/build

src/lib/utils/CMakeFiles/G__gamr_utils.dir/clean:
	cd /Users/99j/git/gamma-root/build/src/lib/utils && $(CMAKE_COMMAND) -P CMakeFiles/G__gamr_utils.dir/cmake_clean.cmake
.PHONY : src/lib/utils/CMakeFiles/G__gamr_utils.dir/clean

src/lib/utils/CMakeFiles/G__gamr_utils.dir/depend:
	cd /Users/99j/git/gamma-root/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/99j/git/gamma-root /Users/99j/git/gamma-root/src/lib/utils /Users/99j/git/gamma-root/build /Users/99j/git/gamma-root/build/src/lib/utils /Users/99j/git/gamma-root/build/src/lib/utils/CMakeFiles/G__gamr_utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lib/utils/CMakeFiles/G__gamr_utils.dir/depend

