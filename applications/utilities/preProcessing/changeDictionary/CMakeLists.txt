set(_FILES
  changeDictionary.C
)
add_executable(changeDictionary ${_FILES})
target_compile_features(changeDictionary PUBLIC cxx_std_11)
target_link_libraries(changeDictionary PUBLIC finiteVolume)
