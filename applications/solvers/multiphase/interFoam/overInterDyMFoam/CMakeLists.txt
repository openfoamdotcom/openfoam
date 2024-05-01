set(_FILES
  overInterDyMFoam.C
)
add_executable(overInterDyMFoam ${_FILES})
target_compile_features(overInterDyMFoam PUBLIC cxx_std_11)
target_link_libraries(overInterDyMFoam PUBLIC immiscibleIncompressibleTwoPhaseMixture topoChangerFvMesh twoPhaseProperties waveModels)
