set(_FILES
  Test-CompactIOList.C
)
add_executable(Test-CompactIOList ${_FILES})
target_compile_features(Test-CompactIOList PUBLIC cxx_std_11)
