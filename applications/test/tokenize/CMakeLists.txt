set(_FILES
  Test-tokenize.C
)
add_executable(Test-tokenize ${_FILES})
target_compile_features(Test-tokenize PUBLIC cxx_std_11)
