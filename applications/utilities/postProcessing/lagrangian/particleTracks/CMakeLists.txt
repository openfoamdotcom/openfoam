set(_FILES
  particleTracks.C
)
add_executable(particleTracks ${_FILES})
target_compile_features(particleTracks PUBLIC cxx_std_11)
target_link_libraries(particleTracks PUBLIC finiteVolume)
