add_executable(root2ban root2ban.cc)

target_link_libraries(root2ban ${ROOT_LIBRARIES} gamr_ornl)

install(TARGETS root2ban DESTINATION ${GAMR_INSTALL_BINDIR})
