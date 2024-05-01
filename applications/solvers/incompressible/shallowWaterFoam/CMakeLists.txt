set(_FILES
  shallowWaterFoam.C
)
add_executable(shallowWaterFoam ${_FILES})
target_compile_features(shallowWaterFoam PUBLIC cxx_std_11)
target_link_libraries(shallowWaterFoam PUBLIC finiteVolume meshTools)
target_include_directories(shallowWaterFoam PUBLIC
  .
)
