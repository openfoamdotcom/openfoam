set(_FILES
  basicThermo/basicThermo.C
  fluidThermo/fluidThermo.C
  psiThermo/psiThermo.C
  psiThermo/psiThermos.C
  psiThermo/psiZoneThermos.C
  rhoThermo/rhoThermo.C
  rhoThermo/rhoThermos.C
  rhoThermo/liquidThermo.C
  rhoThermo/rhoZoneThermos.C
  derivedFvPatchFields/fixedEnergy/fixedEnergyFvPatchScalarField.C
  derivedFvPatchFields/gradientEnergy/gradientEnergyFvPatchScalarField.C
  derivedFvPatchFields/mixedEnergy/mixedEnergyFvPatchScalarField.C
  derivedFvPatchFields/energyJump/energyJump/energyJumpFvPatchScalarField.C
  derivedFvPatchFields/energyJump/energyJumpAMI/energyJumpAMIFvPatchScalarField.C
)
add_library(fluidThermophysicalModels ${_FILES})
target_compile_features(fluidThermophysicalModels PUBLIC cxx_std_11)
set_property(TARGET fluidThermophysicalModels PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(fluidThermophysicalModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(fluidThermophysicalModels PUBLIC compressibleTransportModels thermophysicalProperties)
target_include_directories(fluidThermophysicalModels PUBLIC
  .
  PRIVATE
  ${OPENFOAM_SRC_DIR}/regionModels/pyrolysisModels
  ${OPENFOAM_SRC_DIR}/regionModels/regionModel
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/chemistryModel
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/radiation
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/reactionThermo
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/solidChemistryModel
  ${OPENFOAM_SRC_DIR}/thermophysicalModels/solidThermo
)
install(TARGETS fluidThermophysicalModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
