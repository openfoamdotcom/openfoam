set(_FILES
  splitCells.C
)
add_executable(splitCells ${_FILES})
target_compile_features(splitCells PUBLIC cxx_std_11)
target_link_libraries(splitCells PUBLIC finiteVolume)
