set(_FILES
  sprayDyMFoam.C
)
add_executable(sprayDyMFoam ${_FILES})
target_compile_features(sprayDyMFoam PUBLIC cxx_std_11)
target_link_libraries(sprayDyMFoam PUBLIC faOptions fvOptions lagrangianSpray regionFaModels surfaceFilmModels topoChangerFvMesh)
target_include_directories(sprayDyMFoam PUBLIC
  .
)
