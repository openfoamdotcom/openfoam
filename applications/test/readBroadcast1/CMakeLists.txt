set(_FILES
  Test-readBroadcast1.C
)
add_executable(Test-readBroadcast1 ${_FILES})
target_compile_features(Test-readBroadcast1 PUBLIC cxx_std_11)
target_link_libraries(Test-readBroadcast1 PUBLIC finiteVolume)
