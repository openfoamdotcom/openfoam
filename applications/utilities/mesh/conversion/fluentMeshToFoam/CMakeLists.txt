set(_FILES
  extrudedTriangleCellShape.C
  extrudedQuadCellShape.C
  create3DCellShape.C
)
set(_flex_src ${CMAKE_CURRENT_BINARY_DIR}/fluentMeshToFoam.C)
flex_target(MyFlexName fluentMeshToFoam.L "${_flex_src}" COMPILE_FLAGS --c++)
add_executable(fluentMeshToFoam ${_FILES} ${_flex_src})
target_compile_features(fluentMeshToFoam PUBLIC cxx_std_11)
target_link_libraries(fluentMeshToFoam PUBLIC dynamicMesh)
target_include_directories(fluentMeshToFoam PUBLIC
  .
)
