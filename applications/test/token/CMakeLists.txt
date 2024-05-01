set(_FILES
)
add_executable(Test-token ${_FILES})
target_compile_features(Test-token PUBLIC cxx_std_11)
target_include_directories(Test-token PUBLIC
  .
)
