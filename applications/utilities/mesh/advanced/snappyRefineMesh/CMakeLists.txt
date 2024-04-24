set(_FILES
  snappyRefineMesh.C
)
add_executable(snappyRefineMesh ${_FILES})
target_compile_features(snappyRefineMesh PUBLIC cxx_std_11)
target_link_libraries(snappyRefineMesh PUBLIC finiteVolume)
