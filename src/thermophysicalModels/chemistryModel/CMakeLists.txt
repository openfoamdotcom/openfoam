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
set_property(TARGET chemistryModel PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(chemistryModel PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(chemistryModel PUBLIC ODE reactionThermophysicalModels thermophysicalProperties)
target_include_directories(chemistryModel PUBLIC
  .
)
install(TARGETS chemistryModel DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
