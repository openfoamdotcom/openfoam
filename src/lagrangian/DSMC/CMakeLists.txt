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
target_compile_definitions(DSMC PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(DSMC PUBLIC finiteVolume lagrangian)
target_include_directories(DSMC PUBLIC
  clouds/Templates/DSMCCloud
  clouds/baseClasses/DSMCBaseCloud
  parcels/Templates/DSMCParcel
  parcels/derived/dsmcParcel
  submodels/BinaryCollisionModel/BinaryCollisionModel
  submodels/BinaryCollisionModel/LarsenBorgnakkeVariableHardSphere
  submodels/BinaryCollisionModel/NoBinaryCollision
  submodels/BinaryCollisionModel/VariableHardSphere
  submodels/InflowBoundaryModel/FreeStream
  submodels/InflowBoundaryModel/InflowBoundaryModel
  submodels/InflowBoundaryModel/NoInflow
  submodels/WallInteractionModel/MaxwellianThermal
  submodels/WallInteractionModel/MixedDiffuseSpecular
  submodels/WallInteractionModel/SpecularReflection
  submodels/WallInteractionModel/WallInteractionModel
  clouds/derived/dsmcCloud
)
install(TARGETS DSMC DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
