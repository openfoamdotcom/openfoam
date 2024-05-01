set(_FILES
  MPPICFoam.C
)
add_executable(MPPICFoam ${_FILES})
target_compile_features(MPPICFoam PUBLIC cxx_std_11)
target_link_libraries(MPPICFoam PUBLIC fvOptions lagrangianTurbulence DPMTurbulenceModels surfaceFilmModels regionFaModels faOptions)
