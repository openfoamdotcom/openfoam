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
target_compile_definitions(conversion PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(conversion PUBLIC finiteVolume finiteArea meshTools)
target_include_directories(conversion PUBLIC
  ccm/common
  ccm/reader
  ccm/writer
  common/reader
  common/tables
  common/writer
  ensight/output
  fire
  polyDualMesh
  starcd
  vtk/adaptor
  vtk/output
)
install(TARGETS conversion DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
