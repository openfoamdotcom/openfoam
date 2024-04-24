set(_FILES
  solidRegionDiffNo.C
  solidFoam.C
)
add_executable(solidFoam ${_FILES})
target_compile_features(solidFoam PUBLIC cxx_std_11)
target_link_libraries(solidFoam PUBLIC finiteVolume)
