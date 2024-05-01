set(_FILES
  Test-labelRanges.C
)
add_executable(Test-labelRanges ${_FILES})
target_compile_features(Test-labelRanges PUBLIC cxx_std_11)
target_include_directories(Test-labelRanges PUBLIC
  .
)
