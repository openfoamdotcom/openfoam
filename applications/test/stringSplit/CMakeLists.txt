set(_FILES
  Test-stringSplit.C
)
add_executable(Test-stringSplit ${_FILES})
target_compile_features(Test-stringSplit PUBLIC cxx_std_11)
