set(_FILES
  sonicDyMFoam.C
)
add_executable(sonicDyMFoam ${_FILES})
target_compile_features(sonicDyMFoam PUBLIC cxx_std_11)
target_link_libraries(sonicDyMFoam PUBLIC fvOptions sampling thermoTools topoChangerFvMesh)
