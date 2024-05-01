set(_FILES
  equilibriumFlameT.C
)
add_executable(equilibriumFlameT ${_FILES})
target_compile_features(equilibriumFlameT PUBLIC cxx_std_11)
target_link_libraries(equilibriumFlameT PUBLIC specie)
target_include_directories(equilibriumFlameT PUBLIC
  .
)
