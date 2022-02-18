# Configure filepaths
configure_file(pxi/tests.cc.in pxi/tests.cc)

add_executable(gamrtest_tree ${CMAKE_CURRENT_BINARY_DIR}/pxi/tests.cc)
target_link_libraries(gamrtest_tree gamrtest_main ${ROOT_LIBRARIES} gamr_tree TreePlayer)

add_test(NAME libgamr_tree COMMAND gamrtest_tree)
