set(_FILES
  smoothSurfaceData.C
)
add_executable(smoothSurfaceData ${_FILES})
target_compile_features(smoothSurfaceData PUBLIC cxx_std_11)
target_link_libraries(smoothSurfaceData PUBLIC finiteVolume)
