set(_FILES
  renumberMethod/renumberMethod.C
  manualRenumber/manualRenumber.C
  CuthillMcKeeRenumber/CuthillMcKeeRenumber.C
  randomRenumber/randomRenumber.C
  springRenumber/springRenumber.C
  structuredRenumber/structuredRenumber.C
  structuredRenumber/OppositeFaceCellWaveBase.C
)
add_library(renumberMethods ${_FILES})
target_compile_features(renumberMethods PUBLIC cxx_std_11)
target_compile_definitions(renumberMethods PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(renumberMethods PUBLIC finiteVolume meshTools)
target_include_directories(renumberMethods PUBLIC
  .
)
install(TARGETS renumberMethods DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
