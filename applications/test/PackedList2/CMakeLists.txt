set(_FILES
  Test-PackedList2.C
)
add_executable(Test-PackedList2 ${_FILES})
target_compile_features(Test-PackedList2 PUBLIC cxx_std_11)
target_include_directories(Test-PackedList2 PUBLIC
  .
)
