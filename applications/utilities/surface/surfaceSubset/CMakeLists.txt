set(_FILES
  surfaceSubset.C
)
add_executable(surfaceSubset ${_FILES})
target_compile_features(surfaceSubset PUBLIC cxx_std_11)
target_link_libraries(surfaceSubset PUBLIC finiteVolume)
