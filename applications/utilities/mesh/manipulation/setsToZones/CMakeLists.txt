set(_FILES
  setsToZones.C
)
add_executable(setsToZones ${_FILES})
target_compile_features(setsToZones PUBLIC cxx_std_11)
target_link_libraries(setsToZones PUBLIC finiteVolume)
