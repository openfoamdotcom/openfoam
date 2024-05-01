set(_FILES
  scotchDecomp.C
)
add_library(scotchDecomp ${_FILES})
target_compile_features(scotchDecomp PUBLIC cxx_std_11)
target_compile_definitions(scotchDecomp PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(scotchDecomp PUBLIC SCOTCH::scotch decompositionMethods)
target_include_directories(scotchDecomp PUBLIC
  .
)
install(TARGETS scotchDecomp DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
