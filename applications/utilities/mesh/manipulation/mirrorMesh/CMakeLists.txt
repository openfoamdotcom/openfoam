set(_FILES
  mirrorFvMesh.C
  mirrorMesh.C
)
add_executable(mirrorMesh ${_FILES})
target_compile_features(mirrorMesh PUBLIC cxx_std_11)
target_link_libraries(mirrorMesh PUBLIC finiteVolume)
