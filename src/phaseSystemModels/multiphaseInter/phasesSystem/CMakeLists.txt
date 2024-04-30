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
target_link_libraries(incompressibleMultiphaseSystems PUBLIC incompressibleTransportModels geometricVoF twoPhaseProperties combustionModels saturationModel)
target_include_directories(incompressibleMultiphaseSystems PUBLIC
  InterfaceCompositionModelCaseDir
  MassTransferPhaseSystem
  derivedFvPatchFields/timeVaryingMassSorption
  interfaceCompositionModel
  interfaceModels/porousModels/VollerPrakash
  interfaceModels/porousModels/porousModel
  interfaceModels/surfaceTensionModels/constantSurfaceTensionCoefficient
  interfaceModels/surfaceTensionModels/surfaceTensionModel
  massTransferModels/Lee
  massTransferModels/diffusionGasEvaporation
  massTransferModels/interfaceHeatResistance
  massTransferModels/interfaceOxideRate
  massTransferModels/kineticGasEvaporation
  multiphaseInterSystem
  multiphaseSystem
  phaseModel/MovingPhaseModel
  phaseModel/MultiComponentPhaseModel
  phaseModel/PurePhaseModel
  phaseModel/StaticPhaseModel
  phaseModel/phaseModel
  phasePair
)
install(TARGETS incompressibleMultiphaseSystems DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
