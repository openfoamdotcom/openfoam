set(_FILES
  Test-barycentric.C
)
add_executable(Test-barycentric ${_FILES})
target_compile_features(Test-barycentric PUBLIC cxx_std_11)
target_include_directories(Test-barycentric PUBLIC
  .
)
