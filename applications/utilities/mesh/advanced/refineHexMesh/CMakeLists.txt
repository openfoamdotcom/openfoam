set(_FILES
  refineHexMesh.C
)
add_executable(refineHexMesh ${_FILES})
target_compile_features(refineHexMesh PUBLIC cxx_std_11)
target_link_libraries(refineHexMesh PUBLIC finiteVolume)
