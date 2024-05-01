set(_FILES
  refineWallLayer.C
)
add_executable(refineWallLayer ${_FILES})
target_compile_features(refineWallLayer PUBLIC cxx_std_11)
target_link_libraries(refineWallLayer PUBLIC dynamicMesh reconstruct)
