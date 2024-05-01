set(_FILES
  Test-findSphereFeatureEdges-octree.C
)
add_executable(Test-findSphereFeatureEdges-octree ${_FILES})
target_compile_features(Test-findSphereFeatureEdges-octree PUBLIC cxx_std_11)
