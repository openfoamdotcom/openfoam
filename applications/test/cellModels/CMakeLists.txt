set(_FILES
  Test-cellModels.C
)
add_executable(Test-cellModels ${_FILES})
target_compile_features(Test-cellModels PUBLIC cxx_std_11)
target_include_directories(Test-cellModels PUBLIC
  .
)
