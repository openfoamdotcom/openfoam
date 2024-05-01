set(_FILES
  stitchMesh.C
)
add_executable(stitchMesh ${_FILES})
target_compile_features(stitchMesh PUBLIC cxx_std_11)
target_link_libraries(stitchMesh PUBLIC dynamicMesh genericPatchFields)
target_include_directories(stitchMesh PUBLIC
  .
)
