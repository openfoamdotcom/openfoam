set(_FILES
  moveEngineMesh.C
)
add_executable(moveEngineMesh ${_FILES})
target_compile_features(moveEngineMesh PUBLIC cxx_std_11)
target_link_libraries(moveEngineMesh PUBLIC finiteVolume)
