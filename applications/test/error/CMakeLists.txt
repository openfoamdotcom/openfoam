set(_FILES
  Test-error.C
)
add_executable(Test-error ${_FILES})
target_compile_features(Test-error PUBLIC cxx_std_11)
