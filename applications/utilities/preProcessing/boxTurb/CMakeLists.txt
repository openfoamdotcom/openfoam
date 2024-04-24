set(_FILES
  boxTurb.C
)
add_executable(boxTurb ${_FILES})
target_compile_features(boxTurb PUBLIC cxx_std_11)
target_link_libraries(boxTurb PUBLIC finiteVolume)
