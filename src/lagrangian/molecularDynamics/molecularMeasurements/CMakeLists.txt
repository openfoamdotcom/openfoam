set(_FILES
  distribution/distribution.C
)
add_library(molecularMeasurements ${_FILES})
target_compile_features(molecularMeasurements PUBLIC cxx_std_11)
target_compile_definitions(molecularMeasurements PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(molecularMeasurements PUBLIC OpenFOAM)
target_include_directories(molecularMeasurements PUBLIC
  bufferedAccumulator
  correlationFunction
  distribution
)
install(TARGETS molecularMeasurements DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
