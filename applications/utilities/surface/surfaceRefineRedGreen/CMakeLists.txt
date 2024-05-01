set(_FILES
  surfaceRefineRedGreen.C
)
add_executable(surfaceRefineRedGreen ${_FILES})
target_compile_features(surfaceRefineRedGreen PUBLIC cxx_std_11)
target_link_libraries(surfaceRefineRedGreen PUBLIC meshTools)
target_include_directories(surfaceRefineRedGreen PUBLIC
  .
)
