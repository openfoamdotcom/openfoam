set(_FILES
  lumpedPointMovement.C
)
add_executable(lumpedPointMovement ${_FILES})
target_compile_features(lumpedPointMovement PUBLIC cxx_std_11)
target_link_libraries(lumpedPointMovement PUBLIC lumpedPointMotion)
target_include_directories(lumpedPointMovement PUBLIC
  .
)
