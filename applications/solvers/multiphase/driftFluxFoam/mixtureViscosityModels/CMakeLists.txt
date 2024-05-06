set(_FILES
  mixtureViscosityModel/mixtureViscosityModel.C
  mixtureViscosityModel/mixtureViscosityModelNew.C
  plastic/plastic.C
  BinghamPlastic/BinghamPlastic.C
  slurry/slurry.C
)
add_library(driftFluxTransportModels ${_FILES})
target_compile_features(driftFluxTransportModels PUBLIC cxx_std_11)
set_property(TARGET driftFluxTransportModels PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(driftFluxTransportModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(driftFluxTransportModels PUBLIC finiteVolume incompressibleTransportModels)
target_include_directories(driftFluxTransportModels PUBLIC
  .
)
install(TARGETS driftFluxTransportModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
