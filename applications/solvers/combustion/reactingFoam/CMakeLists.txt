set(_FILES
  reactingFoam.C
)
add_executable(reactingFoam ${_FILES})
target_compile_features(reactingFoam PUBLIC cxx_std_11)
target_link_libraries(reactingFoam PUBLIC finiteVolume)
