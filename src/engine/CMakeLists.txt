set(_FILES
  engineTime/engineTime/engineTime.C
  engineTime/engineTime/engineTimeNew.C
  engineTime/freePiston/freePiston.C
  engineTime/crankConRod/crankConRod.C
  ignition/ignition.C
  ignition/ignitionIO.C
  ignition/ignitionSite.C
  ignition/ignitionSiteIO.C
  engineValve/engineValve.C
  enginePiston/enginePiston.C
  engineMesh/engineMesh/engineMesh.C
  engineMesh/engineMesh/engineMeshNew.C
  engineMesh/staticEngineMesh/staticEngineMesh.C
  engineMesh/layeredEngineMesh/layeredEngineMesh.C
  engineMesh/fvMotionSolverEngineMesh/fvMotionSolverEngineMesh.C
)
add_library(engine ${_FILES})
target_compile_features(engine PUBLIC cxx_std_11)
target_compile_definitions(engine PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(engine PUBLIC fvMotionSolvers)
target_include_directories(engine PUBLIC
  .
)
install(TARGETS engine DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
