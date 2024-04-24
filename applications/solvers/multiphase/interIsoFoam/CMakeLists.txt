set(_FILES
  interIsoFoam.C
)
add_executable(interIsoFoam ${_FILES})
target_compile_features(interIsoFoam PUBLIC cxx_std_11)
target_link_libraries(interIsoFoam PUBLIC finiteVolume)
