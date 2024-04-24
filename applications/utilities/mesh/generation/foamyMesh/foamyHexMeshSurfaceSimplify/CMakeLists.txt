set(_FILES
  foamyHexMeshSurfaceSimplify.C
)
add_executable(foamyHexMeshSurfaceSimplify ${_FILES})
target_compile_features(foamyHexMeshSurfaceSimplify PUBLIC cxx_std_11)
target_link_libraries(foamyHexMeshSurfaceSimplify PUBLIC finiteVolume)
