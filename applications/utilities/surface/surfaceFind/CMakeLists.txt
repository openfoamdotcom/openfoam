set(_FILES
  surfaceFind.C
)
add_executable(surfaceFind ${_FILES})
target_compile_features(surfaceFind PUBLIC cxx_std_11)
target_link_libraries(surfaceFind PUBLIC surfMesh)
