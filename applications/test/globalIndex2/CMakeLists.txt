set(_FILES
)
add_executable(Test-globalIndex2 ${_FILES})
target_compile_features(Test-globalIndex2 PUBLIC cxx_std_11)
target_include_directories(Test-globalIndex2 PUBLIC
  .
)
