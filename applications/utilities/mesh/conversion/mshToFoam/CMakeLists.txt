set(_FILES
  mshToFoam.C
)
add_executable(mshToFoam ${_FILES})
target_compile_features(mshToFoam PUBLIC cxx_std_11)
target_link_libraries(mshToFoam PUBLIC finiteVolume)
