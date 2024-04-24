set(_FILES
  Test-compoundToken1.C
)
add_executable(Test-compoundToken1 ${_FILES})
target_compile_features(Test-compoundToken1 PUBLIC cxx_std_11)
target_link_libraries(Test-compoundToken1 PUBLIC finiteVolume)
