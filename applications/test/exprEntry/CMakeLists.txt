set(_FILES
  Test-exprEntry.C
)
add_executable(Test-exprEntry ${_FILES})
target_compile_features(Test-exprEntry PUBLIC cxx_std_11)
target_include_directories(Test-exprEntry PUBLIC
  .
)
