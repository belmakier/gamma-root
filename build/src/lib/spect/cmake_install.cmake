# Install script for directory: /Users/99j/git/gamma-root/src/lib/spect

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/99j/.local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0" TYPE SHARED_LIBRARY FILES "/Users/99j/git/gamma-root/build/src/lib/spect/libgamr_spect_rdict.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect_rdict.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect_rdict.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/99j/root_build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect_rdict.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/99j/git/gamma-root/build/src/lib/nucleus"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect_rdict.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/99j/git/gamma-root/build/src/lib/toolkit"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect_rdict.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/99j/git/gamma-root/build/src/lib/utils"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect_rdict.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/99j/.local/lib/gamr-0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect_rdict.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/99j/root_build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect_rdict.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect_rdict.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0" TYPE FILE FILES "/Users/99j/git/gamma-root/build/src/lib/spect/libgamr_spect_rdict.pcm")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gamr-0.0.0/spect" TYPE FILE FILES
    "/Users/99j/git/gamma-root/src/lib/spect/IO.hh"
    "/Users/99j/git/gamma-root/src/lib/spect/Cut.hh"
    "/Users/99j/git/gamma-root/src/lib/spect/Integral.hh"
    "/Users/99j/git/gamma-root/src/lib/spect/Transform.hh"
    "/Users/99j/git/gamma-root/src/lib/spect/Fit.hh"
    "/Users/99j/git/gamma-root/src/lib/spect/FitGuesses.hh"
    "/Users/99j/git/gamma-root/src/lib/spect/Display.hh"
    "/Users/99j/git/gamma-root/src/lib/spect/FFT.hh"
    "/Users/99j/git/gamma-root/src/lib/spect/Backsub.hh"
    "/Users/99j/git/gamma-root/src/lib/spect/Calibrate.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0" TYPE SHARED_LIBRARY FILES "/Users/99j/git/gamma-root/build/src/lib/spect/libgamr_spect.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/99j/root_build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/99j/git/gamma-root/build/src/lib/spect"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/99j/git/gamma-root/build/src/lib/nucleus"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/99j/git/gamma-root/build/src/lib/toolkit"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/99j/git/gamma-root/build/src/lib/utils"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/99j/.local/lib/gamr-0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/99j/root_build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/gamr-0.0.0/libgamr_spect.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gamr-0.0.0" TYPE FILE FILES "/Users/99j/git/gamma-root/src/lib/spect/FitGuesses.dat")
endif()

