set(_FILES
  faceAgglomerate.C
)
add_executable(faceAgglomerate ${_FILES})
target_compile_features(faceAgglomerate PUBLIC cxx_std_11)
target_link_libraries(faceAgglomerate PUBLIC finiteVolume)
