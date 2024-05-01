set(_FILES
  Test-IOobjectList.C
)
add_executable(Test-IOobjectList ${_FILES})
target_compile_features(Test-IOobjectList PUBLIC cxx_std_11)
