set(_FILES
  interPhaseChangeDyMFoam.C
)
add_executable(interPhaseChangeDyMFoam ${_FILES})
target_compile_features(interPhaseChangeDyMFoam PUBLIC cxx_std_11)
target_link_libraries(interPhaseChangeDyMFoam PUBLIC finiteVolume)
