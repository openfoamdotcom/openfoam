set(_FILES
  surfaceInertia.C
)
add_executable(surfaceInertia ${_FILES})
target_compile_features(surfaceInertia PUBLIC cxx_std_11)
target_link_libraries(surfaceInertia PUBLIC meshTools)
target_include_directories(surfaceInertia PUBLIC
  .
)
