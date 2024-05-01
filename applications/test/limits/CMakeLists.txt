set(_FILES
  Test-limits.C
)
add_executable(Test-limits ${_FILES})
target_compile_features(Test-limits PUBLIC cxx_std_11)
