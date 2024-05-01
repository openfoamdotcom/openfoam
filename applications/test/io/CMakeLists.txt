set(_FILES
  Test-io.C
)
add_executable(Test-io ${_FILES})
target_compile_features(Test-io PUBLIC cxx_std_11)
target_include_directories(Test-io PUBLIC
  .
)
