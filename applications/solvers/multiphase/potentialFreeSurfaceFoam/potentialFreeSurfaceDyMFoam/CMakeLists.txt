set(_FILES
  potentialFreeSurfaceDyMFoam.C
)
add_executable(potentialFreeSurfaceDyMFoam ${_FILES})
target_compile_features(potentialFreeSurfaceDyMFoam PUBLIC cxx_std_11)
target_link_libraries(potentialFreeSurfaceDyMFoam PUBLIC fvOptions incompressibleTurbulenceModels sampling topoChangerFvMesh)
target_include_directories(potentialFreeSurfaceDyMFoam PUBLIC
  .
)
