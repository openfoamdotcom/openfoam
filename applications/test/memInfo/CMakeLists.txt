set(_FILES
)
add_executable(Test-memInfo ${_FILES})
target_compile_features(Test-memInfo PUBLIC cxx_std_11)
target_include_directories(Test-memInfo PUBLIC
  .
)
