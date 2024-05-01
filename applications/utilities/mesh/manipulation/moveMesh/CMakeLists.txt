set(_FILES
  moveMesh.C
)
add_executable(moveMesh ${_FILES})
target_compile_features(moveMesh PUBLIC cxx_std_11)
target_link_libraries(moveMesh PUBLIC dynamicMesh)
target_include_directories(moveMesh PUBLIC
  .
)
