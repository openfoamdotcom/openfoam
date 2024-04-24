set(_FILES
  rotateMesh.C
)
add_executable(rotateMesh ${_FILES})
target_compile_features(rotateMesh PUBLIC cxx_std_11)
target_link_libraries(rotateMesh PUBLIC finiteVolume)
