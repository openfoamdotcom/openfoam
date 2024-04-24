set(_FILES
  fireFoam.C
)
add_executable(fireFoam ${_FILES})
target_compile_features(fireFoam PUBLIC cxx_std_11)
target_link_libraries(fireFoam PUBLIC finiteVolume)
