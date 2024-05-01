set(_FILES
  orientFaceZone.C
)
add_executable(orientFaceZone ${_FILES})
target_compile_features(orientFaceZone PUBLIC cxx_std_11)
target_link_libraries(orientFaceZone PUBLIC snappyHexMeshLib)
