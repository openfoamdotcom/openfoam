set(_FILES
  Test-gravityMeshObject.C
)
add_executable(Test-gravityMeshObject ${_FILES})
target_compile_features(Test-gravityMeshObject PUBLIC cxx_std_11)
target_include_directories(Test-gravityMeshObject PUBLIC
  .
)
