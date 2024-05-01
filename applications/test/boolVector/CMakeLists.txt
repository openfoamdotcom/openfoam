set(_FILES
  Test-boolVector.C
)
add_executable(Test-boolVector ${_FILES})
target_compile_features(Test-boolVector PUBLIC cxx_std_11)
target_include_directories(Test-boolVector PUBLIC
  .
)
