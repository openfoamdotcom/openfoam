set(_FILES
  Test-SymmTensor.C
)
add_executable(Test-SymmTensor ${_FILES})
target_compile_features(Test-SymmTensor PUBLIC cxx_std_11)
target_include_directories(Test-SymmTensor PUBLIC
  .
)
