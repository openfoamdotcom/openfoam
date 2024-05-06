set(_FILES
  ./surfaceFeaturesExtraction.C
  ./extractFromFile.C
  ./extractFromNone.C
  ./extractFromSurface.C
)
add_library(surfaceFeatureExtractLib ${_FILES})
target_compile_features(surfaceFeatureExtractLib PUBLIC cxx_std_11)
set_property(TARGET surfaceFeatureExtractLib PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(surfaceFeatureExtractLib PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(surfaceFeatureExtractLib PUBLIC meshTools)
set_target_properties(surfaceFeatureExtractLib PROPERTIES OUTPUT_NAME surfaceFeatureExtract)
target_include_directories(surfaceFeatureExtractLib PUBLIC
  .
)
install(TARGETS surfaceFeatureExtractLib DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
