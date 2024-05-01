set(_FILES
  subsetMesh.C
)
add_executable(subsetMesh ${_FILES})
target_compile_features(subsetMesh PUBLIC cxx_std_11)
target_link_libraries(subsetMesh PUBLIC dynamicMesh genericPatchFields reconstruct)
target_include_directories(subsetMesh PUBLIC
  .
)
