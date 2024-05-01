set(_FILES
  Test-exprTraits.C
)
add_executable(Test-exprTraits ${_FILES})
target_compile_features(Test-exprTraits PUBLIC cxx_std_11)
target_include_directories(Test-exprTraits PUBLIC
  .
)
