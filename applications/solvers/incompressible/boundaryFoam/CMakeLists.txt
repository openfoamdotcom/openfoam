set(_FILES
  boundaryFoam.C
)
add_executable(boundaryFoam ${_FILES})
target_compile_features(boundaryFoam PUBLIC cxx_std_11)
target_link_libraries(boundaryFoam PUBLIC fvOptions sampling incompressibleTurbulenceModels incompressibleTransportModels)
