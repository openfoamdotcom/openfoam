set(_FILES
  common/reader/meshReader.C
  common/reader/meshReaderAux.C
  common/reader/calcPointCells.C
  common/reader/createPolyCells.C
  common/reader/createPolyBoundary.C
  common/writer/meshWriter.C
  common/tables/boundaryRegion.C
  common/tables/cellTable.C
  fire/FIREMeshReader.C
  fire/FIREMeshWriter.C
  fire/checkFireEdges.C
  starcd/STARCDMeshReader.C
  starcd/STARCDMeshWriter.C
  polyDualMesh/polyDualMesh.C
  vtk/output/foamVtkSurfaceFieldWriter.C
)
add_library(conversion ${_FILES})
target_compile_features(conversion PUBLIC cxx_std_11)
set_property(TARGET conversion PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(conversion PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(conversion PUBLIC finiteArea finiteVolume meshTools)
target_include_directories(conversion PUBLIC
  .
)
install(TARGETS conversion DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
