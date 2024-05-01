set(_FILES
  sonicFoam.C
)
add_executable(sonicFoam ${_FILES})
target_compile_features(sonicFoam PUBLIC cxx_std_11)
target_link_libraries(sonicFoam PUBLIC fvOptions thermoTools)
