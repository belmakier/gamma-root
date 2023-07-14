set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_bateman)
set_property(GLOBAL APPEND PROPERTY GAMR_LIBDIRS bateman)

include_directories(${PROJECT_SOURCE_DIR}/src/lib ${Boost_INCLUDE_DIRS})

#generate root dictionary
configure_file(gamr_bateman_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_bateman_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_bateman Nucleus.hh Scheme.hh Solver.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_bateman_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_bateman_rdict SHARED Nucleus.cc Scheme.cc Solver.cc G__gamr_bateman)
target_include_directories(gamr_bateman_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_bateman_rdict ${ROOT_LIBRARIES} )
set_target_properties(gamr_bateman_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_bateman_rdict
  EXPORT gamr_bateman-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_bateman_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_bateman SHARED Nucleus.cc Scheme.cc Solver.cc)
target_link_libraries(gamr_bateman PUBLIC ${LIB_LOADALL_PRE} gamr_bateman_rdict ${LIB_LOADALL_POST})

#install
install(FILES Nucleus.hh Scheme.hh Solver.hh DESTINATION ${GAMR_INSTALL_INCDIR}/bateman)
install(TARGETS gamr_bateman DESTINATION ${GAMR_INSTALL_LIBDIR})
