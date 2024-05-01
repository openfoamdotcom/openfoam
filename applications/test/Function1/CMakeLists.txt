set(_FILES
  Test-Function1.C
)
add_executable(Test-Function1 ${_FILES})
target_compile_features(Test-Function1 PUBLIC cxx_std_11)
