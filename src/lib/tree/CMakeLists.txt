# EasyMode gamr/src/lib/tree/CMakeLists.txt
set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_tree)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)
include_directories(${PROJECT_SOURCE_DIR}/extern)

# Generate Linkdef and Typedef
execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/helpers/TreeDefnParser.py" "${PROJECT_SOURCE_DIR}/docs/md/tree/treetypes.md" "linkdef" OUTPUT_VARIABLE GAMR_TREE_LINKDEF)
execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/helpers/TreeDefnParser.py" "${PROJECT_SOURCE_DIR}/docs/md/tree/treetypes.md" "typedef" OUTPUT_VARIABLE GAMR_TREE_TYPEDEF)

# Configure Typedef File
configure_file(Tree.hh.in Tree.hh)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Tree.hh DESTINATION ${GAMR_INSTALL_INCDIR}/tree)

#generate root dictionary
configure_file(gamr_tree_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_tree_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_tree ExpDefn.hh Event.hh Detector.hh DetDefn.hh Reader.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_tree_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_tree_rdict SHARED ExpDefn.cc Event.cc Detector.cc DetDefn.cc Reader.cc G__gamr_tree)
target_include_directories(gamr_tree_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_tree_rdict ${ROOT_LIBRARIES} )
set_target_properties(gamr_tree_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_tree_rdict
  EXPORT gamr_tree-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_tree_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_tree SHARED ExpDefn.cc Event.cc Detector.cc DetDefn.cc Reader.cc)
target_link_libraries(gamr_tree PUBLIC ${LIB_LOADALL_PRE} gamr_tree_rdict ${LIB_LOADALL_POST})

#install
install(FILES ExpDefn.hh Event.hh Detector.hh DetDefn.hh Reader.hh DESTINATION ${GAMR_INSTALL_INCDIR}/tree)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Tree.hh DESTINATION ${GAMR_INSTALL_INCDIR}/tree)
install(TARGETS gamr_tree DESTINATION ${GAMR_INSTALL_LIBDIR})

file(GLOB template_implementation RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.tt")
foreach (f ${template_implementation})
  install(FILES ${f} DESTINATION ${GAMR_INSTALL_INCDIR}/tree)
endforeach()
