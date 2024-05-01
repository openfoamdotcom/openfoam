set(_FILES
  Test-parallel-comm3a.C
)
add_executable(Test-parallel-comm3a ${_FILES})
target_compile_features(Test-parallel-comm3a PUBLIC cxx_std_11)
target_include_directories(Test-parallel-comm3a PUBLIC
  .
)
