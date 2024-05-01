set(_FILES
  overPimpleDyMFoam.C
)
add_executable(overPimpleDyMFoam ${_FILES})
target_compile_features(overPimpleDyMFoam PUBLIC cxx_std_11)
target_link_libraries(overPimpleDyMFoam PUBLIC fvOptions incompressibleTurbulenceModels incompressibleTransportModels topoChangerFvMesh overset)
