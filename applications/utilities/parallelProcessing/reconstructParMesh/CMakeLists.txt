set(_FILES
  reconstructParMesh.C
)
add_executable(reconstructParMesh ${_FILES})
target_compile_features(reconstructParMesh PUBLIC cxx_std_11)
target_link_libraries(reconstructParMesh PUBLIC dynamicMesh)
