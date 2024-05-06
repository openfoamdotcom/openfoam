set(_FILES
  solidParticle.C
  solidParticleIO.C
  solidParticleCloud.C
)
add_library(solidParticle ${_FILES})
target_compile_features(solidParticle PUBLIC cxx_std_11)
set_property(TARGET solidParticle PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(solidParticle PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(solidParticle PUBLIC finiteVolume lagrangian)
target_include_directories(solidParticle PUBLIC
  .
)
install(TARGETS solidParticle DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
