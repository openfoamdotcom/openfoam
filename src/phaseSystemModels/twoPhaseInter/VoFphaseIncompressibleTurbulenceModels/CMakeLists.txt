set(_FILES
  VoFphaseTurbulentTransportModels.C
)
add_library(VoFphaseTurbulentTransportModels ${_FILES})
target_compile_features(VoFphaseTurbulentTransportModels PUBLIC cxx_std_11)
target_compile_definitions(VoFphaseTurbulentTransportModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(VoFphaseTurbulentTransportModels PUBLIC
  .
)
install(TARGETS VoFphaseTurbulentTransportModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
