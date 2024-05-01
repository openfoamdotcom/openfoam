set(_FILES
  Test-BinSum.C
)
add_executable(Test-BinSum ${_FILES})
target_compile_features(Test-BinSum PUBLIC cxx_std_11)
target_include_directories(Test-BinSum PUBLIC
  .
)
