set(_FILES
  snappyHexMesh.C
)
add_executable(snappyHexMesh ${_FILES})
target_compile_features(snappyHexMesh PUBLIC cxx_std_11)
target_link_libraries(snappyHexMesh PUBLIC kahipDecomp metisDecomp ptscotchDecomp scotchDecomp decompose reconstruct snappyHexMeshLib)
