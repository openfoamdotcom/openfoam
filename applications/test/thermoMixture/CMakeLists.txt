set(_FILES
  Test-thermoMixture.C
)
add_executable(Test-thermoMixture ${_FILES})
target_compile_features(Test-thermoMixture PUBLIC cxx_std_11)
target_include_directories(Test-thermoMixture PUBLIC
  .
)
