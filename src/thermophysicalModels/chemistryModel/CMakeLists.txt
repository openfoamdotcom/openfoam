set(_FILES
  chemistryModel/basicChemistryModel/basicChemistryModel.C
  chemistryModel/BasicChemistryModelCaseDir/BasicChemistryModels.C
  chemistryModel/TDACChemistryModel/reduction/makeChemistryReductionMethods.C
  chemistryModel/TDACChemistryModel/tabulation/makeChemistryTabulationMethods.C
  chemistrySolver/chemistrySolver/makeChemistrySolvers.C
  functionObjects/specieReactionRates/specieReactionRates.C
  functionObjects/BilgerMixtureFraction/BilgerMixtureFraction.C
)
add_library(chemistryModel ${_FILES})
target_compile_features(chemistryModel PUBLIC cxx_std_11)
target_compile_definitions(chemistryModel PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(chemistryModel PUBLIC ODE reactionThermophysicalModels thermophysicalProperties)
target_include_directories(chemistryModel PUBLIC
  chemistryModel
  chemistryModel/BasicChemistryModelCaseDir
  chemistryModel/basicChemistryModel
  chemistryModel/TDACChemistryModel
  chemistryModel/TDACChemistryModel/tabulation
  chemistryModel/TDACChemistryModel/tabulation/ISAT
  chemistryModel/TDACChemistryModel/tabulation/ISAT/binaryNode
  chemistryModel/TDACChemistryModel/tabulation/ISAT/binaryTree
  chemistryModel/TDACChemistryModel/tabulation/ISAT/chemPointISAT
  chemistryModel/TDACChemistryModel/tabulation/noChemistryTabulation
  chemistryModel/TDACChemistryModel/tabulation/chemistryTabulationMethod
  chemistryModel/TDACChemistryModel/reduction
  chemistryModel/TDACChemistryModel/reduction/DRGEP
  chemistryModel/TDACChemistryModel/reduction/DRG
  chemistryModel/TDACChemistryModel/reduction/PFA
  chemistryModel/TDACChemistryModel/reduction/chemistryReductionMethod
  chemistryModel/TDACChemistryModel/reduction/DAC
  chemistryModel/TDACChemistryModel/reduction/noChemistryReduction
  chemistryModel/TDACChemistryModel/reduction/EFA
  chemistryModel/StandardChemistryModel
  chemistrySolver/noChemistrySolver
  chemistrySolver/chemistrySolver
  chemistrySolver/ode
  chemistrySolver/EulerImplicit
  functionObjects/BilgerMixtureFraction
  functionObjects/specieReactionRates
)
install(TARGETS chemistryModel DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)