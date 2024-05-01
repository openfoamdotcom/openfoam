set(_FILES
  Test-treeComms.C
)
add_executable(Test-treeComms ${_FILES})
target_compile_features(Test-treeComms PUBLIC cxx_std_11)
target_include_directories(Test-treeComms PUBLIC
  .
)
