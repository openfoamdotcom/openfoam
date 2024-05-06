set(_FILES
  phaseModel/phaseModel.C
  alphaContactAngle/alphaContactAngleFvPatchScalarField.C
  multiphaseMixtureThermo.C
)
add_library(multiphaseMixtureThermo ${_FILES})
target_compile_features(multiphaseMixtureThermo PUBLIC cxx_std_11)
set_property(TARGET multiphaseMixtureThermo PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(multiphaseMixtureThermo PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(multiphaseMixtureThermo PUBLIC finiteVolume fluidThermophysicalModels meshTools specie)
target_include_directories(multiphaseMixtureThermo PUBLIC
  .
)
install(TARGETS multiphaseMixtureThermo DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
