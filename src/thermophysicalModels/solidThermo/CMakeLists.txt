set(_FILES
  solidThermo/solidThermo.C
  solidThermo/solidThermos.C
  solidReactionThermo/solidReactionThermo.C
  solidReactionThermo/solidReactionThermos.C
  solidThermo/heZoneSolidThermos.C
)
add_library(solidThermo ${_FILES})
target_compile_features(solidThermo PUBLIC cxx_std_11)
set_property(TARGET solidThermo PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(solidThermo PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(solidThermo PUBLIC compressibleTransportModels reactionThermophysicalModels thermophysicalProperties)
target_include_directories(solidThermo PUBLIC
  .
)
install(TARGETS solidThermo DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
