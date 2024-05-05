set(_FILES
  combustionModel/combustionModel.C
  CombustionModelCaseDir/CombustionModel/CombustionModels.C
  diffusion/diffusions.C
  infinitelyFastChemistry/infinitelyFastChemistrys.C
  PaSR/PaSRs.C
  EDC/EDCs.C
  eddyDissipationDiffusionModel/eddyDissipationDiffusionModels.C
  laminar/laminars.C
  FSD/reactionRateFlameAreaModels/consumptionSpeed/consumptionSpeed.C
  FSD/reactionRateFlameAreaModels/reactionRateFlameArea/reactionRateFlameArea.C
  FSD/reactionRateFlameAreaModels/reactionRateFlameArea/reactionRateFlameAreaNew.C
  FSD/reactionRateFlameAreaModels/relaxation/relaxation.C
  FSD/FSDs.C
  diffusionMulticomponent/diffusionMulticomponents.C
  zoneCombustion/zoneCombustions.C
  noCombustion/noCombustions.C
)
add_library(combustionModels ${_FILES})
target_compile_features(combustionModels PUBLIC cxx_std_11)
target_compile_definitions(combustionModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(combustionModels PUBLIC chemistryModel compressibleTurbulenceModels thermophysicalProperties)
target_include_directories(combustionModels PUBLIC
  .
)
install(TARGETS combustionModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
