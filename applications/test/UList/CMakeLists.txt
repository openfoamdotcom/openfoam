set(_FILES
  Test-UList.C
)
add_executable(Test-UList ${_FILES})
target_compile_features(Test-UList PUBLIC cxx_std_11)
target_include_directories(Test-UList PUBLIC
  .
)
