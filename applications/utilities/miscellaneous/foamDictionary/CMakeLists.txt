set(_FILES
  foamDictionary.C
)
add_executable(foamDictionary ${_FILES})
target_compile_features(foamDictionary PUBLIC cxx_std_11)
target_link_libraries(foamDictionary PUBLIC finiteVolume)
