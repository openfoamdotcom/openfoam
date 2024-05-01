set(_FILES
  interFoam.C
)
add_executable(interFoam ${_FILES})
target_compile_features(interFoam PUBLIC cxx_std_11)
target_link_libraries(interFoam PUBLIC waveModels incompressibleInterPhaseTransportModels)
