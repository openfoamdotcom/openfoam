set(_FILES
  writeMorpherCPs.C
)
add_executable(writeMorpherCPs ${_FILES})
target_compile_features(writeMorpherCPs PUBLIC cxx_std_11)
target_link_libraries(writeMorpherCPs PUBLIC finiteVolume)
