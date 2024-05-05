set(_FILES
  snappyHexMeshDriver/snappyLayerDriver.C
  snappyHexMeshDriver/snappyLayerDriverSinglePass.C
  snappyHexMeshDriver/snappySnapDriver.C
  snappyHexMeshDriver/snappySnapDriverFeature.C
  snappyHexMeshDriver/snappyRefineDriver.C
  snappyHexMeshDriver/snappyVoxelMeshDriver.C
  snappyHexMeshDriver/layerParameters/layerParameters.C
  snappyHexMeshDriver/refinementParameters/refinementParameters.C
  snappyHexMeshDriver/snapParameters/snapParameters.C
  meshRefinement/meshRefinementBaffles.C
  meshRefinement/meshRefinement.C
  meshRefinement/meshRefinementMerge.C
  meshRefinement/meshRefinementProblemCells.C
  meshRefinement/meshRefinementRefine.C
  meshRefinement/meshRefinementGapRefine.C
  meshRefinement/meshRefinementBlock.C
  meshRefinement/wallPoints.C
  meshRefinement/patchFaceOrientation.C
  meshRefinement/weightedPosition.C
  refinementFeatures/refinementFeatures.C
  refinementSurfaces/surfaceZonesInfo.C
  refinementSurfaces/refinementSurfaces.C
  shellSurfaces/shellSurfaces.C
  trackedParticle/trackedParticle.C
  trackedParticle/trackedParticleCloud.C
  externalDisplacementMeshMover/displacementMeshMoverMotionSolver.C
  externalDisplacementMeshMover/externalDisplacementMeshMover.C
  externalDisplacementMeshMover/medialAxisMeshMover.C
  externalDisplacementMeshMover/displacementMotionSolverMeshMover.C
  externalDisplacementMeshMover/zeroFixedValue/zeroFixedValuePointPatchFields.C
  externalDisplacementMeshMover/fieldSmoother/fieldSmoother.C
)
add_library(snappyHexMeshLib ${_FILES})
target_compile_features(snappyHexMeshLib PUBLIC cxx_std_11)
target_compile_definitions(snappyHexMeshLib PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(snappyHexMeshLib PUBLIC decompositionMethods distributed fvMotionSolvers overset)
set_target_properties(snappyHexMeshLib PROPERTIES OUTPUT_NAME snappyHexMesh)
target_include_directories(snappyHexMeshLib PUBLIC
  .
)
install(TARGETS snappyHexMeshLib DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
