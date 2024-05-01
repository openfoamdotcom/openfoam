set(_FILES
  meshDualiser.C
  polyDualMeshApp.C
)
add_executable(polyDualMesh ${_FILES})
target_compile_features(polyDualMesh PUBLIC cxx_std_11)
target_link_libraries(polyDualMesh PUBLIC dynamicMesh reconstruct genericPatchFields)
