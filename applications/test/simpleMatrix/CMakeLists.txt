set(_FILES
  Test-simpleMatrix.C
)
add_executable(Test-simpleMatrix ${_FILES})
target_compile_features(Test-simpleMatrix PUBLIC cxx_std_11)
target_include_directories(Test-simpleMatrix PUBLIC
  .
)
