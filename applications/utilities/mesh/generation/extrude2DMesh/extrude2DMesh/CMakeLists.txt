set(_FILES
  extrude2DMesh/extrude2DMesh.C
  patchToPoly2DMesh/patchToPoly2DMesh.C
)
add_library(extrude2DMesh ${_FILES})
target_compile_features(extrude2DMesh PUBLIC cxx_std_11)
target_compile_definitions(extrude2DMesh PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(extrude2DMesh PUBLIC dynamicMesh extrudeModel)
target_include_directories(extrude2DMesh PUBLIC
  .
)
install(TARGETS extrude2DMesh DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
