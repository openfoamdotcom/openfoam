set(_FILES
  Test-HashingSpeed.C
)
add_executable(Test-HashingSpeed ${_FILES})
target_compile_features(Test-HashingSpeed PUBLIC cxx_std_11)
target_include_directories(Test-HashingSpeed PUBLIC
  .
)
