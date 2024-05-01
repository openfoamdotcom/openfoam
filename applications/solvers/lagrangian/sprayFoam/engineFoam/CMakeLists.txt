set(_FILES
  engineFoam.C
)
add_executable(engineFoam ${_FILES})
target_compile_features(engineFoam PUBLIC cxx_std_11)
target_link_libraries(engineFoam PUBLIC engine faOptions lagrangianSpray regionFaModels surfaceFilmModels)
