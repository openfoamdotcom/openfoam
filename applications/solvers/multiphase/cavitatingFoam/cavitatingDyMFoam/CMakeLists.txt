set(_FILES
  cavitatingDyMFoam.C
)
add_executable(cavitatingDyMFoam ${_FILES})
target_compile_features(cavitatingDyMFoam PUBLIC cxx_std_11)
target_link_libraries(cavitatingDyMFoam PUBLIC finiteVolume)
