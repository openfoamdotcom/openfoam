set(_FILES
  checkFaMesh.C
)
add_executable(checkFaMesh ${_FILES})
target_compile_features(checkFaMesh PUBLIC cxx_std_11)
target_link_libraries(checkFaMesh PUBLIC finiteVolume)
