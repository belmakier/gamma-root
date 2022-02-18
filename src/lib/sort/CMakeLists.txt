set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_sort)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)

#generate root dictionary
configure_file(gamr_sort_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_sort_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_sort Sorter.hh GatedTimeDifference.hh TimeDifference.hh CoincidenceMatrixPair.hh Matrix.hh TimeDifferencePairs.hh TimeWalkCal.hh CoincidenceCubeDiff.hh CoincidenceMatrix.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_sort_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_sort_rdict SHARED Sorter.cc G__gamr_sort)
target_include_directories(gamr_sort_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_sort_rdict ${ROOT_LIBRARIES} gamr_toolkit gamr_nucleus)
set_target_properties(gamr_sort_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_sort_rdict
  EXPORT gamr_sort-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_sort_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_sort SHARED Sorter.cc)
target_link_libraries(gamr_sort PUBLIC ${LIB_LOADALL_PRE} gamr_sort_rdict ${LIB_LOADALL_POST})

#install
install(FILES Sorter.hh GatedTimeDifference.hh TimeDifference.hh CoincidenceMatrixPair.hh Matrix.hh TimeDifferencePairs.hh TimeWalkCal.hh CoincidenceCubeDiff.hh CoincidenceMatrix.hh DESTINATION ${GAMR_INSTALL_INCDIR}/sort)
install(TARGETS gamr_sort DESTINATION ${GAMR_INSTALL_LIBDIR})

