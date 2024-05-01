set(_FILES
)
add_executable(Test-globalIndex1 ${_FILES})
target_compile_features(Test-globalIndex1 PUBLIC cxx_std_11)
target_include_directories(Test-globalIndex1 PUBLIC
  .
)
