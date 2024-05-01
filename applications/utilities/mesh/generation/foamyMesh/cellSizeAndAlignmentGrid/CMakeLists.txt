set(_FILES
  cellSizeAndAlignmentGrid.C
)
add_executable(cellSizeAndAlignmentGrid ${_FILES})
target_compile_features(cellSizeAndAlignmentGrid PUBLIC cxx_std_11)
target_link_libraries(cellSizeAndAlignmentGrid PUBLIC conformalVoronoiMesh dynamicMesh metisDecomp ptscotchDecomp)
if (KAHIP_FOUND)
  target_link_libraries(cellSizeAndAlignmentGrid PUBLIC kahipDecomp)
endif()
if (SCOTCH_FOUND)
  target_link_libraries(cellSizeAndAlignmentGrid PUBLIC scotchDecomp)
endif()
target_include_directories(cellSizeAndAlignmentGrid PUBLIC
  .
)
