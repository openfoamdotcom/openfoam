set(_FILES
  noise.C
)
add_executable(noise ${_FILES})
target_compile_features(noise PUBLIC cxx_std_11)
target_link_libraries(noise PUBLIC randomProcesses)
