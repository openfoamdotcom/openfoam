set(_FILES
  foamyHexMesh.C
)
add_executable(foamyHexMesh ${_FILES})
target_compile_features(foamyHexMesh PUBLIC cxx_std_11)
target_link_libraries(foamyHexMesh PUBLIC conformalVoronoiMesh decompose dynamicMesh metisDecomp ptscotchDecomp)
if (KAHIP_FOUND)
  target_link_libraries(foamyHexMesh PUBLIC kahipDecomp)
endif()
if (SCOTCH_FOUND)
  target_link_libraries(foamyHexMesh PUBLIC scotchDecomp)
endif()
target_include_directories(foamyHexMesh PUBLIC
  .
)
