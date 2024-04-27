set(_FILES
  pairPatchAgglomeration.C
)
add_library(pairPatchAgglomeration ${_FILES})
target_compile_features(pairPatchAgglomeration PUBLIC cxx_std_11)
target_compile_definitions(pairPatchAgglomeration PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(pairPatchAgglomeration PUBLIC finiteVolume)
target_include_directories(pairPatchAgglomeration PUBLIC
  .
)
install(TARGETS pairPatchAgglomeration DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
