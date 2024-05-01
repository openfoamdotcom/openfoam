set(_FILES
  Test-IStringStream.C
)
add_executable(Test-IStringStream ${_FILES})
target_compile_features(Test-IStringStream PUBLIC cxx_std_11)
