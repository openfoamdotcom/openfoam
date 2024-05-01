set(_FILES
  postProcess.C
)
add_executable(postProcess ${_FILES})
target_compile_features(postProcess PUBLIC cxx_std_11)
target_link_libraries(postProcess PUBLIC fvOptions incompressibleTurbulenceModels thermoTools incompressibleTransportModels fluidThermophysicalModels specie genericPatchFields)
