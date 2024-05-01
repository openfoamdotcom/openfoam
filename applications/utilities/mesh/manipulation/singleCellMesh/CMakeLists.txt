set(_FILES
  singleCellMesh.C
)
add_executable(singleCellMesh ${_FILES})
target_compile_features(singleCellMesh PUBLIC cxx_std_11)
target_link_libraries(singleCellMesh PUBLIC genericPatchFields)
