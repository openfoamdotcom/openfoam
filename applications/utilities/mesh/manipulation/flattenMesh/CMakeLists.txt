set(_FILES
  flattenMesh.C
)
add_executable(flattenMesh ${_FILES})
target_compile_features(flattenMesh PUBLIC cxx_std_11)
target_link_libraries(flattenMesh PUBLIC dynamicMesh)
