set(_FILES
  extrudeModel/extrudeModel.C
  extrudeModel/extrudeModelNew.C
  linearNormal/linearNormal.C
  planeExtrusion/planeExtrusion.C
  linearDirection/linearDirection.C
  linearRadial/linearRadial.C
  offsetSurface/offsetSurface.C
  radial/radial.C
  sigmaRadial/sigmaRadial.C
  sector/sector.C
  cyclicSector/cyclicSector.C
  wedge/wedge.C
  polyline/polyline.C
)
add_library(extrudeModel ${_FILES})
target_compile_features(extrudeModel PUBLIC cxx_std_11)
target_compile_definitions(extrudeModel PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(extrudeModel PUBLIC blockMeshLib)
target_include_directories(extrudeModel PUBLIC
  cyclicSector
  extrudeModel
  linearDirection
  linearNormal
  linearRadial
  offsetSurface
  planeExtrusion
  polyline
  radial
  sector
  sigmaRadial
  wedge
)
install(TARGETS extrudeModel DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
