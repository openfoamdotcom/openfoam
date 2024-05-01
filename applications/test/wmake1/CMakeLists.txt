set(_FILES
  Test-wmake1.C
  newStub.C
  oldStub.C
)
add_executable(Test-wmake1 ${_FILES})
target_compile_features(Test-wmake1 PUBLIC cxx_std_11)
target_include_directories(Test-wmake1 PUBLIC
  .
)
