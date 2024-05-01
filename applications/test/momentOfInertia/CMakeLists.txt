set(_FILES
  Test-momentOfInertia.C
)
add_executable(Test-momentOfInertia ${_FILES})
target_compile_features(Test-momentOfInertia PUBLIC cxx_std_11)
target_include_directories(Test-momentOfInertia PUBLIC
  .
)
