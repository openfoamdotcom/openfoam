set(_FILES
  foamHelp.C
)
add_executable(foamHelp ${_FILES})
target_compile_features(foamHelp PUBLIC cxx_std_11)
target_link_libraries(foamHelp PUBLIC fluidThermophysicalModels helpTypes incompressibleTurbulenceModels radiationModels thermoTools)
target_include_directories(foamHelp PUBLIC
  .
)
