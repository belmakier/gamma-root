set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_efficiency)
set_property(GLOBAL APPEND PROPERTY GAMR_LIBDIRS efficiency)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)

#generate root dictionary
configure_file(gamr_efficiency_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_efficiency_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_efficiency Efficiency.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_efficiency_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_efficiency_rdict SHARED Efficiency.cc G__gamr_efficiency)
target_include_directories(gamr_efficiency_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_efficiency_rdict ${ROOT_LIBRARIES} gamr_nucleus gamr_toolkit Minuit)
set_target_properties(gamr_efficiency_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_efficiency_rdict
  EXPORT gamr_efficiency-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_efficiency_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_efficiency SHARED Efficiency.cc)
target_link_libraries(gamr_efficiency PUBLIC ${LIB_LOADALL_PRE} gamr_efficiency_rdict ${LIB_LOADALL_POST})

#install
install(FILES Efficiency.hh DESTINATION ${GAMR_INSTALL_INCDIR}/efficiency)
install(TARGETS gamr_efficiency DESTINATION ${GAMR_INSTALL_LIBDIR})
