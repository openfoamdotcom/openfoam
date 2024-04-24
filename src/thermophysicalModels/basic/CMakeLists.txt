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
target_compile_definitions(fluidThermophysicalModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(fluidThermophysicalModels PUBLIC
  derivedFvPatchFields/energyJump/energyJump
  derivedFvPatchFields/energyJump/energyJumpAMI
  derivedFvPatchFields/fixedEnergy
  derivedFvPatchFields/gradientEnergy
  derivedFvPatchFields/mixedEnergy
  rhoThermo
  mixtures/basicMixture
  mixtures/pureZoneMixture
  mixtures/pureMixture
  fluidThermo
  psiThermo
  basicThermo
  heThermo
)
install(TARGETS fluidThermophysicalModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
