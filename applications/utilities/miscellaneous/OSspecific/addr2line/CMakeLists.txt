set(_FILES
  addr2line.C
)
add_executable(addr2line ${_FILES})
target_compile_features(addr2line PUBLIC cxx_std_11)
target_link_libraries(addr2line PUBLIC finiteVolume)
