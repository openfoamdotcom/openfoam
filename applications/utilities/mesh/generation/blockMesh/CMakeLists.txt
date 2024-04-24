set(_FILES
  blockMesh.C
)
add_executable(blockMesh ${_FILES})
target_compile_features(blockMesh PUBLIC cxx_std_11)
target_link_libraries(blockMesh PUBLIC finiteVolume)
