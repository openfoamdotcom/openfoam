set(_FILES
  kahipDecomp.C
)
add_library(kahipDecomp ${_FILES})
target_compile_features(kahipDecomp PUBLIC cxx_std_11)
target_compile_definitions(kahipDecomp PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(kahipDecomp PUBLIC 
  .
)
install(TARGETS kahipDecomp DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
