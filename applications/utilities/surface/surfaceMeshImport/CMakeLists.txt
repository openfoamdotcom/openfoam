set(_FILES
  surfaceMeshImport.C
)
add_executable(surfaceMeshImport ${_FILES})
target_compile_features(surfaceMeshImport PUBLIC cxx_std_11)
target_link_libraries(surfaceMeshImport PUBLIC finiteVolume)
