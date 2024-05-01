set(_FILES
  foamToStarMesh.C
)
add_executable(foamToStarMesh ${_FILES})
target_compile_features(foamToStarMesh PUBLIC cxx_std_11)
target_link_libraries(foamToStarMesh PUBLIC conversion)
