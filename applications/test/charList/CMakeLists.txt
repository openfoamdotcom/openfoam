set(_FILES
  Test-charList.C
)
add_executable(Test-charList ${_FILES})
target_compile_features(Test-charList PUBLIC cxx_std_11)
target_include_directories(Test-charList PUBLIC
  .
)
