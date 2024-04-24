set(_FILES
  mixtureAdiabaticFlameT.C
)
add_executable(mixtureAdiabaticFlameT ${_FILES})
target_compile_features(mixtureAdiabaticFlameT PUBLIC cxx_std_11)
target_link_libraries(mixtureAdiabaticFlameT PUBLIC finiteVolume)
