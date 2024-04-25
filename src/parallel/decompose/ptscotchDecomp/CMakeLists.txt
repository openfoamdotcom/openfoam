set(_FILES
  ptscotchDecomp.C
)
add_library(ptscotchDecomp ${_FILES})
target_compile_features(ptscotchDecomp PUBLIC cxx_std_11)
target_compile_definitions(ptscotchDecomp PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(ptscotchDecomp PUBLIC decompositionMethods SCOTCH::ptscotch)
target_include_directories(ptscotchDecomp PUBLIC
  .
)
install(TARGETS ptscotchDecomp DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
