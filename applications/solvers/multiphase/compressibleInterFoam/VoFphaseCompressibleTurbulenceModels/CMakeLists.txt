set(_FILES
  VoFphaseCompressibleTurbulenceModels.C
  compressibleInterPhaseTransportModel.C
)
add_library(VoFphaseCompressibleTurbulenceModels ${_FILES})
target_compile_features(VoFphaseCompressibleTurbulenceModels PUBLIC cxx_std_11)
set_property(TARGET VoFphaseCompressibleTurbulenceModels PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(VoFphaseCompressibleTurbulenceModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(VoFphaseCompressibleTurbulenceModels PUBLIC incompressibleTransportModels thermoTools twoPhaseMixtureThermo)
target_include_directories(VoFphaseCompressibleTurbulenceModels PUBLIC
  .
)
install(TARGETS VoFphaseCompressibleTurbulenceModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
