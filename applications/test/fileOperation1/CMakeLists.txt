set(_FILES
  Test-fileOperation1.C
)
add_executable(Test-fileOperation1 ${_FILES})
target_compile_features(Test-fileOperation1 PUBLIC cxx_std_11)
