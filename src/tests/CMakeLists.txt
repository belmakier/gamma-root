include_directories(${PROJECT_SOURCE_DIR}/src/lib)
include_directories(${PROJECT_BINARY_DIR}/src/lib)
include_directories(${PROJECT_SOURCE_DIR}/extern)

add_library(gamrtest_main SHARED main.cc)
target_link_libraries(gamrtest_main extern_doctest)

# UNITS
if (GAMRTREE)
  add_subdirectory(tree)
endif()
if (GAMRCOULEX)
  add_subdirectory(coulex)
endif()
if (GAMRBATEMAN)
  add_subdirectory(bateman)
endif()
