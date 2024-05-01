set(_FILES
  lumpedPointZones.C
)
add_executable(lumpedPointZones ${_FILES})
target_compile_features(lumpedPointZones PUBLIC cxx_std_11)
target_link_libraries(lumpedPointZones PUBLIC lumpedPointMotion dynamicMesh)
