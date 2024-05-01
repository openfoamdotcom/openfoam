set(_FILES
  relativeVelocityModel/relativeVelocityModel.C
  simple/simple.C
  general/general.C
)
add_library(driftFluxRelativeVelocityModels ${_FILES})
target_compile_features(driftFluxRelativeVelocityModels PUBLIC cxx_std_11)
target_compile_definitions(driftFluxRelativeVelocityModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(driftFluxRelativeVelocityModels PUBLIC finiteVolume incompressibleTransportModels meshTools)
target_include_directories(driftFluxRelativeVelocityModels PUBLIC
  general
  relativeVelocityModel
  simple
)
install(TARGETS driftFluxRelativeVelocityModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
