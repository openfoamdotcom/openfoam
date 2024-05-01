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
target_link_libraries(geometricVoF PUBLIC dynamicMesh sampling twoPhaseProperties)
target_include_directories(geometricVoF PUBLIC
  advectionSchemes/isoAdvection
  cellCuts/cutCell
  cellCuts/cutFace
  reconstructedDistanceFunction
  reconstructionSchemes
  reconstructionSchemes/isoSchemes/isoAlpha
  reconstructionSchemes/plicSchemes/gradAlpha
  reconstructionSchemes/plicSchemes/plicRDF
  sampledInterface
  surfaceIterators
)
install(TARGETS geometricVoF DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
