set(_FILES
  foamyHexMeshSurfaceSimplify.C
)
add_executable(foamyHexMeshSurfaceSimplify ${_FILES})
target_compile_features(foamyHexMeshSurfaceSimplify PUBLIC cxx_std_11)
target_link_libraries(foamyHexMeshSurfaceSimplify PUBLIC conformalVoronoiMesh dynamicMesh metisDecomp)
if (KAHIP_FOUND)
  target_link_libraries(foamyHexMeshSurfaceSimplify PUBLIC kahipDecomp)
endif()
if (SCOTCH_FOUND)
  target_link_libraries(foamyHexMeshSurfaceSimplify PUBLIC scotchDecomp)
endif()
