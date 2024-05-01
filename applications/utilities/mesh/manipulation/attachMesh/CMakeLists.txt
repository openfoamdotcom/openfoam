set(_FILES
  attachMesh.C
)
add_executable(attachMesh ${_FILES})
target_compile_features(attachMesh PUBLIC cxx_std_11)
target_link_libraries(attachMesh PUBLIC dynamicMesh meshTools)
