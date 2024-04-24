set(_FILES
  surfaceSplitByTopology.C
)
add_executable(surfaceSplitByTopology ${_FILES})
target_compile_features(surfaceSplitByTopology PUBLIC cxx_std_11)
target_link_libraries(surfaceSplitByTopology PUBLIC finiteVolume)
