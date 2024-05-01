set(_FILES
  Test-Tensor.C
)
add_executable(Test-Tensor ${_FILES})
target_compile_features(Test-Tensor PUBLIC cxx_std_11)
