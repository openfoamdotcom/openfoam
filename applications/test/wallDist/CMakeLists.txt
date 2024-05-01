set(_FILES
  Test-wallDist.C
)
add_executable(Test-wallDist ${_FILES})
target_compile_features(Test-wallDist PUBLIC cxx_std_11)
target_include_directories(Test-wallDist PUBLIC
  .
)
