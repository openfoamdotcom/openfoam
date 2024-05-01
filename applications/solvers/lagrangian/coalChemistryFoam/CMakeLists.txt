set(_FILES
  coalChemistryFoam.C
)
add_executable(coalChemistryFoam ${_FILES})
target_compile_features(coalChemistryFoam PUBLIC cxx_std_11)
target_link_libraries(coalChemistryFoam PUBLIC coalCombustion faOptions fvOptions regionFaModels surfaceFilmModels)
target_include_directories(coalChemistryFoam PUBLIC
  .
)
