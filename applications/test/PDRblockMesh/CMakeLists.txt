set(_FILES
  Test-PDRblockMesh.C
)
add_executable(Test-PDRblockMesh ${_FILES})
target_compile_features(Test-PDRblockMesh PUBLIC cxx_std_11)
