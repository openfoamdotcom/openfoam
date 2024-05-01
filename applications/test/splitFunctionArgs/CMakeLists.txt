set(_FILES
  Test-splitFunctionArgs.C
)
add_executable(Test-splitFunctionArgs ${_FILES})
target_compile_features(Test-splitFunctionArgs PUBLIC cxx_std_11)
target_include_directories(Test-splitFunctionArgs PUBLIC
  .
)
