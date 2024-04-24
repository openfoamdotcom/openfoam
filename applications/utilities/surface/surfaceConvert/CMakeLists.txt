set(_FILES
  surfaceConvert.C
)
add_executable(surfaceConvert ${_FILES})
target_compile_features(surfaceConvert PUBLIC cxx_std_11)
target_link_libraries(surfaceConvert PUBLIC finiteVolume)
