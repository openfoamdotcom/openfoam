set(_FILES
  Test-PatchTools.C
)
add_executable(Test-PatchTools ${_FILES})
target_compile_features(Test-PatchTools PUBLIC cxx_std_11)
target_include_directories(Test-PatchTools PUBLIC
  .
)
