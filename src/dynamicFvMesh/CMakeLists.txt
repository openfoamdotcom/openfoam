set(_FILES
  dynamicFvMesh/dynamicFvMesh.C
  dynamicFvMesh/dynamicFvMeshNew.C
  staticFvMesh/staticFvMesh.C
  dynamicMotionSolverFvMesh/dynamicMotionSolverFvMesh.C
  dynamicMultiMotionSolverFvMesh/dynamicMultiMotionSolverFvMesh.C
  dynamicInkJetFvMesh/dynamicInkJetFvMesh.C
  dynamicRefineFvMesh/dynamicRefineFvMesh.C
  dynamicMotionSolverListFvMesh/dynamicMotionSolverListFvMesh.C
  simplifiedDynamicFvMesh/simplifiedDynamicFvMeshes.C
  simplifiedDynamicFvMesh/simplifiedDynamicFvMesh.C
  dynamicMotionSolverFvMeshAMI/dynamicMotionSolverFvMeshAMI.C
)
add_library(dynamicFvMesh ${_FILES})
target_compile_features(dynamicFvMesh PUBLIC cxx_std_11)
target_compile_definitions(dynamicFvMesh PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(dynamicFvMesh PUBLIC dynamicMesh)
target_include_directories(dynamicFvMesh PUBLIC
  include
  dynamicFvMesh
  dynamicInkJetFvMesh
  dynamicMotionSolverFvMesh
  dynamicMotionSolverFvMeshAMI
  dynamicMotionSolverListFvMesh
  dynamicMultiMotionSolverFvMesh
  dynamicRefineFvMesh
  simplifiedDynamicFvMesh
  staticFvMesh
)
install(TARGETS dynamicFvMesh DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
