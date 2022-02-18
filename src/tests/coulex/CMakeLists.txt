# Configure filepaths
configure_file(coulex.cc.in coulex.cc)

add_executable(gamrtest_coulex ${CMAKE_CURRENT_BINARY_DIR}/coulex.cc)
target_link_libraries(gamrtest_coulex gamrtest_main ${ROOT_LIBRARIES} gamr_coulex gamr_angdist)

add_test(NAME libgamr_coulex COMMAND gamrtest_coulex)
