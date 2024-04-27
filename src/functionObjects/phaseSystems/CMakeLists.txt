set(_FILES
  sizeDistribution/sizeDistribution.C
  phaseForces/phaseForces.C
)
add_library(phaseFunctionObjects ${_FILES})
target_compile_features(phaseFunctionObjects PUBLIC cxx_std_11)
target_compile_definitions(phaseFunctionObjects PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(phaseFunctionObjects PUBLIC fieldFunctionObjects reactingMultiphaseSystem dynamicMesh meshTools)
target_include_directories(phaseFunctionObjects PUBLIC
  phaseForces
  sizeDistribution
)
install(TARGETS phaseFunctionObjects DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
