set(_FILES
  fluentFvMesh.C
  foamMeshToFluent.C
)
add_executable(foamMeshToFluent ${_FILES})
target_compile_features(foamMeshToFluent PUBLIC cxx_std_11)
target_link_libraries(foamMeshToFluent PUBLIC finiteVolume)
target_include_directories(foamMeshToFluent PUBLIC
  .
)
