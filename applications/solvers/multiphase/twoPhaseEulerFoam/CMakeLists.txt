set(_FILES
  twoPhaseEulerFoam.C
)
add_executable(twoPhaseEulerFoam ${_FILES})
target_compile_features(twoPhaseEulerFoam PUBLIC cxx_std_11)
target_link_libraries(twoPhaseEulerFoam PUBLIC finiteVolume)
