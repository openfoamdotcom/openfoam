set(_FILES
  mergeOrSplitBaffles.C
)
add_executable(mergeOrSplitBaffles ${_FILES})
target_compile_features(mergeOrSplitBaffles PUBLIC cxx_std_11)
target_link_libraries(mergeOrSplitBaffles PUBLIC dynamicMesh genericPatchFields reconstruct)
target_include_directories(mergeOrSplitBaffles PUBLIC
  .
)
