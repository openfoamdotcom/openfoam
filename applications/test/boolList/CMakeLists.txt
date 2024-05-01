set(_FILES
  Test-boolList.C
)
add_executable(Test-boolList ${_FILES})
target_compile_features(Test-boolList PUBLIC cxx_std_11)
