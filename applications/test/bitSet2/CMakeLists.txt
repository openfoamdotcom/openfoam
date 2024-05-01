set(_FILES
  Test-bitSet2.C
)
add_executable(Test-bitSet2 ${_FILES})
target_compile_features(Test-bitSet2 PUBLIC cxx_std_11)
target_include_directories(Test-bitSet2 PUBLIC
  .
)
