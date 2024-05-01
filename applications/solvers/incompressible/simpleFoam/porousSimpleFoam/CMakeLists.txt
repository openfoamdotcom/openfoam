set(_FILES
  porousSimpleFoam.C
)
add_executable(porousSimpleFoam ${_FILES})
target_compile_features(porousSimpleFoam PUBLIC cxx_std_11)
target_link_libraries(porousSimpleFoam PUBLIC fvOptions incompressibleTransportModels incompressibleTurbulenceModels sampling)
