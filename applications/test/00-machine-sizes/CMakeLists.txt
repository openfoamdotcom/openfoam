set(_FILES
)
add_executable(Test-machine-sizes ${_FILES})
target_compile_features(Test-machine-sizes PUBLIC cxx_std_11)
target_include_directories(Test-machine-sizes PUBLIC
  .
)
