set(_FILES
  foamListTimes.C
)
add_executable(foamListTimes ${_FILES})
target_compile_features(foamListTimes PUBLIC cxx_std_11)
target_include_directories(foamListTimes PUBLIC
  .
)
