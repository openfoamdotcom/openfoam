set(_FILES
  steadyParticleTracks.C
)
add_executable(steadyParticleTracks ${_FILES})
target_compile_features(steadyParticleTracks PUBLIC cxx_std_11)
target_link_libraries(steadyParticleTracks PUBLIC finiteVolume)
