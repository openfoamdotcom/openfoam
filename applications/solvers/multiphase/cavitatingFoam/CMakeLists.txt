set(_FILES
  cavitatingFoam.C
)
add_executable(cavitatingFoam ${_FILES})
target_compile_features(cavitatingFoam PUBLIC cxx_std_11)
target_link_libraries(cavitatingFoam PUBLIC barotropicCompressibilityModel fvOptions incompressibleTurbulenceModels interfaceProperties)
target_include_directories(cavitatingFoam PUBLIC
  .
)
