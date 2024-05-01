set(_FILES
  Test-DiagonalMatrix.C
)
add_executable(Test-DiagonalMatrix ${_FILES})
target_compile_features(Test-DiagonalMatrix PUBLIC cxx_std_11)
