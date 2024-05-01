set(_FILES
  calcRadiusField.C
)
add_executable(calcRadiusField ${_FILES})
target_compile_features(calcRadiusField PUBLIC cxx_std_11)
target_link_libraries(calcRadiusField PUBLIC finiteVolume)
target_include_directories(calcRadiusField PUBLIC
  .
)
