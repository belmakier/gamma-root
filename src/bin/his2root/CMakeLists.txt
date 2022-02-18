add_executable(his2root his2root.cc)
target_link_libraries(his2root PUBLIC ${ROOT_LIBRARIES})
install(TARGETS his2root DESTINATION ${GAMR_INSTALL_BINDIR})

