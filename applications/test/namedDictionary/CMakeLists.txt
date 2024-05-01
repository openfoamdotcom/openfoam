set(_FILES
  Test-namedDictionary.C
)
add_executable(Test-namedDictionary ${_FILES})
target_compile_features(Test-namedDictionary PUBLIC cxx_std_11)
