set(_FILES
  Test-codeStream.C
)
add_executable(Test-codeStream ${_FILES})
target_compile_features(Test-codeStream PUBLIC cxx_std_11)
target_include_directories(Test-codeStream PUBLIC
  .
)
