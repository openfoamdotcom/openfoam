set(_FILES
  sonicLiquidFoam.C
)
add_executable(sonicLiquidFoam ${_FILES})
target_compile_features(sonicLiquidFoam PUBLIC cxx_std_11)
target_link_libraries(sonicLiquidFoam PUBLIC finiteVolume meshTools)
target_include_directories(sonicLiquidFoam PUBLIC
  .
)
