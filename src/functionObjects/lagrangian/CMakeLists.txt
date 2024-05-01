set(_FILES
  common/parcelSelectionDetail.C
  dataCloud/dataCloud.C
  cloudInfo/cloudInfo.C
  icoUncoupledKinematicCloud/icoUncoupledKinematicCloud.C
  dsmcFields/dsmcFields.C
  vtkCloud/vtkCloud.C
)
add_library(lagrangianFunctionObjects ${_FILES})
target_compile_features(lagrangianFunctionObjects PUBLIC cxx_std_11)
target_compile_definitions(lagrangianFunctionObjects PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(lagrangianFunctionObjects PUBLIC DSMC conversion faOptions lagrangianTurbulence regionFaModels surfaceFilmModels)
target_include_directories(lagrangianFunctionObjects PUBLIC
  cloudInfo
  common
  dataCloud
  dsmcFields
  icoUncoupledKinematicCloud
  vtkCloud
)
install(TARGETS lagrangianFunctionObjects DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
