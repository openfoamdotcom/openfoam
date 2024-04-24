set(_FILES
  edgeStats.C
  selectCells.C
)
add_executable(selectCells ${_FILES})
target_compile_features(selectCells PUBLIC cxx_std_11)
target_link_libraries(selectCells PUBLIC finiteVolume)
