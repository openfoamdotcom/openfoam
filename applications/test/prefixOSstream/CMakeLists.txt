set(_FILES
  Test-prefixOSstream.C
)
add_executable(Test-prefixOSstream ${_FILES})
target_compile_features(Test-prefixOSstream PUBLIC cxx_std_11)
