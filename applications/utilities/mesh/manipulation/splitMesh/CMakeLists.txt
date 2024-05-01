set(_FILES
  regionSide.C
  splitMesh.C
)
add_executable(splitMesh ${_FILES})
target_compile_features(splitMesh PUBLIC cxx_std_11)
target_link_libraries(splitMesh PUBLIC dynamicMesh reconstruct)
target_include_directories(splitMesh PUBLIC
  .
)
