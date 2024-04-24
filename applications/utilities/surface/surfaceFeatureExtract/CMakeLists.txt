set(_FILES
  surfaceFeatureExtract.C
)
add_executable(surfaceFeatureExtract ${_FILES})
target_compile_features(surfaceFeatureExtract PUBLIC cxx_std_11)
target_link_libraries(surfaceFeatureExtract PUBLIC finiteVolume)
