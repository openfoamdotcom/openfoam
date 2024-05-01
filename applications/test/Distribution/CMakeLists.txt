set(_FILES
  Test-Distribution.C
)
add_executable(Test-DistributionTest ${_FILES})
target_compile_features(Test-DistributionTest PUBLIC cxx_std_11)
target_include_directories(Test-DistributionTest PUBLIC
  .
)
