set(_FILES
  Test-multiDimPolyFitter.C
)
add_executable(Test-multiDimPolyFitter ${_FILES})
target_compile_features(Test-multiDimPolyFitter PUBLIC cxx_std_11)
target_include_directories(Test-multiDimPolyFitter PUBLIC
  .
)
