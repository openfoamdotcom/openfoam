set(_FILES
  overPimpleDyMFoam.C
)
add_executable(overPimpleDyMFoam ${_FILES})
target_compile_features(overPimpleDyMFoam PUBLIC cxx_std_11)
target_link_libraries(overPimpleDyMFoam PUBLIC fvOptions incompressibleTransportModels incompressibleTurbulenceModels overset topoChangerFvMesh)
target_include_directories(overPimpleDyMFoam PUBLIC
  .
)
