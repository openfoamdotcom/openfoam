set(_FILES
  surfaceBooleanFeatures.C
)
add_executable(surfaceBooleanFeatures ${_FILES})
target_compile_features(surfaceBooleanFeatures PUBLIC cxx_std_11)
target_link_libraries(surfaceBooleanFeatures PUBLIC finiteVolume)
