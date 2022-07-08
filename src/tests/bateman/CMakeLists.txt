# Configure filepaths
include_directories(${Boost_INCLUDE_DIRS})

configure_file(bateman.cc.in bateman.cc)

add_executable(gamrtest_bateman ${CMAKE_CURRENT_BINARY_DIR}/bateman.cc)
target_link_libraries(gamrtest_bateman gamrtest_main ${ROOT_LIBRARIES} gamr_bateman)

add_test(NAME libgamr_bateman COMMAND gamrtest_bateman)
