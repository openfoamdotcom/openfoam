set(_FILES
  PDRarrays.C
  PDRarraysAnalyse.C
  PDRarraysCalc.C
  PDRmeshArrays.C
  PDRparams.C
  PDRpatchDef.C
  PDRlegacyMeshSpec.C
  PDRutilsIntersect.C
  PDRutilsOverlap.C
  obstacles/PDRobstacle.C
  obstacles/PDRobstacleIO.C
  obstacles/PDRobstacleTypes.C
  obstacles/PDRobstacleLegacyIO.C
  obstacles/PDRobstacleLegacyRead.C
)
add_library(pdrFields ${_FILES})
target_compile_features(pdrFields PUBLIC cxx_std_11)
target_compile_definitions(pdrFields PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(pdrFields PUBLIC blockMeshLib finiteVolume)
target_include_directories(pdrFields PUBLIC
  .
  obstacles
)
install(TARGETS pdrFields DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
