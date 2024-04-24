set(_FILES
  gen6DoF.C
)
add_executable(gen6DoF ${_FILES})
target_compile_features(gen6DoF PUBLIC cxx_std_11)
target_link_libraries(gen6DoF PUBLIC finiteVolume)
