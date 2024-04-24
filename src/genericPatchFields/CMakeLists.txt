set(_FILES
  common/genericPatchFieldBase.C
  genericFaPatchField/genericFaPatchFields.C
  genericFvPatchField/genericFvPatchFields.C
  genericFvsPatchField/genericFvsPatchFields.C
  genericPointPatchField/genericPointPatchFields.C
)
add_library(genericPatchFields ${_FILES})
target_compile_features(genericPatchFields PUBLIC cxx_std_11)
target_compile_definitions(genericPatchFields PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(genericPatchFields PUBLIC 
  genericFvsPatchField
  genericPointPatchField
  genericFvPatchField
  genericFaePatchField
  common
  genericFaPatchField
)
install(TARGETS genericPatchFields DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
