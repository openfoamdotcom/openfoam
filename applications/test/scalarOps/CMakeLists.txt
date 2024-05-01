set(_FILES
  Test-scalarOps.C
)
add_executable(Test-scalarOps ${_FILES})
target_compile_features(Test-scalarOps PUBLIC cxx_std_11)
target_include_directories(Test-scalarOps PUBLIC
  .
)
