set(_FILES
  Test-faceHashing.C
)
add_executable(Test-faceHashing ${_FILES})
target_compile_features(Test-faceHashing PUBLIC cxx_std_11)
target_include_directories(Test-faceHashing PUBLIC
  .
)
