set(_FILES
  hexBlock.C
  cfx4ToFoam.C
)
add_executable(cfx4ToFoam ${_FILES})
target_compile_features(cfx4ToFoam PUBLIC cxx_std_11)
target_link_libraries(cfx4ToFoam PUBLIC finiteVolume)
