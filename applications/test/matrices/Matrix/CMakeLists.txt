set(_FILES
  Test-Matrix.C
)
add_executable(Test-Matrix ${_FILES})
target_compile_features(Test-Matrix PUBLIC cxx_std_11)
target_include_directories(Test-Matrix PUBLIC
  .
)
