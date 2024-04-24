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
target_include_directories(lagrangianFunctionObjects PUBLIC 
  icoUncoupledKinematicCloud
  vtkCloud
  cloudInfo
  common
  dataCloud
  dsmcFields
)
install(TARGETS lagrangianFunctionObjects DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
