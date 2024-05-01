set(_FILES
  surfaceMeshConvert.C
)
add_executable(surfaceMeshConvert ${_FILES})
target_compile_features(surfaceMeshConvert PUBLIC cxx_std_11)
target_link_libraries(surfaceMeshConvert PUBLIC meshTools)
target_include_directories(surfaceMeshConvert PUBLIC
  .
)
