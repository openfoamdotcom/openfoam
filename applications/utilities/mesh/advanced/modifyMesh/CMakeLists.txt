set(_FILES
  cellSplitter.C
  modifyMesh.C
)
add_executable(modifyMesh ${_FILES})
target_compile_features(modifyMesh PUBLIC cxx_std_11)
target_link_libraries(modifyMesh PUBLIC dynamicMesh reconstruct)
target_include_directories(modifyMesh PUBLIC
  .
)
