set(_FILES
  Test-tetTetOverlap.C
)
add_executable(Test-tetTetOverlap ${_FILES})
target_compile_features(Test-tetTetOverlap PUBLIC cxx_std_11)
target_include_directories(Test-tetTetOverlap PUBLIC
  .
)
