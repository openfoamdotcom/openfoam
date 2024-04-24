set(_FILES
  foamListRegions.C
)
add_executable(foamListRegions ${_FILES})
target_compile_features(foamListRegions PUBLIC cxx_std_11)
target_link_libraries(foamListRegions PUBLIC finiteVolume)
