set(_FILES
  Test-stringList.C
)
add_executable(Test-stringList ${_FILES})
target_compile_features(Test-stringList PUBLIC cxx_std_11)
