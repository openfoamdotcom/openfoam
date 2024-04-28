set(_FILES
  chemistryReaders/chemkinReader/chemkinReader.C
  chemistryReaders/chemistryReader/makeChemistryReaders.C
  mixtures/basicMultiComponentMixture/basicMultiComponentMixture.C
  mixtures/basicSpecieMixture/basicSpecieMixture.C
  mixtures/basicCombustionMixture/basicCombustionMixture.C
  psiReactionThermo/psiReactionThermo.C
  psiReactionThermo/psiReactionThermos.C
  psiuReactionThermo/psiuReactionThermo.C
  psiuReactionThermo/psiuReactionThermos.C
  rhoReactionThermo/rhoReactionThermo.C
  rhoReactionThermo/rhoReactionThermos.C
  derivedFvPatchFields/fixedUnburntEnthalpy/fixedUnburntEnthalpyFvPatchScalarField.C
  derivedFvPatchFields/gradientUnburntEnthalpy/gradientUnburntEnthalpyFvPatchScalarField.C
  derivedFvPatchFields/mixedUnburntEnthalpy/mixedUnburntEnthalpyFvPatchScalarField.C
  derivedFvPatchFields/speciesSorption/speciesSorptionFvPatchScalarField.C
  derivedFvPatchFields/enthalpySorption/enthalpySorptionFvPatchScalarField.C
  derivedFvPatchFields/boundarySourcePatch/boundarySourcePatch.C
  functionObjects/moleFractions/moleFractionsFunctionObjects.C
)
set(_flex_src ${CMAKE_CURRENT_BINARY_DIR}/chemkinLexer.C)
flex_target(MyFlexName chemistryReaders/chemkinReader/chemkinLexer.L "${_flex_src}" COMPILE_FLAGS --c++)
add_library(reactionThermophysicalModels ${_FILES} ${_flex_src})
target_compile_features(reactionThermophysicalModels PUBLIC cxx_std_11)
target_compile_definitions(reactionThermophysicalModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(reactionThermophysicalModels PUBLIC fluidThermophysicalModels solidSpecie thermophysicalProperties specie)
target_include_directories(reactionThermophysicalModels PUBLIC
  .
  derivedFvPatchFields/gradientUnburntEnthalpy
  derivedFvPatchFields/boundarySourcePatch
  derivedFvPatchFields/fixedUnburntEnthalpy
  derivedFvPatchFields/mixedUnburntEnthalpy
  derivedFvPatchFields/speciesSorption
  derivedFvPatchFields/enthalpySorption
  chemistryReaders/chemistryReader
  chemistryReaders/foamChemistryReader
  chemistryReaders/chemkinReader
  functionObjects/moleFractions
  psiReactionThermo
  mixtures/basicMultiComponentMixture
  mixtures/veryInhomogeneousMixture
  mixtures/multiComponentMixture
  mixtures/basicCombustionMixture
  mixtures/basicSpecieMixture
  mixtures/reactingMixture
  mixtures/SpecieMixture
  mixtures/egrMixture
  mixtures/homogeneousMixture
  mixtures/singleStepReactingMixture
  mixtures/inhomogeneousMixture
  mixtures/singleComponentMixture
  rhoReactionThermo
  psiuReactionThermo
)
install(TARGETS reactionThermophysicalModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
