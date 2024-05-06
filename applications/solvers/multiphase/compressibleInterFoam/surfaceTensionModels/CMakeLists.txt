set(_FILES
  liquidProperties/liquidPropertiesSurfaceTension.C
)
add_library(twoPhaseSurfaceTension ${_FILES})
target_compile_features(twoPhaseSurfaceTension PUBLIC cxx_std_11)
set_property(TARGET twoPhaseSurfaceTension PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(twoPhaseSurfaceTension PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(twoPhaseSurfaceTension PUBLIC finiteVolume fluidThermophysicalModels interfaceProperties thermophysicalProperties)
target_include_directories(twoPhaseSurfaceTension PUBLIC
  .
)
install(TARGETS twoPhaseSurfaceTension DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
