set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_coulex)
set_property(GLOBAL APPEND PROPERTY GAMR_LIBDIRS coulex)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)

set(CMAKE_Fortran_IMPLICIT_LINK_LIBRARIES gfortran quadmath m )

message("CMAKE FORTRAN FLAGS: " ${CMAKE_Fortran_FLAGS})
message("CMAKE FORTRAN IMPLICIT LINK DIRS: " ${CMAKE_Fortran_IMPLICIT_LINK_DIRECTORIES})
message("CMAKE FORTRAN IMPLICIT LINK LIBS: " ${CMAKE_Fortran_IMPLICIT_LINK_LIBRARIES})

configure_file(Eloss.cc.in Eloss.cc)
configure_file(Eloss.hh Eloss.hh COPYONLY)

#generate root dictionary
configure_file(gamr_coulex_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_coulex_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_coulex Coulex.hh CoulexCalculation.hh Eloss.hh WDBSubs.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_coulex_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_coulex_rdict SHARED Coulex.cc CoulexCalculation.cc ${CMAKE_CURRENT_BINARY_DIR}/Eloss.cc  WDBSubs.for G__gamr_coulex)
target_include_directories(gamr_coulex_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_coulex_rdict ${ROOT_LIBRARIES} gamr_utils gamr_toolkit gamr_angdist)
set_target_properties(gamr_coulex_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_coulex_rdict
  EXPORT gamr_coulex-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_coulex_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_coulex SHARED Coulex.cc CoulexCalculation.cc ${CMAKE_CURRENT_BINARY_DIR}/Eloss.cc  WDBSubs.for)
target_link_libraries(gamr_coulex PUBLIC ${LIB_LOADALL_PRE} gamr_coulex_rdict ${LIB_LOADALL_POST})

#install
install(FILES Coulex.hh CoulexCalculation.hh Eloss.hh WDBSubs.hh DESTINATION ${GAMR_INSTALL_INCDIR}/coulex)
install(TARGETS gamr_coulex DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES SCOEF.dat DESTINATION ${GAMR_INSTALL_DATADIR}/coulex)
