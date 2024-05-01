set(_FILES
  reactingParcelFoam.C
)
add_executable(reactingParcelFoam ${_FILES})
target_compile_features(reactingParcelFoam PUBLIC cxx_std_11)
target_link_libraries(reactingParcelFoam PUBLIC faOptions fvOptions lagrangianTurbulence regionFaModels surfaceFilmDerivedFvPatchFields)
target_include_directories(reactingParcelFoam PUBLIC
  .
)
