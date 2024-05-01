set(_FILES
  Test-sigFpe.C
)
add_executable(Test-sigFpe ${_FILES})
target_compile_features(Test-sigFpe PUBLIC cxx_std_11)
target_include_directories(Test-sigFpe PUBLIC
  .
)
