set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_spect)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)

configure_file(FitGuesses.hh FitGuesses.hh COPYONLY)
configure_file(FitGuesses.cc.in FitGuesses.cc)

message("${CMAKE_CURRENT_SOURCE_DIR}")

#generate root dictionary
configure_file(gamr_spect_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_spect_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_spect IO.hh Cut.hh Integral.hh Transform.hh Fit.hh FitGuesses.hh Display.hh FFT.hh BackSub.hh Calibrate.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_spect_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_spect_rdict SHARED IO.cc Cut.cc Integral.cc Transform.cc Fit.cc ${PROJECT_BINARY_DIR}/src/lib/spect/FitGuesses.cc Display.cc FFT.cc BackSub.cc Calibrate.cc G__gamr_spect)
target_include_directories(gamr_spect_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_spect_rdict ${ROOT_LIBRARIES} gamr_nucleus gamr_utils Spectrum)
set_target_properties(gamr_spect_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_spect_rdict
  EXPORT gamr_spect-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_spect_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_spect SHARED IO.cc Cut.cc Integral.cc Transform.cc Fit.cc ${PROJECT_BINARY_DIR}/src/lib/spect/FitGuesses.cc Display.cc FFT.cc BackSub.cc Calibrate.cc)
target_link_libraries(gamr_spect PUBLIC ${LIB_LOADALL_PRE} gamr_spect_rdict ${LIB_LOADALL_POST} Spectrum)

#install
install(FILES IO.hh Cut.hh Integral.hh Transform.hh Fit.hh FitGuesses.hh Display.hh FFT.hh BackSub.hh Calibrate.hh DESTINATION ${GAMR_INSTALL_INCDIR}/spect)
install(TARGETS gamr_spect DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES FitGuesses.dat DESTINATION ${GAMR_INSTALL_DATADIR})

