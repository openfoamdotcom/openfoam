set(_FILES
  Test-SymmTensor2D.C
)
add_executable(Test-SymmTensor2D ${_FILES})
target_compile_features(Test-SymmTensor2D PUBLIC cxx_std_11)
