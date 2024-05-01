set(_FILES
  Test-stringSplit.C
)
add_executable(Test-stringSplit ${_FILES})
target_compile_features(Test-stringSplit PUBLIC cxx_std_11)
target_include_directories(Test-stringSplit PUBLIC
  .
)
