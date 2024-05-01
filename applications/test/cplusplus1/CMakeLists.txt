set(_FILES
  Test-cpluplus1.C
)
add_executable(Test-cpluplus1 ${_FILES})
target_compile_features(Test-cpluplus1 PUBLIC cxx_std_11)
target_include_directories(Test-cpluplus1 PUBLIC
  .
)
