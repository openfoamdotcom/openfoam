set(_FILES
  Test-constantFields.C
)
add_executable(Test-constantFields ${_FILES})
target_compile_features(Test-constantFields PUBLIC cxx_std_11)
target_include_directories(Test-constantFields PUBLIC
  .
)
