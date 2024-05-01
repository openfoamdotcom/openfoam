set(_FILES
  Test-fstreamPointer.C
)
add_executable(Test-fstreamPointer ${_FILES})
target_compile_features(Test-fstreamPointer PUBLIC cxx_std_11)
