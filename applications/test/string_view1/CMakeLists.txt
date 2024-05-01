set(_FILES
  Test-string_view1.C
)
add_executable(Test-string_view1 ${_FILES})
target_compile_features(Test-string_view1 PUBLIC cxx_std_11)
target_include_directories(Test-string_view1 PUBLIC
  .
)
