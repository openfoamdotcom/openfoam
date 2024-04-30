set(_FILES
  U/maxwellSlipUFvPatchVectorField.C
  T/smoluchowskiJumpTFvPatchScalarField.C
  rho/fixedRhoFvPatchScalarField.C
)
add_library(rhoCentralFoam ${_FILES})
target_compile_features(rhoCentralFoam PUBLIC cxx_std_11)
target_compile_definitions(rhoCentralFoam PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(rhoCentralFoam PUBLIC fluidThermophysicalModels specie)
target_include_directories(rhoCentralFoam PUBLIC
  T
  U
  rho
)
install(TARGETS rhoCentralFoam DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
