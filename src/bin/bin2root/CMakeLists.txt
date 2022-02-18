add_executable(bin2root bin2root.cc)
target_link_libraries(bin2root PUBLIC ${ROOT_LIBRARIES})
install(TARGETS bin2root DESTINATION ${GAMR_INSTALL_BINDIR})

