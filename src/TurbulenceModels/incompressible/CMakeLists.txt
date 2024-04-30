set(_FILES
  incompressibleTurbulenceModel.C
  incompressibleRhoTurbulenceModel.C
  turbulentTransportModels/turbulentTransportModels.C
  turbulentTransportModels/RAS/qZeta/qZeta.C
  turbulentTransportModels/RAS/kkLOmega/kkLOmega.C
  turbulentTransportModels/RAS/LamBremhorstKE/LamBremhorstKE.C
  turbulentTransportModels/RAS/LienLeschziner/LienLeschziner.C
  turbulentTransportModels/RAS/ShihQuadraticKE/ShihQuadraticKE.C
  turbulentTransportModels/RAS/LienCubicKE/LienCubicKE.C
  turbulentTransportModels/derivedFvPatchFields/wallFunctions/alphatWallFunctions/alphatJayatillekeWallFunction/alphatJayatillekeWallFunctionFvPatchScalarField.C
)
add_library(incompressibleTurbulenceModels ${_FILES})
target_compile_features(incompressibleTurbulenceModels PUBLIC cxx_std_11)
target_compile_definitions(incompressibleTurbulenceModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(incompressibleTurbulenceModels PUBLIC turbulenceModels incompressibleTransportModels)
target_include_directories(incompressibleTurbulenceModels PUBLIC
  .
  turbulentTransportModels
  turbulentTransportModels/derivedFvPatchFields/wallFunctions/alphatWallFunctions/alphatJayatillekeWallFunction
  turbulentTransportModels/RAS/LienCubicKE
  turbulentTransportModels/RAS/ShihQuadraticKE
  turbulentTransportModels/RAS/LamBremhorstKE
  turbulentTransportModels/RAS/qZeta
  turbulentTransportModels/RAS/LienLeschziner
  turbulentTransportModels/RAS/kkLOmega
  IncompressibleTurbulenceModel
  ${OPENFOAM_SRC_DIR}/TurbulenceModels/phaseIncompressible/PhaseIncompressibleTurbulenceModel
)
install(TARGETS incompressibleTurbulenceModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
