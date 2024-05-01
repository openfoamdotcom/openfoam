set(_FILES
  ensightMeshReader.C
  ensightToFoam.C
)
add_executable(ensightToFoam ${_FILES})
target_compile_features(ensightToFoam PUBLIC cxx_std_11)
target_link_libraries(ensightToFoam PUBLIC conversion)
target_include_directories(ensightToFoam PUBLIC
  .
)
