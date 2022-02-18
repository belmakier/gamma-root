# DEPENDENCIES CMAKE FILE

## Git Submodules

if(NOT GIT_FOUND)
  message(FATAL_ERROR "Git is needed for dependency submodules.")
endif()

### INIH is a INI Parser
execute_process(COMMAND
  ${GIT_EXECUTABLE} submodule update --init -- inih
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
add_library(extern_inih INTERFACE)
target_include_directories(extern_inih INTERFACE "inih")
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/inih/INIReader.h DESTINATION ${GAMR_INSTALL_INCDIR}/inih)

### ARGS argument parser
execute_process(COMMAND
  ${GIT_EXECUTABLE} submodule update --init -- args
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
add_library(extern_args INTERFACE)
target_include_directories(extern_args INTERFACE "args")

### Doctest unit testing
execute_process(COMMAND
  ${GIT_EXECUTABLE} submodule update --init -- doctest
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
add_library(extern_doctest INTERFACE)
target_include_directories(extern_doctest INTERFACE "doctest")

