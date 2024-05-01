set(_FILES
  Test-edges.C
)
add_executable(Test-edges ${_FILES})
target_compile_features(Test-edges PUBLIC cxx_std_11)
