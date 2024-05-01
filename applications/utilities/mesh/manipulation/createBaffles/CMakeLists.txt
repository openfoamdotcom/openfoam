set(_FILES
  faceSelection/faceSelection.C
  faceSelection/faceZoneSelection.C
  faceSelection/searchableSurfaceSelection.C
  createBaffles.C
)
add_executable(createBaffles ${_FILES})
target_compile_features(createBaffles PUBLIC cxx_std_11)
target_link_libraries(createBaffles PUBLIC dynamicMesh reconstruct genericPatchFields)
