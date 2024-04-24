set(_FILES
  dnsFoam.C
)
add_executable(dnsFoam ${_FILES})
target_compile_features(dnsFoam PUBLIC cxx_std_11)
target_link_libraries(dnsFoam PUBLIC finiteVolume)
