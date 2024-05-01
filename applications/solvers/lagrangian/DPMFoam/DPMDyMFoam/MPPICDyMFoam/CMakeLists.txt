set(_FILES
  MPPICDyMFoam.C
)
add_executable(MPPICDyMFoam ${_FILES})
target_compile_features(MPPICDyMFoam PUBLIC cxx_std_11)
target_link_libraries(MPPICDyMFoam PUBLIC DPMTurbulenceModels faOptions fvOptions lagrangianTurbulence regionFaModels surfaceFilmModels topoChangerFvMesh)
