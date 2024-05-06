set(_FILES
  DPMTurbulenceModels.C
)
add_library(DPMTurbulenceModels ${_FILES})
target_compile_features(DPMTurbulenceModels PUBLIC cxx_std_11)
set_property(TARGET DPMTurbulenceModels PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(DPMTurbulenceModels PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(DPMTurbulenceModels PUBLIC compressibleTransportModels incompressibleTurbulenceModels)
target_include_directories(DPMTurbulenceModels PUBLIC
  .
)
install(TARGETS DPMTurbulenceModels DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
