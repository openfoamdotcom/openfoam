set(_FILES
  interfaceTrackingFvMesh.C
  freeSurfacePointDisplacement.C
  fvPatchFields/freeSurfacePressure/freeSurfacePressureFvPatchScalarField.C
  fvPatchFields/freeSurfaceVelocity/freeSurfaceVelocityFvPatchVectorField.C
  functionObjects/pointHistory/pointHistory.C
  functionObjects/writeFreeSurface/writeFreeSurface.C
)
add_library(interfaceTrackingFvMesh ${_FILES})
target_compile_features(interfaceTrackingFvMesh PUBLIC cxx_std_11)
target_compile_definitions(interfaceTrackingFvMesh PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(interfaceTrackingFvMesh PUBLIC finiteArea fvMotionSolvers dynamicMesh)
target_include_directories(interfaceTrackingFvMesh PUBLIC
  .
  fvPatchFields/freeSurfaceVelocity
  fvPatchFields/freeSurfacePressure
  functionObjects/writeFreeSurface
  functionObjects/pointHistory
)
install(TARGETS interfaceTrackingFvMesh DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
