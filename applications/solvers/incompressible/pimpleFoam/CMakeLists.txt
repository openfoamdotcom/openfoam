set(_FILES
  pimpleFoam.C
)
add_executable(pimpleFoam ${_FILES})
target_compile_features(pimpleFoam PUBLIC cxx_std_11)
target_link_libraries(pimpleFoam PUBLIC finiteVolume)
