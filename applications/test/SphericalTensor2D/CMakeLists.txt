set(_FILES
  Test-SphericalTensor2D.C
)
add_executable(Test-SphericalTensor2D ${_FILES})
target_compile_features(Test-SphericalTensor2D PUBLIC cxx_std_11)
target_include_directories(Test-SphericalTensor2D PUBLIC
  .
)
