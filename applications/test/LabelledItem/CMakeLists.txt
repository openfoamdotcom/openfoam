set(_FILES
  Test-LabelledItem.C
)
add_executable(Test-LabelledItem ${_FILES})
target_compile_features(Test-LabelledItem PUBLIC cxx_std_11)
target_include_directories(Test-LabelledItem PUBLIC
  .
)
