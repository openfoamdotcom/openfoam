set(_FILES
  moveDynamicMesh.C
)
add_executable(moveDynamicMesh ${_FILES})
target_compile_features(moveDynamicMesh PUBLIC cxx_std_11)
target_link_libraries(moveDynamicMesh PUBLIC dynamicFvMesh)
