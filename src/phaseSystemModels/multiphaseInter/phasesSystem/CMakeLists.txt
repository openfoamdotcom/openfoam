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
set_property(TARGET incompressibleMultiphaseSystems PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(incompressibleMultiphaseSystems PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(incompressibleMultiphaseSystems PUBLIC combustionModels geometricVoF incompressibleTransportModels saturationModel twoPhaseProperties)
target_include_directories(incompressibleMultiphaseSystems PUBLIC
  .
)
install(TARGETS incompressibleMultiphaseSystems DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
