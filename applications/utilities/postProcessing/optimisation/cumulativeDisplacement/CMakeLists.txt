set(_FILES
  cumulativeDisplacement.C
)
add_executable(cumulativeDisplacement ${_FILES})
target_compile_features(cumulativeDisplacement PUBLIC cxx_std_11)
target_link_libraries(cumulativeDisplacement PUBLIC dynamicFvMesh dynamicMesh finiteVolume)
