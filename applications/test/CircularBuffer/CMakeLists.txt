set(_FILES
  Test-CircularBuffer.C
)
add_executable(Test-CircularBuffer ${_FILES})
target_compile_features(Test-CircularBuffer PUBLIC cxx_std_11)
