set(_FILES
  Test-boundaryMeshEntries.C
)
add_executable(Test-boundaryMeshEntries ${_FILES})
target_compile_features(Test-boundaryMeshEntries PUBLIC cxx_std_11)
target_include_directories(Test-boundaryMeshEntries PUBLIC
  .
)
