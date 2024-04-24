set(_FILES
  fluid/compressibleCourantNo.C
  solid/solidRegionDiffNo.C
  chtMultiRegionFoam.C
)
add_executable(chtMultiRegionFoam ${_FILES})
target_compile_features(chtMultiRegionFoam PUBLIC cxx_std_11)
target_link_libraries(chtMultiRegionFoam PUBLIC finiteVolume)
