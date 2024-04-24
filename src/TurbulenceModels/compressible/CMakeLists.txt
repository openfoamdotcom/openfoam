set(_FILES
  compressibleTurbulenceModel.C
  turbulentFluidThermoModels/turbulentFluidThermoModels.C
)
add_library(compressibleTurbulenceModels ${_FILES})
target_compile_features(compressibleTurbulenceModels PUBLIC cxx_std_11)
target_compile_definitions(compressibleTurbulenceModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(compressibleTurbulenceModels PUBLIC
  .
  RAS/buoyantKEpsilon
  turbulentFluidThermoModels
  CompressibleTurbulenceModel
  ThermalDiffusivity
  EddyDiffusivity
)
install(TARGETS compressibleTurbulenceModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
