set(_FILES
  particle/particle.C
  particle/particleIO.C
  passiveParticle/passiveParticleCloud.C
  indexedParticle/indexedParticleCloud.C
  injectedParticle/injectedParticle.C
  injectedParticle/injectedParticleIO.C
  injectedParticle/injectedParticleCloud.C
  InteractionLists/referredWallFace/referredWallFace.C
)
add_library(lagrangian ${_FILES})
target_compile_features(lagrangian PUBLIC cxx_std_11)
target_compile_definitions(lagrangian PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_link_libraries(lagrangian PUBLIC meshTools)
target_include_directories(lagrangian PUBLIC
  .
)
install(TARGETS lagrangian DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
