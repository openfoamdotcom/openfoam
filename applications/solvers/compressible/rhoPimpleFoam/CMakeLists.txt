set(_FILES
  rhoPimpleFoam.C
)
add_executable(rhoPimpleFoam ${_FILES})
target_compile_features(rhoPimpleFoam PUBLIC cxx_std_11)
target_link_libraries(rhoPimpleFoam PUBLIC atmosphericModels finiteArea regionFaModels topoChangerFvMesh)
