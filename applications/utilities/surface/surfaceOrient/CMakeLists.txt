set(_FILES
  surfaceOrient.C
)
add_executable(surfaceOrient ${_FILES})
target_compile_features(surfaceOrient PUBLIC cxx_std_11)
target_link_libraries(surfaceOrient PUBLIC meshTools)
target_include_directories(surfaceOrient PUBLIC
  .
)
