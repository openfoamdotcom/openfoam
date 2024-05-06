set(_FILES
  distributionModel/distributionModel.C
  distributionModel/distributionModelNew.C
  binned/binned.C
  exponential/exponential.C
  fixedValue/fixedValue.C
  general/general.C
  multiNormal/multiNormal.C
  normal/normal.C
  RosinRammler/RosinRammler.C
  massRosinRammler/massRosinRammler.C
  uniform/uniform.C
)
add_library(distributionModels ${_FILES})
target_compile_features(distributionModels PUBLIC cxx_std_11)
set_property(TARGET distributionModels PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(distributionModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(distributionModels PUBLIC lagrangian)
target_include_directories(distributionModels PUBLIC
  .
)
install(TARGETS distributionModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
