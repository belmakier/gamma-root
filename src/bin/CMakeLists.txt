add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/linux)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bin2root)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gamrcal)

if (GAMRTREE)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/root2gamr)
endif()

if (GAMRORNL)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ban2root)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/his2root)
endif()
if (GAMRSORT)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gamrsort)
endif()



