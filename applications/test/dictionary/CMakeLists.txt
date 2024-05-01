set(_FILES
  Test-dictionary.C
)
add_executable(Test-dictionary ${_FILES})
target_compile_features(Test-dictionary PUBLIC cxx_std_11)
target_include_directories(Test-dictionary PUBLIC
  .
)
