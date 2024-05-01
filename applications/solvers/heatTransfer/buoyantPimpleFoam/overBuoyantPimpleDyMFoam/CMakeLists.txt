set(_FILES
  overBuoyantPimpleDyMFoam.C
)
add_executable(overBuoyantPimpleDyMFoam ${_FILES})
target_compile_features(overBuoyantPimpleDyMFoam PUBLIC cxx_std_11)
target_link_libraries(overBuoyantPimpleDyMFoam PUBLIC thermoTools atmosphericModels overset topoChangerFvMesh)
