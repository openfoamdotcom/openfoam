set(_FILES
  processorMeshes.C
  fvFieldReconstructor.C
  pointFieldReconstructor.C
  passivePositionParticleCloud.C
  lagrangianReconstructor.C
)
add_library(reconstruct ${_FILES})
target_compile_features(reconstruct PUBLIC cxx_std_11)
target_compile_definitions(reconstruct PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(reconstruct PUBLIC finiteVolume lagrangian)
target_include_directories(reconstruct PUBLIC
  .
)
install(TARGETS reconstruct DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
