set(_FILES
  DPMFoam.C
)
add_executable(DPMFoam ${_FILES})
target_compile_features(DPMFoam PUBLIC cxx_std_11)
target_link_libraries(DPMFoam PUBLIC DPMTurbulenceModels faOptions fvOptions lagrangianTurbulence regionFaModels surfaceFilmModels)
