set(_FILES
  laserDTRM.C
  DTRMParticle/DTRMParticle.C
  DTRMParticle/DTRMParticleIO.C
  localDensityAbsorptionEmission/localDensityAbsorptionEmission.C
  reflectionModel/reflectionModel/reflectionModel.C
  reflectionModel/reflectionModel/reflectionModelNew.C
  reflectionModel/noReflection/noReflection.C
  reflectionModel/FresnelLaser/FresnelLaser.C
  reflectionModel/Fresnel/Fresnel.C
)
add_library(laserDTRM ${_FILES})
target_compile_features(laserDTRM PUBLIC cxx_std_11)
target_compile_definitions(laserDTRM PUBLIC WM_LABEL_SIZE=${WM_LABEL_SIZE} WM_${WM_PRECISION} NoRepository OPENFOAM=${OPENFOAM_VERSION})
target_include_directories(laserDTRM PUBLIC
  .
  localDensityAbsorptionEmission
  DTRMParticle
  reflectionModel/Fresnel
  reflectionModel/FresnelLaser
  reflectionModel/reflectionModel
  reflectionModel/noReflection
)
install(TARGETS laserDTRM DESTINATION ${CMAKE_INSTALL_LIBDIR}/openfoam EXPORT openfoam-targets)
