set(_FILES
  Test-ODE.C
)
add_executable(Test-ODE ${_FILES})
target_compile_features(Test-ODE PUBLIC cxx_std_11)
target_include_directories(Test-ODE PUBLIC
  .
)
