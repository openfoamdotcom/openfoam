set(_FILES
  surfaceAdd.C
)
add_executable(surfaceAdd ${_FILES})
target_compile_features(surfaceAdd PUBLIC cxx_std_11)
target_link_libraries(surfaceAdd PUBLIC surfMesh)
target_include_directories(surfaceAdd PUBLIC
  .
)
