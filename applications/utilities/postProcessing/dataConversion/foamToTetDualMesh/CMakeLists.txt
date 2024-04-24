set(_FILES
  foamToTetDualMesh.C
)
add_executable(foamToTetDualMesh ${_FILES})
target_compile_features(foamToTetDualMesh PUBLIC cxx_std_11)
target_link_libraries(foamToTetDualMesh PUBLIC finiteVolume)
