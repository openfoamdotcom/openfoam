set(_FILES
  writeFluentScalarField.C
  writeFluentVectorField.C
  foamDataToFluent.C
)
add_executable(foamDataToFluent ${_FILES})
target_compile_features(foamDataToFluent PUBLIC cxx_std_11)
target_link_libraries(foamDataToFluent PUBLIC genericPatchFields)
