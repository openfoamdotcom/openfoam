set(_FILES
  Test-UniformField.C
)
add_executable(Test-UniformField ${_FILES})
target_compile_features(Test-UniformField PUBLIC cxx_std_11)
target_include_directories(Test-UniformField PUBLIC
  .
)
