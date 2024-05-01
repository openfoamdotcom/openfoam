set(_FILES
  Test-timeSelector.C
)
add_executable(Test-timeSelector ${_FILES})
target_compile_features(Test-timeSelector PUBLIC cxx_std_11)
target_include_directories(Test-timeSelector PUBLIC
  .
)
