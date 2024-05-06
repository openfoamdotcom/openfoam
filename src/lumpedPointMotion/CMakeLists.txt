set(_FILES
  controller/lumpedPointController.C
  state/lumpedPointState.C
  state/lumpedPointStateWriter.C
  movement/lumpedPointMovement.C
  movement/lumpedPointMovementWriter.C
  movement/lumpedPointIOMovement.C
  tools/lumpedPointTools.C
  pointPatchFields/lumpedPointDisplacementPointPatchVectorField.C
)
add_library(lumpedPointMotion ${_FILES})
target_compile_features(lumpedPointMotion PUBLIC cxx_std_11)
set_property(TARGET lumpedPointMotion PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(lumpedPointMotion PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(lumpedPointMotion PUBLIC dynamicMesh)
target_include_directories(lumpedPointMotion PUBLIC
  .
)
install(TARGETS lumpedPointMotion DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
