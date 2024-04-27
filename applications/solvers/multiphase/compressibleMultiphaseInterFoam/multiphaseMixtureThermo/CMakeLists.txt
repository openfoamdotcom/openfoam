set(_FILES
  phaseModel/phaseModel.C
  alphaContactAngle/alphaContactAngleFvPatchScalarField.C
  multiphaseMixtureThermo.C
)
add_library(multiphaseMixtureThermo ${_FILES})
target_compile_features(multiphaseMixtureThermo PUBLIC cxx_std_11)
target_compile_definitions(multiphaseMixtureThermo PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(multiphaseMixtureThermo PUBLIC fluidThermophysicalModels specie finiteVolume meshTools)
target_include_directories(multiphaseMixtureThermo PUBLIC
  .
  alphaContactAngle
  phaseModel
)
install(TARGETS multiphaseMixtureThermo DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
