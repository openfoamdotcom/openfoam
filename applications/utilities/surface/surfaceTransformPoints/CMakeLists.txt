set(_FILES
  surfaceTransformPoints.C
)
add_executable(surfaceTransformPoints ${_FILES})
target_compile_features(surfaceTransformPoints PUBLIC cxx_std_11)
target_link_libraries(surfaceTransformPoints PUBLIC finiteVolume)
