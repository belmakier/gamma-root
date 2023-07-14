set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_ornl)
set_property(GLOBAL APPEND PROPERTY GAMR_LIBDIRS ornl)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)

#generate root dictionary
configure_file(gamr_ornl_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_ornl_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_ornl OakRidge.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_ornl_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_ornl_rdict SHARED OakRidge.cc G__gamr_ornl)
target_include_directories(gamr_ornl_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_ornl_rdict ${ROOT_LIBRARIES})
set_target_properties(gamr_ornl_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_ornl_rdict
  EXPORT gamr_ornl-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_ornl_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_ornl SHARED OakRidge.cc)
target_link_libraries(gamr_ornl PUBLIC ${LIB_LOADALL_PRE} gamr_ornl_rdict ${LIB_LOADALL_POST})

#install
install(FILES OakRidge.hh DESTINATION ${GAMR_INSTALL_INCDIR}/ornl)
install(TARGETS gamr_ornl DESTINATION ${GAMR_INSTALL_LIBDIR})
