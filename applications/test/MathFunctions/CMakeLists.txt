set(_FILES
  Test-MathFunctions.C
)
add_executable(Test-MathFunctions ${_FILES})
target_compile_features(Test-MathFunctions PUBLIC cxx_std_11)
target_include_directories(Test-MathFunctions PUBLIC
  .
)
