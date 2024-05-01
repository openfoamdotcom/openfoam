set(_FILES
  spring.C
)
add_executable(Test-spring ${_FILES})
target_compile_features(Test-spring PUBLIC cxx_std_11)
