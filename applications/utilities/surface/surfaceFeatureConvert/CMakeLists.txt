set(_FILES
  surfaceFeatureConvert.C
)
add_executable(surfaceFeatureConvert ${_FILES})
target_compile_features(surfaceFeatureConvert PUBLIC cxx_std_11)
target_link_libraries(surfaceFeatureConvert PUBLIC meshTools)
target_include_directories(surfaceFeatureConvert PUBLIC
  .
)
