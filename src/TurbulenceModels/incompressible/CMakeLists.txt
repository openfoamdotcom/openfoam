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
set_property(TARGET incompressibleTurbulenceModels PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(incompressibleTurbulenceModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(incompressibleTurbulenceModels PUBLIC incompressibleTransportModels turbulenceModels)
target_include_directories(incompressibleTurbulenceModels PUBLIC
  .
)
install(TARGETS incompressibleTurbulenceModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
