set(_FILES
  Test-fileHandler-dummy.C
)
add_executable(Test-fileHandler-dummy ${_FILES})
target_compile_features(Test-fileHandler-dummy PUBLIC cxx_std_11)
target_include_directories(Test-fileHandler-dummy PUBLIC
  .
)
