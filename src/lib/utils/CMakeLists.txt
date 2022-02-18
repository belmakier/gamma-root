set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_utils)

#make root library
configure_file(gamr_utils_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_utils_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_utils REPL.hh Utilities.hh Tuples.hh RTTI.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_utils_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_utils_rdict SHARED REPL.cc Utilities.cc G__gamr_utils)
target_include_directories(gamr_utils_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_utils_rdict ${ROOT_LIBRARIES})
set_target_properties(gamr_utils_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_utils_rdict
  EXPORT gamr_utils-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_utils_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})


#build actual library
add_library(gamr_utils SHARED REPL.cc Utilities.cc)
target_link_libraries(gamr_utils PUBLIC ${LIB_LOADALL_PRE} gamr_utils_rdict ${LIB_LOADALL_POST})

#install
install(FILES REPL.hh Utilities.hh Tuples.hh RTTI.hh DESTINATION ${GAMR_INSTALL_INCDIR}/utils)

install(TARGETS gamr_utils DESTINATION ${GAMR_INSTALL_LIBDIR})
