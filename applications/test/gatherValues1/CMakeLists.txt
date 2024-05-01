set(_FILES
  Test-gatherValues1.C
)
add_executable(Test-gatherValues1 ${_FILES})
target_compile_features(Test-gatherValues1 PUBLIC cxx_std_11)
target_include_directories(Test-gatherValues1 PUBLIC
  .
)
