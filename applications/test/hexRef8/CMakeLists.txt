set(_FILES
  Test-hexRef8.C
)
add_executable(Test-hexRef8 ${_FILES})
target_compile_features(Test-hexRef8 PUBLIC cxx_std_11)
target_include_directories(Test-hexRef8 PUBLIC
  .
)
