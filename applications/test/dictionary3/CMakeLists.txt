set(_FILES
)
add_executable(Test-dictionary3 ${_FILES})
target_compile_features(Test-dictionary3 PUBLIC cxx_std_11)
target_include_directories(Test-dictionary3 PUBLIC
  .
)
