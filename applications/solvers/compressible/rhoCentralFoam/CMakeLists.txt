set(_FILES
  rhoCentralFoam.C
)
add_executable(rhoCentralFoam ${_FILES})
target_compile_features(rhoCentralFoam PUBLIC cxx_std_11)
target_link_libraries(rhoCentralFoam PUBLIC fvOptions rhoCentralFoam thermoTools topoChangerFvMesh)
target_include_directories(rhoCentralFoam PUBLIC
  .
)
