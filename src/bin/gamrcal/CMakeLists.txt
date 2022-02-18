include_directories(${PROJECT_SOURCE_DIR}/extern)
include_directories(${PROJECT_SOURCE_DIR}/src/lib)
include_directories(${PROJECT_BINARY_DIR}/src/lib)

add_executable(gamrcal gamrcal.cc Gain.cc)
target_link_libraries(gamrcal PUBLIC ${ROOT_LIBRARIES} Spectrum)

install(TARGETS gamrcal DESTINATION ${GAMR_INSTALL_BINDIR})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/caltargets.root DESTINATION ${GAMR_INSTALL_DATADIR})
