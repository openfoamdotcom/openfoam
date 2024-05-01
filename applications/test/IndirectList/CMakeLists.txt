set(_FILES
  Test-IndirectList.C
)
add_executable(Test-IndirectList ${_FILES})
target_compile_features(Test-IndirectList PUBLIC cxx_std_11)
target_include_directories(Test-IndirectList PUBLIC
  .
)
