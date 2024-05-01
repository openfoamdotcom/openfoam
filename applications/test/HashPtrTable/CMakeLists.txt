set(_FILES
  Test-HashPtrTable.C
)
add_executable(Test-HashPtrTable ${_FILES})
target_compile_features(Test-HashPtrTable PUBLIC cxx_std_11)
