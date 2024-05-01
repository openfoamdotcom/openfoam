set(_FILES
  lumpedPointForces.C
)
add_executable(lumpedPointForces ${_FILES})
target_compile_features(lumpedPointForces PUBLIC cxx_std_11)
target_link_libraries(lumpedPointForces PUBLIC lumpedPointMotion)
target_include_directories(lumpedPointForces PUBLIC
  .
)
