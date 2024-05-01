set(_FILES
  Test-Circulator.C
)
add_executable(Test-Circulator ${_FILES})
target_compile_features(Test-Circulator PUBLIC cxx_std_11)
target_include_directories(Test-Circulator PUBLIC
  .
)
