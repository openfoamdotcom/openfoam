set(_FILES
  Test-faces.C
)
add_executable(Test-faces ${_FILES})
target_compile_features(Test-faces PUBLIC cxx_std_11)
target_include_directories(Test-faces PUBLIC
  .
)
