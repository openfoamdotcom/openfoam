set(_FILES
  Test-dimensionSet.C
)
add_executable(Test-dimensionSet ${_FILES})
target_compile_features(Test-dimensionSet PUBLIC cxx_std_11)
target_include_directories(Test-dimensionSet PUBLIC
  .
)
