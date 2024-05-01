set(_FILES
  Test-plotFunction1.C
)
add_executable(Test-plotFunction1 ${_FILES})
target_compile_features(Test-plotFunction1 PUBLIC cxx_std_11)
target_include_directories(Test-plotFunction1 PUBLIC
  .
)
