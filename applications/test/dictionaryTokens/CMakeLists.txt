set(_FILES
  Test-dictionaryTokens.C
  dictionaryTokens.C
)
add_executable(Test-dictionaryTokens ${_FILES})
target_compile_features(Test-dictionaryTokens PUBLIC cxx_std_11)
target_include_directories(Test-dictionaryTokens PUBLIC
  .
)
