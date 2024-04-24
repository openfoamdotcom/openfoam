set(_FILES
  SRFSimpleFoam.C
)
add_executable(SRFSimpleFoam ${_FILES})
target_compile_features(SRFSimpleFoam PUBLIC cxx_std_11)
target_link_libraries(SRFSimpleFoam PUBLIC finiteVolume)
