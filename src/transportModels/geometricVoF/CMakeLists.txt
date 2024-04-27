set(_FILES
  cellCuts/cutCell/cutCell.C
  cellCuts/cutCell/cutCellPLIC.C
  cellCuts/cutCell/cutCellIso.C
  cellCuts/cutFace/cutFace.C
  cellCuts/cutFace/cutFacePLIC.C
  cellCuts/cutFace/cutFaceAdvect.C
  cellCuts/cutFace/cutFaceIso.C
  surfaceIterators/surfaceIteratorPLIC.C
  surfaceIterators/surfaceIteratorIso.C
  reconstructedDistanceFunction/reconstructedDistanceFunction.C
  reconstructionSchemes/reconstructionSchemesNew.C
  reconstructionSchemes/reconstructionSchemes.C
  reconstructionSchemes/isoSchemes/isoAlpha/isoAlpha.C
  reconstructionSchemes/plicSchemes/gradAlpha/gradAlpha.C
  reconstructionSchemes/plicSchemes/plicRDF/plicRDF.C
  advectionSchemes/isoAdvection/isoAdvection.C
  sampledInterface/sampledInterface.C
)
add_library(geometricVoF ${_FILES})
target_compile_features(geometricVoF PUBLIC cxx_std_11)
target_compile_definitions(geometricVoF PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(geometricVoF PUBLIC sampling dynamicMesh twoPhaseProperties)
target_include_directories(geometricVoF PUBLIC
  cellCuts/cutCell
  cellCuts/cutFace
  reconstructionSchemes
  reconstructionSchemes/plicSchemes/gradAlpha
  reconstructionSchemes/plicSchemes/plicRDF
  reconstructionSchemes/isoSchemes/isoAlpha
  surfaceIterators
  advectionSchemes/isoAdvection
  sampledInterface
  reconstructedDistanceFunction
)
install(TARGETS geometricVoF DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
