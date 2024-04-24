set(_FILES
  overLaplacianDyMFoam.C
)
add_executable(overLaplacianDyMFoam ${_FILES})
target_compile_features(overLaplacianDyMFoam PUBLIC cxx_std_11)
target_link_libraries(overLaplacianDyMFoam PUBLIC finiteVolume)
