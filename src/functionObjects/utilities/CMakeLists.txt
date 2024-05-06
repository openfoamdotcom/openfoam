set(_FILES
  abort/abort.C
  caseInfo/caseInfo.C
  codedFunctionObject/codedFunctionObject.C
  areaWrite/areaWrite.C
  ensightWrite/ensightWrite.C
  ensightWrite/ensightWriteUpdate.C
  vtkWrite/vtkWrite.C
  vtkWrite/vtkWriteUpdate.C
  multiRegion/multiRegion.C
  removeRegisteredObject/removeRegisteredObject.C
  parProfiling/parProfiling.C
  parProfiling/parProfilingSolver.C
  solverInfo/solverInfo.C
  timeInfo/timeInfo.C
  runTimeControl/runTimeControl.C
  runTimeControl/runTimeCondition/runTimeCondition/runTimeCondition.C
  runTimeControl/runTimeCondition/runTimeCondition/runTimeConditionNew.C
  runTimeControl/runTimeCondition/averageCondition/averageCondition.C
  runTimeControl/runTimeCondition/equationMaxIterCondition/equationMaxIterCondition.C
  runTimeControl/runTimeCondition/equationInitialResidualCondition/equationInitialResidualCondition.C
  runTimeControl/runTimeCondition/maxDurationCondition/maxDurationCondition.C
  runTimeControl/runTimeCondition/minMaxCondition/minMaxCondition.C
  runTimeControl/runTimeCondition/minTimeStepCondition/minTimeStepCondition.C
  runTimeControl/runTimeCondition/noneCondition/noneCondition.C
  setTimeStep/setTimeStepFunctionObject.C
  systemCall/systemCall.C
  timeActivatedFileUpdate/timeActivatedFileUpdate.C
  writeDictionary/writeDictionary.C
  writeObjects/writeObjects.C
  thermoCoupleProbes/thermoCoupleProbes.C
  syncObjects/syncObjects.C
)
add_library(utilityFunctionObjects ${_FILES})
target_compile_features(utilityFunctionObjects PUBLIC cxx_std_11)
set_property(TARGET utilityFunctionObjects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(utilityFunctionObjects PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(utilityFunctionObjects PUBLIC ODE compressibleTransportModels conversion dynamicMesh fluidThermophysicalModels sampling)
target_include_directories(utilityFunctionObjects PUBLIC
  .
)
install(TARGETS utilityFunctionObjects DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
