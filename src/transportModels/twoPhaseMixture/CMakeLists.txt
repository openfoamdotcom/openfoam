set(_FILES
  twoPhaseMixture/twoPhaseMixture.C
)
add_library(twoPhaseMixture ${_FILES})
target_compile_features(twoPhaseMixture PUBLIC cxx_std_11)
target_compile_definitions(twoPhaseMixture PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(twoPhaseMixture PUBLIC finiteVolume)
target_include_directories(twoPhaseMixture PUBLIC
  .
)
install(TARGETS twoPhaseMixture DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
