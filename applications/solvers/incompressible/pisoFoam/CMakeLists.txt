set(_FILES
  pisoFoam.C
)
add_executable(pisoFoam ${_FILES})
target_compile_features(pisoFoam PUBLIC cxx_std_11)
target_link_libraries(pisoFoam PUBLIC fvOptions incompressibleTransportModels incompressibleTurbulenceModels sampling)
target_include_directories(pisoFoam PUBLIC
  .
)
