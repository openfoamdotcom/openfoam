set(_FILES
  Test-OSspecific.C
)
add_executable(Test-OSspecific ${_FILES})
target_compile_features(Test-OSspecific PUBLIC cxx_std_11)
target_include_directories(Test-OSspecific PUBLIC
  .
)
