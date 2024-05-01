set(_FILES
  Test-OCharStream1.C
)
add_executable(Test-OCharStream1 ${_FILES})
target_compile_features(Test-OCharStream1 PUBLIC cxx_std_11)
target_include_directories(Test-OCharStream1 PUBLIC
  .
)
