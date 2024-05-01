set(_FILES
)
add_executable(Test-ITstream ${_FILES})
target_compile_features(Test-ITstream PUBLIC cxx_std_11)
target_include_directories(Test-ITstream PUBLIC
  .
)
