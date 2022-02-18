set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_processor)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)

#generate root dictionary
configure_file(gamr_processor_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_processor_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_processor TimeWalk.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_processor_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_processor_rdict SHARED TimeWalk.cc G__gamr_processor)
target_include_directories(gamr_processor_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_processor_rdict ${ROOT_LIBRARIES} gamr_nucleus gamr_toolkit Minuit)
set_target_properties(gamr_processor_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_processor_rdict
  EXPORT gamr_processor-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_processor_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_processor SHARED TimeWalk.cc)
target_link_libraries(gamr_processor PUBLIC ${LIB_LOADALL_PRE} gamr_processor_rdict ${LIB_LOADALL_POST})

#install
install(FILES TimeWalk.hh DESTINATION ${GAMR_INSTALL_INCDIR}/processor)
install(TARGETS gamr_processor DESTINATION ${GAMR_INSTALL_LIBDIR})

