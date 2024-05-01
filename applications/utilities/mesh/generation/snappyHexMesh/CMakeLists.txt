set(_FILES
  snappyHexMesh.C
)
add_executable(snappyHexMesh ${_FILES})
target_compile_features(snappyHexMesh PUBLIC cxx_std_11)
target_link_libraries(snappyHexMesh PUBLIC decompose metisDecomp ptscotchDecomp reconstruct snappyHexMeshLib)
if (KAHIP_FOUND)
  target_link_libraries(snappyHexMesh PUBLIC kahipDecomp)
endif()
if (SCOTCH_FOUND)
  target_link_libraries(snappyHexMesh PUBLIC scotchDecomp)
endif()
