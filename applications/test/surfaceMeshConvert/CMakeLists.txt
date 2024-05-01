set(_FILES
  Test-surfaceMeshConvert.C
)
add_executable(Test-surfaceMeshConvert ${_FILES})
target_compile_features(Test-surfaceMeshConvert PUBLIC cxx_std_11)
target_include_directories(Test-surfaceMeshConvert PUBLIC
  .
)
