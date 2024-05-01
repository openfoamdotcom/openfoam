set(_FILES
  Test-rawIOField.C
)
add_executable(Test-rawIOField ${_FILES})
target_compile_features(Test-rawIOField PUBLIC cxx_std_11)
target_include_directories(Test-rawIOField PUBLIC
  .
)
