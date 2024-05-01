set(_FILES
  Test-parallel-comm0.C
)
add_executable(Test-parallel-comm0 ${_FILES})
target_compile_features(Test-parallel-comm0 PUBLIC cxx_std_11)
