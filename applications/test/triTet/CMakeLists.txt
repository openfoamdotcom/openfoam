set(_FILES
  Test-triTet.C
)
add_executable(Test-triTet ${_FILES})
target_compile_features(Test-triTet PUBLIC cxx_std_11)
