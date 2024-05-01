set(_FILES
  Test-dimField.C
)
add_executable(Test-dimField ${_FILES})
target_compile_features(Test-dimField PUBLIC cxx_std_11)
target_include_directories(Test-dimField PUBLIC
  .
)
