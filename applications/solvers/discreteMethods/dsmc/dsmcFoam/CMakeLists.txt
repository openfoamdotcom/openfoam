set(_FILES
  dsmcFoam.C
)
add_executable(dsmcFoam ${_FILES})
target_compile_features(dsmcFoam PUBLIC cxx_std_11)
target_link_libraries(dsmcFoam PUBLIC finiteVolume)
