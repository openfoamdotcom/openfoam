set(_FILES
  foamToGMV.C
  itoa.C
)
add_executable(foamToGMV ${_FILES})
target_compile_features(foamToGMV PUBLIC cxx_std_11)
target_link_libraries(foamToGMV PUBLIC finiteVolume)
