set(_FILES
  decompositionMethod/decompositionMethod.C
  geomDecomp/geomDecomp.C
  simpleGeomDecomp/simpleGeomDecomp.C
  hierarchGeomDecomp/hierarchGeomDecomp.C
  manualDecomp/manualDecomp.C
  multiLevelDecomp/multiLevelDecomp.C
  metisLikeDecomp/metisLikeDecomp.C
  structuredDecomp/structuredDecomp.C
  randomDecomp/randomDecomp.C
  noDecomp/noDecomp.C
  decompositionConstraints/decompositionConstraint/decompositionConstraint.C
  decompositionConstraints/preserveBaffles/preserveBafflesConstraint.C
  decompositionConstraints/preserveFaceZones/preserveFaceZonesConstraint.C
  decompositionConstraints/preservePatches/preservePatchesConstraint.C
  decompositionConstraints/geometric/geometricConstraint.C
  decompositionConstraints/singleProcessorFaceSets/singleProcessorFaceSetsConstraint.C
  decompositionConstraints/refinementHistory/refinementHistoryConstraint.C
)
add_library(decompositionMethods ${_FILES})
target_compile_features(decompositionMethods PUBLIC cxx_std_11)
set_property(TARGET decompositionMethods PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(decompositionMethods PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(decompositionMethods PUBLIC dynamicMesh)
target_include_directories(decompositionMethods PUBLIC
  .
)
install(TARGETS decompositionMethods DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
