set(_FILES
  barotropicCompressibilityModel/barotropicCompressibilityModel.C
  barotropicCompressibilityModel/barotropicCompressibilityModelNew.C
  linear/linear.C
  Wallis/Wallis.C
  Chung/Chung.C
)
add_library(barotropicCompressibilityModel ${_FILES})
target_compile_features(barotropicCompressibilityModel PUBLIC cxx_std_11)
target_compile_definitions(barotropicCompressibilityModel PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(barotropicCompressibilityModel PUBLIC finiteVolume)
target_include_directories(barotropicCompressibilityModel PUBLIC
  Chung
  Wallis
  barotropicCompressibilityModel
  linear
)
install(TARGETS barotropicCompressibilityModel DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
