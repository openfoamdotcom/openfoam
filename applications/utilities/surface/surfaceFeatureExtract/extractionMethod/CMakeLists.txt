set(_FILES
  ./surfaceFeaturesExtraction.C
  ./extractFromFile.C
  ./extractFromNone.C
  ./extractFromSurface.C
)
add_library(surfaceFeatureExtract ${_FILES})
target_compile_features(surfaceFeatureExtract PUBLIC cxx_std_11)
target_compile_definitions(surfaceFeatureExtract PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(surfaceFeatureExtract PUBLIC meshTools)
target_include_directories(surfaceFeatureExtract PUBLIC
  .
)
install(TARGETS surfaceFeatureExtract DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
