set(_FILES
  Test-patchRegion.C
)
add_executable(Test-patchRegion ${_FILES})
target_compile_features(Test-patchRegion PUBLIC cxx_std_11)
target_include_directories(Test-patchRegion PUBLIC
  .
)
