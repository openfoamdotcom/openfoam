set(_FILES
  surfaceMeshExtract.C
)
add_executable(surfaceMeshExtract ${_FILES})
target_compile_features(surfaceMeshExtract PUBLIC cxx_std_11)
target_link_libraries(surfaceMeshExtract PUBLIC meshTools)
