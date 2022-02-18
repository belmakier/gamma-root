include_directories(${PROJECT_SOURCE_DIR}/src/lib)

add_executable(ban2root ban2root.cc)
target_link_libraries(ban2root ${ROOT_LIBRARIES} gamr_ornl)
install(TARGETS ban2root DESTINATION ${GAMR_INSTALL_BINDIR})
