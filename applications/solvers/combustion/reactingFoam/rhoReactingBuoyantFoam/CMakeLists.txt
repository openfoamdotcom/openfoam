set(_FILES
  rhoReactingBuoyantFoam.C
)
add_executable(rhoReactingBuoyantFoam ${_FILES})
target_compile_features(rhoReactingBuoyantFoam PUBLIC cxx_std_11)
target_link_libraries(rhoReactingBuoyantFoam PUBLIC combustionModels fvOptions thermoTools)
