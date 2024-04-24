set(_FILES
  combinePatchFaces.C
)
add_executable(combinePatchFaces ${_FILES})
target_compile_features(combinePatchFaces PUBLIC cxx_std_11)
target_link_libraries(combinePatchFaces PUBLIC finiteVolume)
