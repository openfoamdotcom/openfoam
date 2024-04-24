set(_FILES
  faFieldDecomposer.C
  faFieldDecomposerCache.C
  faMeshDecomposition.C
)
add_library(faDecompose ${_FILES})
target_compile_features(faDecompose PUBLIC cxx_std_11)
target_compile_definitions(faDecompose PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(faDecompose PUBLIC 
  .
)
install(TARGETS faDecompose DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
