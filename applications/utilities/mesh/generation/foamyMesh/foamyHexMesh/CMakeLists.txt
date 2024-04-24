set(_FILES
  foamyHexMesh.C
)
add_executable(foamyHexMesh ${_FILES})
target_compile_features(foamyHexMesh PUBLIC cxx_std_11)
target_link_libraries(foamyHexMesh PUBLIC finiteVolume)
