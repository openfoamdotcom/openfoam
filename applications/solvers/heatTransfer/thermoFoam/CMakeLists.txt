set(_FILES
  thermoFoam.C
)
add_executable(thermoFoam ${_FILES})
target_compile_features(thermoFoam PUBLIC cxx_std_11)
target_link_libraries(thermoFoam PUBLIC fvOptions thermoTools)
target_include_directories(thermoFoam PUBLIC
  .
)
