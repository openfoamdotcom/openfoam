set(_FILES
  removeFaces.C
)
add_executable(removeFaces ${_FILES})
target_compile_features(removeFaces PUBLIC cxx_std_11)
target_link_libraries(removeFaces PUBLIC dynamicMesh genericPatchFields reconstruct)
