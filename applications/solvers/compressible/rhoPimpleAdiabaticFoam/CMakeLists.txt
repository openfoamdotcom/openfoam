set(_FILES
  rhoPimpleAdiabaticFoam.C
)
add_executable(rhoPimpleAdiabaticFoam ${_FILES})
target_compile_features(rhoPimpleAdiabaticFoam PUBLIC cxx_std_11)
target_link_libraries(rhoPimpleAdiabaticFoam PUBLIC fvOptions thermoTools)
target_include_directories(rhoPimpleAdiabaticFoam PUBLIC
  .
)
