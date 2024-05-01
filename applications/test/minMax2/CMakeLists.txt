set(_FILES
  Test-minMax2.C
)
add_executable(Test-minMax2 ${_FILES})
target_compile_features(Test-minMax2 PUBLIC cxx_std_11)
target_include_directories(Test-minMax2 PUBLIC
  .
)
