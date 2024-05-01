set(_FILES
  Test-Tensor2DCaseDir.C
)
add_executable(Test-Tensor2DCaseDir ${_FILES})
target_compile_features(Test-Tensor2DCaseDir PUBLIC cxx_std_11)
target_include_directories(Test-Tensor2DCaseDir PUBLIC
  .
)
