set(_FILES
  Test-DictionaryCaseDir.C
)
add_executable(Test-DictionaryCaseDir ${_FILES})
target_compile_features(Test-DictionaryCaseDir PUBLIC cxx_std_11)
target_link_libraries(Test-DictionaryCaseDir PUBLIC finiteVolume)
