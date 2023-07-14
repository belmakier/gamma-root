set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_viewer)
set_property(GLOBAL APPEND PROPERTY GAMR_LIBDIRS viewer)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)
include_directories(${PROJECT_BINARY_DIR}/src/lib)
include_directories(${PROJECT_SOURCE_DIR}/extern)

#generate root dictionary
configure_file(gamr_viewer_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_viewer_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_viewer Viewer.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_viewer_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_viewer_rdict SHARED Viewer.cc G__gamr_viewer)
target_include_directories(gamr_viewer_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_viewer_rdict ${ROOT_LIBRARIES} gamr_tree)
set_target_properties(gamr_viewer_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_viewer_rdict
  EXPORT gamr_viewer-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_viewer_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_viewer SHARED Viewer.cc)
target_link_libraries(gamr_viewer PUBLIC ${LIB_LOADALL_PRE} gamr_viewer_rdict ${LIB_LOADALL_POST})

#install
install(FILES Viewer.hh DESTINATION ${GAMR_INSTALL_INCDIR}/viewer)
install(TARGETS gamr_viewer DESTINATION ${GAMR_INSTALL_LIBDIR})

