include_directories(${PROJECT_SOURCE_DIR}/extern)
include_directories(${PROJECT_SOURCE_DIR}/src/lib)
include_directories(${PROJECT_BINARY_DIR}/src/lib)

add_executable(gamrsort gamrsort.cc)
target_link_libraries(gamrsort PUBLIC gamr_utils gamr_sort gamr_tree gamr_nucleus gamr_toolkit TreePlayer tbb)
install(TARGETS gamrsort DESTINATION ${GAMR_INSTALL_BINDIR})

