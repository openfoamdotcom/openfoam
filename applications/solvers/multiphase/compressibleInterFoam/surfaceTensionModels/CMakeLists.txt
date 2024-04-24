set(_FILES
  liquidProperties/liquidPropertiesSurfaceTension.C
)
add_library(twoPhaseSurfaceTension ${_FILES})
target_compile_features(twoPhaseSurfaceTension PUBLIC cxx_std_11)
target_compile_definitions(twoPhaseSurfaceTension PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(twoPhaseSurfaceTension PUBLIC
  liquidProperties
)
install(TARGETS twoPhaseSurfaceTension DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
