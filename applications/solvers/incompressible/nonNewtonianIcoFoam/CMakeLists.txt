set(_FILES
  nonNewtonianIcoFoam.C
)
add_executable(nonNewtonianIcoFoam ${_FILES})
target_compile_features(nonNewtonianIcoFoam PUBLIC cxx_std_11)
target_link_libraries(nonNewtonianIcoFoam PUBLIC incompressibleTransportModels finiteVolume meshTools)
