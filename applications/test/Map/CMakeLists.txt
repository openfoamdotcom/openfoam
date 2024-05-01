set(_FILES
  Test-Map.C
)
add_executable(Test-Map ${_FILES})
target_compile_features(Test-Map PUBLIC cxx_std_11)
