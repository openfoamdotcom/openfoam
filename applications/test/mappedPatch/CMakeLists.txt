set(_FILES
  Test-MappedPatch.C
)
add_executable(Test-MappedPatch ${_FILES})
target_compile_features(Test-MappedPatch PUBLIC cxx_std_11)
target_include_directories(Test-MappedPatch PUBLIC
  .
)
