set(_FILES
  compressibleTurbulenceModel.C
  turbulentFluidThermoModels/turbulentFluidThermoModels.C
)
add_library(compressibleTurbulenceModels ${_FILES})
target_compile_features(compressibleTurbulenceModels PUBLIC cxx_std_11)
target_compile_definitions(compressibleTurbulenceModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(compressibleTurbulenceModels PUBLIC radiationModels solidThermo solidSpecie turbulenceModels specie)
target_include_directories(compressibleTurbulenceModels PUBLIC
  .
  RAS/buoyantKEpsilon
  turbulentFluidThermoModels
  CompressibleTurbulenceModel
  ThermalDiffusivity
  EddyDiffusivity
  ${OPENFOAM_SRC_DIR}/TurbulenceModels/phaseCompressible/RAS/continuousGasKEpsilon
  ${OPENFOAM_SRC_DIR}/TurbulenceModels/phaseCompressible/RAS/LaheyKEpsilon
  ${OPENFOAM_SRC_DIR}/TurbulenceModels/phaseCompressible/RAS/kOmegaSSTSato
  ${OPENFOAM_SRC_DIR}/TurbulenceModels/phaseCompressible/RAS/mixtureKEpsilon
  ${OPENFOAM_SRC_DIR}/TurbulenceModels/phaseCompressible/PhaseCompressibleTurbulenceModel
  ${OPENFOAM_SRC_DIR}/TurbulenceModels/phaseCompressible/LES/continuousGasKEqn
  ${OPENFOAM_SRC_DIR}/TurbulenceModels/phaseCompressible/LES/SmagorinskyZhang
  ${OPENFOAM_SRC_DIR}/TurbulenceModels/phaseCompressible/LES/Niceno
)
install(TARGETS compressibleTurbulenceModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
