set(_FILES
  VoFphaseTurbulentTransportModels.C
)
add_library(VoFphaseTurbulentTransportModels ${_FILES})
target_compile_features(VoFphaseTurbulentTransportModels PUBLIC cxx_std_11)
set_property(TARGET VoFphaseTurbulentTransportModels PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(VoFphaseTurbulentTransportModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(VoFphaseTurbulentTransportModels PUBLIC fluidThermophysicalModels incompressibleTurbulenceModels specie)
target_include_directories(VoFphaseTurbulentTransportModels PUBLIC
  .
  PRIVATE
  ${OPENFOAM_SRC_DIR}/
)
install(TARGETS VoFphaseTurbulentTransportModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
