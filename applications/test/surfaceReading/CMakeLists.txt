set(_FILES
  Test-surfaceReading.C
)
add_executable(Test-surfaceReading ${_FILES})
target_compile_features(Test-surfaceReading PUBLIC cxx_std_11)
target_include_directories(Test-surfaceReading PUBLIC
  .
)
