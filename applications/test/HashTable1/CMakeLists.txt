set(_FILES
  Test-HashTable1.C
)
add_executable(Test-HashTable1 ${_FILES})
target_compile_features(Test-HashTable1 PUBLIC cxx_std_11)
