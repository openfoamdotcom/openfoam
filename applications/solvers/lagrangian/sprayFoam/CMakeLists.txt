set(_FILES
  sprayFoam.C
)
add_executable(sprayFoam ${_FILES})
target_compile_features(sprayFoam PUBLIC cxx_std_11)
target_link_libraries(sprayFoam PUBLIC faOptions fvOptions lagrangianSpray regionFaModels surfaceFilmModels)
