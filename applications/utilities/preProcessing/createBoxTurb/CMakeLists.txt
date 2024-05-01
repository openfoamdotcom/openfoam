set(_FILES
  createBoxTurb.C
)
add_executable(createBoxTurb ${_FILES})
target_compile_features(createBoxTurb PUBLIC cxx_std_11)
target_link_libraries(createBoxTurb PUBLIC finiteVolume blockMesh)
