set(_FILES
  temporalInterpolate.C
)
add_executable(temporalInterpolate ${_FILES})
target_compile_features(temporalInterpolate PUBLIC cxx_std_11)
target_link_libraries(temporalInterpolate PUBLIC finiteVolume)
target_include_directories(temporalInterpolate PUBLIC
  .
)
