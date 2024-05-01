set(_FILES
  surfaceCoarsen.C
)
add_executable(surfaceCoarsen ${_FILES})
target_compile_features(surfaceCoarsen PUBLIC cxx_std_11)
target_link_libraries(surfaceCoarsen PUBLIC surfMesh)
