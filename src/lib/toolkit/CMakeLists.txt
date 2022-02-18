set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_toolkit)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)

#generate root dictionary
configure_file(gamr_toolkit_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_toolkit_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_toolkit MonteCarlo.hh Gate.hh Peak.hh Misc.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_toolkit_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_toolkit_rdict SHARED MonteCarlo.cc Gate.cc Peak.cc Misc.cc G__gamr_toolkit)
target_include_directories(gamr_toolkit_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_toolkit_rdict ${ROOT_LIBRARIES} gamr_utils m Mathmore)
set_target_properties(gamr_toolkit_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_toolkit_rdict
  EXPORT gamr_toolkit-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_toolkit_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_toolkit SHARED MonteCarlo.cc Gate.cc Peak.cc Misc.cc)
target_link_libraries(gamr_toolkit PUBLIC ${LIB_LOADALL_PRE} gamr_toolkit_rdict ${LIB_LOADALL_POST} m MathMore)

#install
install(FILES MonteCarlo.hh Gate.hh Peak.hh Misc.hh DESTINATION ${GAMR_INSTALL_INCDIR}/toolkit)
install(TARGETS gamr_toolkit DESTINATION ${GAMR_INSTALL_LIBDIR})
