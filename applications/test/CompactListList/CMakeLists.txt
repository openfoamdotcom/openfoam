set(_FILES
)
add_executable(Test-CompactListList ${_FILES})
target_compile_features(Test-CompactListList PUBLIC cxx_std_11)
target_include_directories(Test-CompactListList PUBLIC
  .
)
