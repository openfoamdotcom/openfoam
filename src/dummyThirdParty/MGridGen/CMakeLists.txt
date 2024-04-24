set(_FILES
)
add_library(MGridGen ${_FILES})
target_compile_features(MGridGen PUBLIC cxx_std_11)
target_compile_definitions(MGridGen PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(MGridGen PUBLIC
  .
)
install(TARGETS MGridGen DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
