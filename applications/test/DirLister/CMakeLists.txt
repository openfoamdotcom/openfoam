set(_FILES
)
add_executable(Test-DirLister ${_FILES})
target_compile_features(Test-DirLister PUBLIC cxx_std_11)
target_include_directories(Test-DirLister PUBLIC
  .
)
