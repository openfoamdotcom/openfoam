set(_FILES
  Test-copyFile.C
)
add_executable(Test-copyFile ${_FILES})
target_compile_features(Test-copyFile PUBLIC cxx_std_11)
target_include_directories(Test-copyFile PUBLIC
  .
)
