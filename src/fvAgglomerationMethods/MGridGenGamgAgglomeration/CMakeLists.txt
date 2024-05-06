set(_FILES
  MGridGenGAMGAgglomeration.C
  MGridGenGAMGAgglomerate.C
)
add_library(MGridGenGAMGAgglomeration ${_FILES})
target_compile_features(MGridGenGAMGAgglomeration PUBLIC cxx_std_11)
set_property(TARGET MGridGenGAMGAgglomeration PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(MGridGenGAMGAgglomeration PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(MGridGenGAMGAgglomeration PUBLIC finiteVolume)
target_include_directories(MGridGenGAMGAgglomeration PUBLIC
  .
)
install(TARGETS MGridGenGAMGAgglomeration DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
