set_property(GLOBAL APPEND PROPERTY GAMR_LIBS gamr_angdist)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)

#generate root dictionary
configure_file(gamr_angdist_Linkdef.h.in ${CMAKE_CURRENT_BINARY_DIR}/gamr_angdist_Linkdef.h @ONLY)
root_generate_dictionary(G__gamr_angdist PopulationParameter.hh WignerD.hh AngDist.hh AngCorr.hh TDPAD.hh GaussianDistr.hh StatTensor.hh SolidAttenuation.hh LINKDEF ${CMAKE_CURRENT_BINARY_DIR}/gamr_angdist_Linkdef.h OPTIONS "-I${CMAKE_CURRENT_SOURCE_DIR}")
add_library(gamr_angdist_rdict SHARED PopulationParameter.cc WignerD.cc AngDist.cc AngCorr.cc TDPAD.cc GaussianDistr.cc StatTensor.cc SolidAttenuation.cc G__gamr_angdist)
target_include_directories(gamr_angdist_rdict PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamr_angdist_rdict ${ROOT_LIBRARIES} gamr_nucleus gamr_spect gamr_utils MathMore)
set_target_properties(gamr_angdist_rdict PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS gamr_angdist_rdict
  EXPORT gamr_angdist-config
  LIBRARY DESTINATION ${GAMR_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${GAMR_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgamr_angdist_rdict.pcm
  DESTINATION ${GAMR_INSTALL_LIBDIR})

#build actual library
add_library(gamr_angdist SHARED PopulationParameter.cc WignerD.cc AngDist.cc AngCorr.cc TDPAD.cc GaussianDistr.cc StatTensor.cc SolidAttenuation.cc)
target_link_libraries(gamr_angdist PUBLIC ${LIB_LOADALL_PRE} gamr_angdist_rdict ${LIB_LOADALL_POST})

#install
install(FILES PopulationParameter.hh WignerD.hh AngDist.hh AngCorr.hh TDPAD.hh GaussianDistr.hh StatTensor.hh SolidAttenuation.hh DESTINATION ${GAMR_INSTALL_INCDIR}/angdist)
install(TARGETS gamr_angdist DESTINATION ${GAMR_INSTALL_LIBDIR})
