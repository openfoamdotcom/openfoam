set(_FILES
  surfacePointMerge.C
)
add_executable(surfacePointMerge ${_FILES})
target_compile_features(surfacePointMerge PUBLIC cxx_std_11)
target_link_libraries(surfacePointMerge PUBLIC meshTools)
