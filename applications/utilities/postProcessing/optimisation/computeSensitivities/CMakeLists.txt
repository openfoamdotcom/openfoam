set(_FILES
  computeSensitivities.C
)
add_executable(computeSensitivities ${_FILES})
target_compile_features(computeSensitivities PUBLIC cxx_std_11)
target_link_libraries(computeSensitivities PUBLIC adjointOptimisation)
