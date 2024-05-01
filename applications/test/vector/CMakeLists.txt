set(_FILES
  Test-vector.C
)
add_executable(Test-vector ${_FILES})
target_compile_features(Test-vector PUBLIC cxx_std_11)
