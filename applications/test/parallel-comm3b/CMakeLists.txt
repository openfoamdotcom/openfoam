set(_FILES
  Test-parallel-comm3b.C
)
add_executable(Test-parallel-comm3b ${_FILES})
target_compile_features(Test-parallel-comm3b PUBLIC cxx_std_11)
target_include_directories(Test-parallel-comm3b PUBLIC
  .
)
