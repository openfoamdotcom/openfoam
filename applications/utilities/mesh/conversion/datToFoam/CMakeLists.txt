set(_FILES
  datToFoam.C
)
add_executable(datToFoam ${_FILES})
target_compile_features(datToFoam PUBLIC cxx_std_11)
target_link_libraries(datToFoam PUBLIC finiteVolume)
