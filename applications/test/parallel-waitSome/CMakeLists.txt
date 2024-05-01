set(_FILES
  Test-parallel-waitSome.C
)
add_executable(Test-parallel-waitSome ${_FILES})
target_compile_features(Test-parallel-waitSome PUBLIC cxx_std_11)
target_include_directories(Test-parallel-waitSome PUBLIC
  .
)
