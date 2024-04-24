set(_FILES
  metisDecomp.C
)
add_library(metisDecomp ${_FILES})
target_compile_features(metisDecomp PUBLIC cxx_std_11)
target_compile_definitions(metisDecomp PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(metisDecomp PUBLIC 
  .
)
install(TARGETS metisDecomp DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
