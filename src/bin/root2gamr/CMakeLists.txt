include_directories(${PROJECT_SOURCE_DIR}/src/lib)
include_directories(${PROJECT_BINARY_DIR}/src/lib)
include_directories(${PROJECT_SOURCE_DIR}/extern)

# Generate the flags and process from the documentation
execute_process(COMMAND "${PROJECT_SOURCE_DIR}/src/lib/tree/helpers/TreeDefnParser.py" "${PROJECT_SOURCE_DIR}/docs/md/tree/treetypes.md" "root2gamr_args" OUTPUT_VARIABLE GAMR_TREE_ROOT2GAMR_ARGS)
execute_process(COMMAND "${PROJECT_SOURCE_DIR}/src/lib/tree/helpers/TreeDefnParser.py" "${PROJECT_SOURCE_DIR}/docs/md/tree/treetypes.md" "root2gamr_process" OUTPUT_VARIABLE GAMR_TREE_ROOT2GAMR_PROCESS)

# Configure the root2gamr binary
configure_file(root2gamr.cc.in root2gamr.cc)

add_executable(root2gamr ${CMAKE_CURRENT_BINARY_DIR}/root2gamr.cc)
target_link_libraries(root2gamr PUBLIC gamr_tree)
install(TARGETS root2gamr DESTINATION ${GAMR_INSTALL_BINDIR})


