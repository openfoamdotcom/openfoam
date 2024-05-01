set(_FILES
  extrudedMesh/extrudedMesh.C
  extrudeMesh.C
)
add_executable(extrudeMesh ${_FILES})
target_compile_features(extrudeMesh PUBLIC cxx_std_11)
target_link_libraries(extrudeMesh PUBLIC dynamicMesh extrudeModel reconstruct)
