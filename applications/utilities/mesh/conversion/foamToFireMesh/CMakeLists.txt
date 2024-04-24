set(_FILES
  foamToFireMesh.C
)
add_executable(foamToFireMesh ${_FILES})
target_compile_features(foamToFireMesh PUBLIC cxx_std_11)
target_link_libraries(foamToFireMesh PUBLIC finiteVolume)
