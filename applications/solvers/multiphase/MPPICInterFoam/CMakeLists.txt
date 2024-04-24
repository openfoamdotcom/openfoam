set(_FILES
  MPPICInterFoam.C
)
add_executable(MPPICInterFoam ${_FILES})
target_compile_features(MPPICInterFoam PUBLIC cxx_std_11)
target_link_libraries(MPPICInterFoam PUBLIC finiteVolume)
