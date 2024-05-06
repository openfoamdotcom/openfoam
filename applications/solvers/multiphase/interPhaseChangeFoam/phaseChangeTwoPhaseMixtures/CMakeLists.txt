set(_FILES
  phaseChangeTwoPhaseMixture/phaseChangeTwoPhaseMixture.C
  phaseChangeTwoPhaseMixture/phaseChangeTwoPhaseMixtureNew.C
  Kunz/Kunz.C
  Merkle/Merkle.C
  SchnerrSauer/SchnerrSauer.C
)
add_library(phaseChangeTwoPhaseMixtures ${_FILES})
target_compile_features(phaseChangeTwoPhaseMixtures PUBLIC cxx_std_11)
set_property(TARGET phaseChangeTwoPhaseMixtures PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(phaseChangeTwoPhaseMixtures PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(phaseChangeTwoPhaseMixtures PUBLIC incompressibleTransportModels twoPhaseProperties)
target_include_directories(phaseChangeTwoPhaseMixtures PUBLIC
  .
)
install(TARGETS phaseChangeTwoPhaseMixtures DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
