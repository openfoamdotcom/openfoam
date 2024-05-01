set(_FILES
  Test-fileNameOS.C
)
add_executable(Test-fileNameOS ${_FILES})
target_compile_features(Test-fileNameOS PUBLIC cxx_std_11)
target_include_directories(Test-fileNameOS PUBLIC
  .
)
