set(_FILES
  Test-vectorTools.C
)
add_executable(Test-vectorTools ${_FILES})
target_compile_features(Test-vectorTools PUBLIC cxx_std_11)
