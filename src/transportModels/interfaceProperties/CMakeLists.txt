set(_FILES
  interfaceProperties.C
  interfaceCompression/interfaceCompression.C
  alphaContactAngle/alphaContactAngleTwoPhaseFvPatchScalarField.C
  surfaceTensionModels/surfaceTensionModel/surfaceTensionModel.C
  surfaceTensionModels/surfaceTensionModel/surfaceTensionModelNew.C
  surfaceTensionModels/constant/constantSurfaceTension.C
  surfaceTensionModels/temperatureDependent/temperatureDependentSurfaceTension.C
)
add_library(interfaceProperties ${_FILES})
target_compile_features(interfaceProperties PUBLIC cxx_std_11)
set_property(TARGET interfaceProperties PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(interfaceProperties PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(interfaceProperties PUBLIC finiteVolume twoPhaseMixture)
target_include_directories(interfaceProperties PUBLIC
  .
)
install(TARGETS interfaceProperties DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
