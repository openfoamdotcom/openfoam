set(_FILES
  spring.C
)
add_executable(Test-spring ${_FILES})
target_compile_features(Test-spring PUBLIC cxx_std_11)
target_include_directories(Test-spring PUBLIC
  .
)
