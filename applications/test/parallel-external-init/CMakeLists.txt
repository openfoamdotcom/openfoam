set(_FILES
  Test-parallel-external-init.C
)
add_executable(Test-parallel-external-init ${_FILES})
target_compile_features(Test-parallel-external-init PUBLIC cxx_std_11)
target_include_directories(Test-parallel-external-init PUBLIC
  .
)
