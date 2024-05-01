set(_FILES
  extrudeToRegionMesh.C
)
add_executable(extrudeToRegionMesh ${_FILES})
target_compile_features(extrudeToRegionMesh PUBLIC cxx_std_11)
target_link_libraries(extrudeToRegionMesh PUBLIC dynamicMesh extrudeModel reconstruct)
