set(_FILES
  parcels/derived/dsmcParcel/dsmcParcel.C
  clouds/baseClasses/DSMCBaseCloud/DSMCBaseCloud.C
  parcels/derived/dsmcParcel/defineDSMCParcel.C
  parcels/derived/dsmcParcel/makeDSMCParcelBinaryCollisionModels.C
  parcels/derived/dsmcParcel/makeDSMCParcelWallInteractionModels.C
  parcels/derived/dsmcParcel/makeDSMCParcelInflowBoundaryModels.C
)
add_library(DSMC ${_FILES})
target_compile_features(DSMC PUBLIC cxx_std_11)
set_property(TARGET DSMC PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(DSMC PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(DSMC PUBLIC finiteVolume lagrangian)
target_include_directories(DSMC PUBLIC
  .
)
install(TARGETS DSMC DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
