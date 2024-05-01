set(_FILES
  Test-mkdir.C
)
add_executable(Test-mkdir ${_FILES})
target_compile_features(Test-mkdir PUBLIC cxx_std_11)
