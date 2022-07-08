include_directories(${PROJECT_SOURCE_DIR}/src/lib)
include_directories(${PROJECT_BINARY_DIR}/src/lib)
include_directories(${PROJECT_SOURCE_DIR}/extern)

add_library(gamrtest_main SHARED main.cc)
target_link_libraries(gamrtest_main extern_doctest)

# UNITS
add_subdirectory(tree)
add_subdirectory(coulex)
if (${Boost_FOUND})
  add_subdirectory(bateman)
endif()
