set(_FILES
  Test-argList.C
)
add_executable(Test-argList ${_FILES})
target_compile_features(Test-argList PUBLIC cxx_std_11)
