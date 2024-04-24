set(_FILES
  common/ccmBase.C
  common/ccmInternal.C
  reader/ccmReader.C
  reader/ccmReaderAux.C
  reader/ccmReaderMesh.C
  reader/ccmReaderSolution.C
  reader/ccmReaderOptions.C
  writer/ccmWriter.C
  writer/ccmWriterMesh.C
  writer/ccmWriterSolution.C
)
add_library(ccm ${_FILES})
target_compile_features(ccm PUBLIC cxx_std_11)
target_compile_definitions(ccm PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(ccm PUBLIC 
  reader
  common
  writer
)
install(TARGETS ccm DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
