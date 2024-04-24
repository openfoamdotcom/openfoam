set(_FILES
  surfaceInflate.C
)
add_executable(surfaceInflate ${_FILES})
target_compile_features(surfaceInflate PUBLIC cxx_std_11)
target_link_libraries(surfaceInflate PUBLIC finiteVolume)
