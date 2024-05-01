set(_FILES
  Test-fileNameClean.C
)
add_executable(Test-fileNameClean ${_FILES})
target_compile_features(Test-fileNameClean PUBLIC cxx_std_11)
