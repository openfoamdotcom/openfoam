set(_FILES
  Test-FixedList.C
)
add_executable(Test-FixedList ${_FILES})
target_compile_features(Test-FixedList PUBLIC cxx_std_11)
target_include_directories(Test-FixedList PUBLIC
  .
)
