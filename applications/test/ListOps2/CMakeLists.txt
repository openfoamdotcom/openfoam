set(_FILES
  Test-ListOps2.C
)
add_executable(Test-ListOps2 ${_FILES})
target_compile_features(Test-ListOps2 PUBLIC cxx_std_11)
