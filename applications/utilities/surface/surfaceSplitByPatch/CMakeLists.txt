set(_FILES
  surfaceSplitByPatch.C
)
add_executable(surfaceSplitByPatch ${_FILES})
target_compile_features(surfaceSplitByPatch PUBLIC cxx_std_11)
target_link_libraries(surfaceSplitByPatch PUBLIC surfMesh)
