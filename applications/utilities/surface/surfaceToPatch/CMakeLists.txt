set(_FILES
  surfaceToPatch.C
)
add_executable(surfaceToPatch ${_FILES})
target_compile_features(surfaceToPatch PUBLIC cxx_std_11)
target_link_libraries(surfaceToPatch PUBLIC dynamicMesh)
target_include_directories(surfaceToPatch PUBLIC
  .
)
