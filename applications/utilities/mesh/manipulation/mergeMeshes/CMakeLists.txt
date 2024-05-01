set(_FILES
  mergePolyMesh.C
  mergeMeshes.C
)
add_executable(mergeMeshes ${_FILES})
target_compile_features(mergeMeshes PUBLIC cxx_std_11)
target_link_libraries(mergeMeshes PUBLIC dynamicMesh reconstruct)
target_include_directories(mergeMeshes PUBLIC
  .
)
