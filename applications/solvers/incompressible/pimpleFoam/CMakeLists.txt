set(_FILES
  pimpleFoam.C
)
add_executable(pimpleFoam ${_FILES})
target_compile_features(pimpleFoam PUBLIC cxx_std_11)
target_link_libraries(pimpleFoam PUBLIC atmosphericModels finiteArea regionFaModels topoChangerFvMesh)
target_include_directories(pimpleFoam PUBLIC
  .
)
