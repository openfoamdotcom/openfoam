set(_FILES
  Test-Random.C
)
add_executable(Test-Random ${_FILES})
target_compile_features(Test-Random PUBLIC cxx_std_11)
target_include_directories(Test-Random PUBLIC
  .
)
