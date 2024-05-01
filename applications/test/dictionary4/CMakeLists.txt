set(_FILES
  Test-dictionary4.C
)
add_executable(Test-dictionary4 ${_FILES})
target_compile_features(Test-dictionary4 PUBLIC cxx_std_11)
target_include_directories(Test-dictionary4 PUBLIC
  .
)
