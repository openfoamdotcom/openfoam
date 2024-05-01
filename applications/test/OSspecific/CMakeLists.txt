set(_FILES
  Test-OSspecific.C
)
add_executable(Test-OSspecific ${_FILES})
target_compile_features(Test-OSspecific PUBLIC cxx_std_11)
