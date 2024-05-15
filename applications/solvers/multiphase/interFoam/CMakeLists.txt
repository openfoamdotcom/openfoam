set(_FILES
  interFoam.C
)
add_executable(interFoam ${_FILES})
target_compile_features(interFoam PUBLIC cxx_std_11)
target_link_libraries(interFoam PUBLIC incompressibleInterPhaseTransportModels waveModels)
target_include_directories(interFoam PUBLIC
  .
  ../VoF
  ${PROJECT_SOURCE_DIR}/src/OpenFOAM/include
)
