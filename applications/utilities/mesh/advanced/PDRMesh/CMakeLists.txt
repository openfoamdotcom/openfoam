set(_FILES
  PDRMesh.C
)
add_executable(PDRMesh ${_FILES})
target_compile_features(PDRMesh PUBLIC cxx_std_11)
target_link_libraries(PDRMesh PUBLIC fluidThermophysicalModels fvOptions thermoTools)
target_include_directories(PDRMesh PUBLIC
  .
)
