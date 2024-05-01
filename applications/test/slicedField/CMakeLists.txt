set(_FILES
  Test-slicedField.C
)
add_executable(Test-slicedField ${_FILES})
target_compile_features(Test-slicedField PUBLIC cxx_std_11)
target_include_directories(Test-slicedField PUBLIC
  .
)
