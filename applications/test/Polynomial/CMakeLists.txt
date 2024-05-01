set(_FILES
  Test-Polynomial.C
)
add_executable(Test-Polynomial ${_FILES})
target_compile_features(Test-Polynomial PUBLIC cxx_std_11)
