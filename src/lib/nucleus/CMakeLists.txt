set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_nucleus)
set_property(GLOBAL APPEND PROPERTY GAMR_LIBDIRS nucleus)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)

#generate root dictionary
configure_file(gamr_nucleus_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_nucleus_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_nucleus Photon.hh State.hh Transition.hh LevelSchemeFitter.hh LevelSchemeDraw.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_nucleus_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_nucleus_rdict SHARED Photon.cc State.cc Transition.cc LevelSchemeFitter.cc LevelSchemeDraw.cc G__gamr_nucleus)
target_include_directories(gamr_nucleus_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_nucleus_rdict ${ROOT_LIBRARIES} gamr_utils gamr_toolkit Minuit)
set_target_properties(gamr_nucleus_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_nucleus_rdict
  EXPORT gamr_nucleus-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_nucleus_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_nucleus SHARED Photon.cc State.cc Transition.cc LevelSchemeFitter.cc LevelSchemeDraw.cc)
target_link_libraries(gamr_nucleus PUBLIC ${LIB_LOADALL_PRE} gamr_nucleus_rdict ${LIB_LOADALL_POST})

#install
install(FILES Photon.hh State.hh Transition.hh LevelSchemeFitter.hh LevelSchemeDraw.hh DESTINATION ${GAMR_INSTALL_INCDIR}/nucleus)
install(TARGETS gamr_nucleus DESTINATION ${GAMR_INSTALL_LIBDIR})
