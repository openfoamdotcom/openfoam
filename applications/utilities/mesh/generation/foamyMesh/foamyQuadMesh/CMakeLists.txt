set(_FILES
  CV2D.C
  insertFeaturePoints.C
  insertSurfaceNearestPointPairs.C
  insertSurfaceNearPointPairs.C
  insertBoundaryConformPointPairs.C
  CV2DIO.C
  shortEdgeFilter2D.C
  foamyQuadMesh.C
)
add_executable(foamyQuadMesh ${_FILES})
target_compile_features(foamyQuadMesh PUBLIC cxx_std_11)
target_link_libraries(foamyQuadMesh PUBLIC conformalVoronoiMesh metisDecomp ptscotchDecomp)
if (KAHIP_FOUND)
  target_link_libraries(foamyQuadMesh PUBLIC kahipDecomp)
endif()
if (SCOTCH_FOUND)
  target_link_libraries(foamyQuadMesh PUBLIC scotchDecomp)
endif()
