set(_FILES
  Test-refPtr.C
)
add_executable(Test-refPtr ${_FILES})
target_compile_features(Test-refPtr PUBLIC cxx_std_11)
target_include_directories(Test-refPtr PUBLIC
  .
)
