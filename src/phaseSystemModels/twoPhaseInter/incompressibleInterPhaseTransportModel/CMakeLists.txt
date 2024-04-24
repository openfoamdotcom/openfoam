set(_FILES
  incompressibleInterPhaseTransportModels.C
)
add_library(incompressibleInterPhaseTransportModels ${_FILES})
target_compile_features(incompressibleInterPhaseTransportModels PUBLIC cxx_std_11)
target_compile_definitions(incompressibleInterPhaseTransportModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(incompressibleInterPhaseTransportModels PUBLIC
  .
)
install(TARGETS incompressibleInterPhaseTransportModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
