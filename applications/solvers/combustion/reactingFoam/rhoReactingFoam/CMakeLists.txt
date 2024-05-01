set(_FILES
  rhoReactingFoam.C
)
add_executable(rhoReactingFoam ${_FILES})
target_compile_features(rhoReactingFoam PUBLIC cxx_std_11)
target_link_libraries(rhoReactingFoam PUBLIC combustionModels fvOptions thermoTools)
target_include_directories(rhoReactingFoam PUBLIC
  .
)
