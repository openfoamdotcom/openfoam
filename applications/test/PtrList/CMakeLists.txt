set(_FILES
  Test-PtrList.C
)
add_executable(Test-PtrList ${_FILES})
target_compile_features(Test-PtrList PUBLIC cxx_std_11)
