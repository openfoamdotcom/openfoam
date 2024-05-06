set(_FILES
  distributedTriSurfaceMesh/distributedTriSurfaceMesh.C
  patchDistMethods/exact/exactPatchDistMethod.C
)
add_library(distributed ${_FILES})
target_compile_features(distributed PUBLIC cxx_std_11)
set_property(TARGET distributed PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(distributed PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(distributed PUBLIC decompositionMethods)
target_include_directories(distributed PUBLIC
  .
)
install(TARGETS distributed DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
