set(_FILES
  foamyHexMeshBackgroundMesh.C
)
add_executable(foamyHexMeshBackgroundMesh ${_FILES})
target_compile_features(foamyHexMeshBackgroundMesh PUBLIC cxx_std_11)
target_link_libraries(foamyHexMeshBackgroundMesh PUBLIC conformalVoronoiMesh decompose dynamicMesh finiteVolume sampling)
if (SCOTCH_FOUND)
  target_link_libraries(foamyHexMeshBackgroundMesh PUBLIC scotchDecomp)
endif()
