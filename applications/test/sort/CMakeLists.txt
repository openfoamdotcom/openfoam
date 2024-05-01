set(_FILES
)
add_executable(Test-sortList ${_FILES})
target_compile_features(Test-sortList PUBLIC cxx_std_11)
target_include_directories(Test-sortList PUBLIC
  .
)
