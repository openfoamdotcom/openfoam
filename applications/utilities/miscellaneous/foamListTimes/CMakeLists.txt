set(_FILES
  foamListTimes.C
)
add_executable(foamListTimes ${_FILES})
target_compile_features(foamListTimes PUBLIC cxx_std_11)
target_link_libraries(foamListTimes PUBLIC finiteVolume)
