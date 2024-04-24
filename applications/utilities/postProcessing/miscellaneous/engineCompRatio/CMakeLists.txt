set(_FILES
  engineCompRatio.C
)
add_executable(engineCompRatio ${_FILES})
target_compile_features(engineCompRatio PUBLIC cxx_std_11)
target_link_libraries(engineCompRatio PUBLIC finiteVolume)
