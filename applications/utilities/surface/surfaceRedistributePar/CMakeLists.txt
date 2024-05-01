set(_FILES
  surfaceRedistributePar.C
)
add_executable(surfaceRedistributePar ${_FILES})
target_compile_features(surfaceRedistributePar PUBLIC cxx_std_11)
target_link_libraries(surfaceRedistributePar PUBLIC distributed decompose)
