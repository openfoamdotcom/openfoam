set(_FILES
  chemkinToFoam.C
)
add_executable(chemkinToFoam ${_FILES})
target_compile_features(chemkinToFoam PUBLIC cxx_std_11)
target_link_libraries(chemkinToFoam PUBLIC finiteVolume)
