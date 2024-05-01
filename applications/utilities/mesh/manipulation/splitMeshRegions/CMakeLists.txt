set(_FILES
  splitMeshRegions.C
)
add_executable(splitMeshRegions ${_FILES})
target_compile_features(splitMeshRegions PUBLIC cxx_std_11)
target_link_libraries(splitMeshRegions PUBLIC dynamicMesh reconstruct genericPatchFields)
