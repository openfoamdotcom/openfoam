set(_FILES
  Test-processorTopology.C
)
add_executable(Test-processorTopology ${_FILES})
target_compile_features(Test-processorTopology PUBLIC cxx_std_11)
target_include_directories(Test-processorTopology PUBLIC
  .
)
