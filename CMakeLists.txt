# EasyMode gamr/CMakeLists.txt

cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

if (APPLE) 
  set(CMAKE_OSX_DEPLOYMENT_TARGET 12.4)
endif()

project(gamr VERSION 0.0.0 LANGUAGES C CXX Fortran)
set(PROJECT_DESCRIPTION "GammaROOT")

set(GAMR_PROJ_VER ${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optimisation
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -pipe")
#set(CMAKE_VERBOSE_MAKEFILE 1)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

option(GAMRSORT "GamR sort program" OFF)
option(GAMRNUCLEUS "GamR level scheme drawing and fitting tools " ON)
option(GAMRANGDIST "GamR angular distributions and correlations" ON)
option(GAMRSPECT "GamR spectroscopy tools" ON)
option(GAMRORNL "GamR interface to old ORNL file formats" ON)
option(GAMRTREE "GamR tree processing" OFF)
option(GAMRVIEWER "GamR tree processing - experimental" OFF)
option(GAMRPROC "GamR fast-timing processor" OFF)
option(GAMREFF "GamR HPGe efficiency fitting" ON)
option(GAMRCOULEX "GamR implementation of Winther-deBoer Coulex codes" OFF)
option(GAMRABBREVS "GamR abbreviations for command-line use" ON)
option(GAMRBATEMAN "GamR Bateman equation solver - requires BOOST" OFF)

option(gamr_WITH_TESTING "Build tests/examples" OFF)
option(gamr_NO_INSTALL "Skip installation process" OFF)

define_property(GLOBAL PROPERTY GAMR_LIBS
  BRIEF_DOCS "List of GamR libraries"
  FULL_DOCS "List of GamR libraries"
)
define_property(GLOBAL PROPERTY GAMR_LIBDIRS
  BRIEF_DOCS "List of GamR library directories"
  FULL_DOCS "List of GamR library directories"
)

if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  MESSAGE(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

include(GNUInstallDirs)

message(${CMAKE_INSTALL_BINDIR})
set(GAMR_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
set(GAMR_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR}/${GAMR_PROJ_VER})
set(GAMR_INSTALL_INCDIR ${CMAKE_INSTALL_INCLUDEDIR}/${GAMR_PROJ_VER})
set(GAMR_INSTALL_DATADIR ${CMAKE_INSTALL_DATADIR}/${GAMR_PROJ_VER})
set(GAMR_INSTALL_DOCDIR ${CMAKE_INSTALL_DOCDIR})

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${GAMR_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT COMPONENTS RIO Net)
if (NOT ROOT_FOUND)
  message(FATAL_ERROR "${BoldRed}Can not find CERN ROOT libraries. Check environment variable $ROOTSYS.${ColourReset}")
endif()

include(${ROOT_USE_FILE})

#boost
find_package(Boost)
if (NOT ${Boost_FOUND})
  set(GAMRBATEMAN OFF)
endif()

#doxygen
find_package(Doxygen)
if (NOT DOXYGEN_FOUND)
  message(FATAL_ERROR "${BoldRed}Doxygen is needed to build API documentation${ColourReset}")
endif()
set(doxy_main_page ${PROJECT_SOURCE_DIR}/docs/Doxymain.md)
set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/docs/Doxyfile.in)
set(DOXYGEN_OUT ${PROJECT_BINARY_DIR}/docs/Doxyfile)
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

add_custom_target(doc
  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  COMMENT "Generating API documentation with Doxygen"
  VERBATIM)

# GIT
find_package(Git)
if (GIT_FOUND)
  # Get the git revision
  execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-list --max-count=1 HEAD
    OUTPUT_VARIABLE GIT_REVISION
    ERROR_QUIET
    )
  if (NOT ${GIT_REVISION} STREQUAL "")
    string(STRIP ${GIT_REVISION} GIT_REVISION)
  endif()
  message(STATUS "Current git revision is ${GIT_REVISION}")
else()
  set(GIT_REVISION "unknown")
endif()

if (APPLE)
  set(LIB_SUFFIX "dylib")
  set(LIB_LOADALL_PRE "-Wl,-all_load")
  set(LIB_LOADALL_POST "")
else()
  set(LIB_SUFFIX "so")
  set(LIB_LOADALL_PRE "-Wl,--no-as-needed")
  set(LIB_LOADALL_POST "-Wl,--as-needed")
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/extern)
add_definitions("-DINI_MAX_LINE=2000")
add_subdirectory(${PROJECT_SOURCE_DIR}/src/lib)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/bin)
if (gamr_WITH_TESTING) 
  add_subdirectory(${PROJECT_SOURCE_DIR}/src/tests)
endif()

get_property(libs GLOBAL PROPERTY GAMR_LIBS)
get_property(libdirs GLOBAL PROPERTY GAMR_LIBDIRS)
#generate rootlogon -> this started breaking things and apparently wasn't necessary (?!?)
#set(GAMR_ROOTLOGON_LIBS "// Libraries")
#foreach (lib ${libs})
#  set(GAMR_ROOTLOGON_LIBS "${GAMR_ROOTLOGON_LIBS}\ngROOT->ProcessLine(\".L ${CMAKE_INSTALL_PREFIX}/${GAMR_INSTALL_LIBDIR}/lib${lib}.${LIB_SUFFIX}\");")  
#endforeach()

set(GAMR_ROOTLOGON_INCLUDES "// Includes")
set(GAMR_ROOTLOGON_INCLUDES "${GAMR_ROOTLOGON_INCLUDES}\ngROOT->ProcessLine(\".include ${CMAKE_INSTALL_PREFIX}/${GAMR_INSTALL_INCDIR}\");")

foreach (lib ${libdirs})
  file(GLOB_RECURSE inc RELATIVE "${PROJECT_SOURCE_DIR}/src/lib/" "${PROJECT_SOURCE_DIR}/src/lib/${lib}/*.hh")
  list(APPEND includes ${inc})
endforeach()

foreach(inc ${includes})
  set(GAMR_ROOTLOGON_INCLUDES "${GAMR_ROOTLOGON_INCLUDES}\ngROOT->ProcessLine(\"#include <${inc}>\");")
endforeach()

configure_file(${PROJECT_SOURCE_DIR}/gamrlogon.cc.in ${PROJECT_BINARY_DIR}/gamrlogon.cc @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/gamrlogon.cc DESTINATION ${GAMR_INSTALL_DATADIR})
install(FILES ${PROJECT_SOURCE_DIR}/gamrlogon_user.cc DESTINATION ${GAMR_INSTALL_DATADIR})

