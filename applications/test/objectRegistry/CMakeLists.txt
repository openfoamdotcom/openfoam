set(_FILES
  Test-objectRegistry.C
)
add_executable(Test-objectRegistry ${_FILES})
target_compile_features(Test-objectRegistry PUBLIC cxx_std_11)
target_include_directories(Test-objectRegistry PUBLIC
  .
)
