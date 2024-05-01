set(_FILES
  potentialFreeSurfaceFoam.C
)
add_executable(potentialFreeSurfaceFoam ${_FILES})
target_compile_features(potentialFreeSurfaceFoam PUBLIC cxx_std_11)
target_link_libraries(potentialFreeSurfaceFoam PUBLIC fvOptions incompressibleTurbulenceModels sampling)
