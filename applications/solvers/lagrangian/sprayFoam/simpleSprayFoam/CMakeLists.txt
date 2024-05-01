set(_FILES
  simpleSprayFoam.C
)
add_executable(simpleSprayFoam ${_FILES})
target_compile_features(simpleSprayFoam PUBLIC cxx_std_11)
target_link_libraries(simpleSprayFoam PUBLIC faOptions fvOptions lagrangianSpray lagrangianTurbulence regionFaModels surfaceFilmModels)
