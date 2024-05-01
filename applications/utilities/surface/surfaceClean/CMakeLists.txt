set(_FILES
  collapseBase.C
  collapseEdge.C
  surfaceClean.C
)
add_executable(surfaceClean ${_FILES})
target_compile_features(surfaceClean PUBLIC cxx_std_11)
target_link_libraries(surfaceClean PUBLIC meshTools)
