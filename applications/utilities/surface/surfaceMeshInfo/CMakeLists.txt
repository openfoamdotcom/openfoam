set(_FILES
  surfaceMeshInfo.C
)
add_executable(surfaceMeshInfo ${_FILES})
target_compile_features(surfaceMeshInfo PUBLIC cxx_std_11)
target_link_libraries(surfaceMeshInfo PUBLIC meshTools)
