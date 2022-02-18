# Install script for directory: /Users/99j/git/gamma-root/src/bin/root2gamr

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/99j/git/gamma-root/build/src/bin/root2gamr/root2gamr")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/root2gamr" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/root2gamr")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/99j/root_build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/root2gamr")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/99j/git/gamma-root/build/src/lib/tree"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/root2gamr")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/99j/.local/lib/gamr-0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/root2gamr")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/99j/root_build/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/root2gamr")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/root2gamr")
    endif()
  endif()
endif()

