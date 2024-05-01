set(_FILES
  Test-parallel-chunks.C
)
add_executable(Test-parallel-chunks ${_FILES})
target_compile_features(Test-parallel-chunks PUBLIC cxx_std_11)
target_include_directories(Test-parallel-chunks PUBLIC
  .
)
