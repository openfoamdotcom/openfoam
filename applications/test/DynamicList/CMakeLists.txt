set(_FILES
  Test-DynamicList.C
)
add_executable(Test-DynamicList ${_FILES})
target_compile_features(Test-DynamicList PUBLIC cxx_std_11)
