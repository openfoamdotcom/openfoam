set(_FILES
  Test-ICharStream1.C
)
add_executable(Test-ICharStream1 ${_FILES})
target_compile_features(Test-ICharStream1 PUBLIC cxx_std_11)
target_link_libraries(Test-ICharStream1 PUBLIC finiteVolume)
