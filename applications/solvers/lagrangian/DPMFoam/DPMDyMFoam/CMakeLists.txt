set(_FILES
  DPMDyMFoam.C
)
add_executable(DPMDyMFoam ${_FILES})
target_compile_features(DPMDyMFoam PUBLIC cxx_std_11)
target_link_libraries(DPMDyMFoam PUBLIC DPMTurbulenceModels faOptions fvOptions lagrangianTurbulence regionFaModels surfaceFilmModels topoChangerFvMesh)
