set(_FILES
  surfaceMeshExport.C
)
add_executable(surfaceMeshExport ${_FILES})
target_compile_features(surfaceMeshExport PUBLIC cxx_std_11)
target_link_libraries(surfaceMeshExport PUBLIC meshTools)
target_include_directories(surfaceMeshExport PUBLIC
  .
)
