set(_FILES
  Test-readBroadcast1.C
)
add_executable(Test-readBroadcast1 ${_FILES})
target_compile_features(Test-readBroadcast1 PUBLIC cxx_std_11)
target_include_directories(Test-readBroadcast1 PUBLIC
  .
)
