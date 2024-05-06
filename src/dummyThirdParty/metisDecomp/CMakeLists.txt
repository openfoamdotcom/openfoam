set(_FILES
)
add_library(metisDecomp ${_FILES})
target_compile_features(metisDecomp PUBLIC cxx_std_11)
set_property(TARGET metisDecomp PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(metisDecomp PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(metisDecomp PUBLIC METIS::METIS decompositionMethods)
target_include_directories(metisDecomp PUBLIC
  .
)
install(TARGETS metisDecomp DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
