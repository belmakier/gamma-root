# gamrdoc
configure_file(gamrdoc.in gamrdoc @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/gamrdoc DESTINATION ${GAMR_INSTALL_BINDIR})

# upgrade_gamr
configure_file(gamr_upgrade.in gamr_upgrade @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/gamr_upgrade DESTINATION ${GAMR_INSTALL_BINDIR})

