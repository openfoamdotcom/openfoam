set(_FILES
  overSimpleFoam.C
)
add_executable(overSimpleFoam ${_FILES})
target_compile_features(overSimpleFoam PUBLIC cxx_std_11)
target_link_libraries(overSimpleFoam PUBLIC fvOptions incompressibleTransportModels incompressibleTurbulenceModels overset topoChangerFvMesh)
target_include_directories(overSimpleFoam PUBLIC
  .
  ${PROJECT_SOURCE_DIR}/src/OpenFOAM/include
  ${PROJECT_SOURCE_DIR}/src/finiteVolume/cfdTools/general/solutionControl
)
