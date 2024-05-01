set(_FILES
  autoPatch.C
)
add_executable(autoPatch ${_FILES})
target_compile_features(autoPatch PUBLIC cxx_std_11)
target_link_libraries(autoPatch PUBLIC dynamicMesh)
