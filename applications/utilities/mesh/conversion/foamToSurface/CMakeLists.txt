set(_FILES
  foamToSurface.C
)
add_executable(foamToSurface ${_FILES})
target_compile_features(foamToSurface PUBLIC cxx_std_11)
target_link_libraries(foamToSurface PUBLIC finiteVolume)
