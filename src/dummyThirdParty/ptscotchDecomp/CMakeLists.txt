set(_FILES
)
add_library(ptscotchDecomp ${_FILES})
target_compile_features(ptscotchDecomp PUBLIC cxx_std_11)
set_property(TARGET ptscotchDecomp PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(ptscotchDecomp PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(ptscotchDecomp PUBLIC SCOTCH::ptscotch decompositionMethods)
target_include_directories(ptscotchDecomp PUBLIC
  .
)
install(TARGETS ptscotchDecomp DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
