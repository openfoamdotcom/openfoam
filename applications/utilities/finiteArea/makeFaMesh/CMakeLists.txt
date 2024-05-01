set(_FILES
  makeFaMesh.C
)
add_executable(makeFaMesh ${_FILES})
target_compile_features(makeFaMesh PUBLIC cxx_std_11)
target_link_libraries(makeFaMesh PUBLIC faDecompose faReconstruct)
