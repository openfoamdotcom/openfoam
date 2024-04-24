set(_FILES
  viscosityModels/viscosityModel/viscosityModel.C
  viscosityModels/viscosityModel/viscosityModelNew.C
  viscosityModels/Newtonian/Newtonian.C
  viscosityModels/powerLaw/powerLaw.C
  viscosityModels/CrossPowerLaw/CrossPowerLaw.C
  viscosityModels/BirdCarreau/BirdCarreau.C
  viscosityModels/HerschelBulkley/HerschelBulkley.C
  viscosityModels/Casson/Casson.C
  viscosityModels/strainRateFunction/strainRateFunction.C
  viscosityModels/Arrhenius/Arrheniuss.C
  transportModel/transportModel.C
  singlePhaseTransportModel/singlePhaseTransportModel.C
  incompressibleTwoPhaseMixture/incompressibleTwoPhaseMixture.C
)
add_library(incompressibleTransportModels ${_FILES})
target_compile_features(incompressibleTransportModels PUBLIC cxx_std_11)
target_compile_definitions(incompressibleTransportModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(incompressibleTransportModels PUBLIC
  singlePhaseTransportModel
  incompressibleTwoPhaseMixture
  transportModel
  viscosityModels/Casson
  viscosityModels/Newtonian
  viscosityModels/BirdCarreau
  viscosityModels/viscosityModel
  viscosityModels/Arrhenius
  viscosityModels/HerschelBulkley
  viscosityModels/CrossPowerLaw
  viscosityModels/powerLaw
  viscosityModels/strainRateFunction
)
install(TARGETS incompressibleTransportModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
