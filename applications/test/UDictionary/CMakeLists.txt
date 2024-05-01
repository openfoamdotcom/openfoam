set(_FILES
  Test-UDictionary.C
)
add_executable(Test-UDictionary ${_FILES})
target_compile_features(Test-UDictionary PUBLIC cxx_std_11)
target_include_directories(Test-UDictionary PUBLIC
  .
)
