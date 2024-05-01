set(_FILES
  equilibriumCO.C
)
add_executable(equilibriumCO ${_FILES})
target_compile_features(equilibriumCO PUBLIC cxx_std_11)
target_link_libraries(equilibriumCO PUBLIC specie)
