set(_FILES
  Test-bitops.C
)
add_executable(Test-bitops ${_FILES})
target_compile_features(Test-bitops PUBLIC cxx_std_11)
target_include_directories(Test-bitops PUBLIC
  .
)
