set(_FILES
  extrudedTriangleCellShape.C
  extrudedQuadCellShape.C
  create3DCellShape.C
)
add_executable(fluentMeshToFoam ${_FILES})
target_compile_features(fluentMeshToFoam PUBLIC cxx_std_11)
target_link_libraries(fluentMeshToFoam PUBLIC finiteVolume)
