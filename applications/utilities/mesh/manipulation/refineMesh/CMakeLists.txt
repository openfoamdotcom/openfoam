set(_FILES
  refineMesh.C
)
add_executable(refineMesh ${_FILES})
target_compile_features(refineMesh PUBLIC cxx_std_11)
target_link_libraries(refineMesh PUBLIC finiteVolume)
