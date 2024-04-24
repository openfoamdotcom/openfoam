set(_FILES
  collapseEdges.C
)
add_executable(collapseEdges ${_FILES})
target_compile_features(collapseEdges PUBLIC cxx_std_11)
target_link_libraries(collapseEdges PUBLIC finiteVolume)
