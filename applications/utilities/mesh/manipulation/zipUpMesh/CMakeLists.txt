set(_FILES
  zipUpMesh.C
)
add_executable(zipUpMesh ${_FILES})
target_compile_features(zipUpMesh PUBLIC cxx_std_11)
target_link_libraries(zipUpMesh PUBLIC meshTools)
target_include_directories(zipUpMesh PUBLIC
  .
)
