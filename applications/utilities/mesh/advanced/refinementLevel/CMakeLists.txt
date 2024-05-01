set(_FILES
  refinementLevel.C
)
add_executable(refinementLevel ${_FILES})
target_compile_features(refinementLevel PUBLIC cxx_std_11)
target_link_libraries(refinementLevel PUBLIC finiteVolume meshTools)
target_include_directories(refinementLevel PUBLIC
  .
)
