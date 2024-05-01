set(_FILES
  Test-DynamicField.C
)
add_executable(Test-DynamicField ${_FILES})
target_compile_features(Test-DynamicField PUBLIC cxx_std_11)
target_include_directories(Test-DynamicField PUBLIC
  .
)
