set(_FILES
  Test-EigenMatrix.C
)
add_executable(Test-EigenMatrix ${_FILES})
target_compile_features(Test-EigenMatrix PUBLIC cxx_std_11)
