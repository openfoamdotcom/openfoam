set(_FILES
  Test-findSphereFeatureEdges-octree.C
)
add_executable(Test-findSphereFeatureEdges-octree ${_FILES})
target_compile_features(Test-findSphereFeatureEdges-octree PUBLIC cxx_std_11)
target_include_directories(Test-findSphereFeatureEdges-octree PUBLIC
  .
)
