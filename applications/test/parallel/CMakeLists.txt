set(_FILES
  Test-parallel.C
)
add_executable(Test-parallel ${_FILES})
target_compile_features(Test-parallel PUBLIC cxx_std_11)
