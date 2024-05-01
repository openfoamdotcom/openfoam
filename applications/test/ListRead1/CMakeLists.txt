set(_FILES
  Test-ListRead1.C
)
add_executable(Test-ListRead1 ${_FILES})
target_compile_features(Test-ListRead1 PUBLIC cxx_std_11)
