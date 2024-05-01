set(_FILES
  Test-invTensor.C
)
add_executable(Test-invTensor ${_FILES})
target_compile_features(Test-invTensor PUBLIC cxx_std_11)
target_include_directories(Test-invTensor PUBLIC
  .
)
