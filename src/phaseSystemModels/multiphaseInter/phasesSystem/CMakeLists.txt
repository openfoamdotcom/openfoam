set(_FILES
  phaseModel/phaseModel/phaseModel.C
  phaseModel/phaseModel/phaseModels.C
  phasePair/phasePair.C
  phasePair/phasePairKey.C
  phasePair/orderedPhasePair.C
  multiphaseInterSystem/multiphaseInterSystem.C
  multiphaseSystem/multiphaseSystem.C
  multiphaseSystem/multiphaseSystemNew.C
  multiphaseSystem/multiphaseSystems.C
  interfaceCompositionModel/interfaceCompositionModel.C
  InterfaceCompositionModelCaseDir/InterfaceCompositionModels.C
  interfaceModels/porousModels/porousModel/porousModel.C
  interfaceModels/porousModels/VollerPrakash/VollerPrakash.C
  interfaceModels/surfaceTensionModels/surfaceTensionModel/surfaceTensionModel.C
  interfaceModels/surfaceTensionModels/constantSurfaceTensionCoefficient/constantSurfaceTensionCoefficient.C
  derivedFvPatchFields/timeVaryingMassSorption/timeVaryingMassSorptionFvPatchScalarField.C
)
add_library(incompressibleMultiphaseSystems ${_FILES})
target_compile_features(incompressibleMultiphaseSystems PUBLIC cxx_std_11)
target_compile_definitions(incompressibleMultiphaseSystems PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(incompressibleMultiphaseSystems PUBLIC 
  MassTransferPhaseSystem
  derivedFvPatchFields/timeVaryingMassSorption
  multiphaseSystem
  massTransferModels/diffusionGasEvaporation
  massTransferModels/Lee
  massTransferModels/interfaceOxideRate
  massTransferModels/kineticGasEvaporation
  massTransferModels/interfaceHeatResistance
  phasePair
  InterfaceCompositionModelCaseDir
  interfaceModels/porousModels/porousModel
  interfaceModels/porousModels/VollerPrakash
  interfaceModels/surfaceTensionModels/constantSurfaceTensionCoefficient
  interfaceModels/surfaceTensionModels/surfaceTensionModel
  phaseModel/MultiComponentPhaseModel
  phaseModel/PurePhaseModel
  phaseModel/StaticPhaseModel
  phaseModel/phaseModel
  phaseModel/MovingPhaseModel
  interfaceCompositionModel
  multiphaseInterSystem
)
install(TARGETS incompressibleMultiphaseSystems DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
