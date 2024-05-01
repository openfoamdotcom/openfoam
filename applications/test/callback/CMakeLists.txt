set(_FILES
  Test-callback.C
)
add_executable(Test-callback ${_FILES})
target_compile_features(Test-callback PUBLIC cxx_std_11)
target_include_directories(Test-callback PUBLIC
  .
)
