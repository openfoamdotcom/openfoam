set(_FILES
  Test-parallel-waitSome.C
)
add_executable(Test-parallel-waitSome ${_FILES})
target_compile_features(Test-parallel-waitSome PUBLIC cxx_std_11)
target_link_libraries(Test-parallel-waitSome PUBLIC finiteVolume)
